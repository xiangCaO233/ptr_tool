//
// Created by 2333 xiang on 2024/8/26.
//

#ifndef PTR_TOOLS_GLOBALSCREEN_H
#define PTR_TOOLS_GLOBALSCREEN_H

#include <ApplicationServices/ApplicationServices.h>
#include "keyboard/dispatcher/KeyEventDispatcher.h"
#include "pointer/dispatcher/PointerEventDispatcher.h"
#include <iostream>
#include <thread>

class GlobalScreen {

public:

    static GlobalScreen globalScreenVal;
    static std::vector<int> pressCode;
    static std::vector<int> controlsCode;

    //开始监听
    static void startListen() {
        std::thread listenThread(open);
        listenThread.detach();
        usleep(20 * 1000);
    }

    //注册监听
    void init() {
        // 创建事件监听器
        eventTap = CGEventTapCreate(
                kCGSessionEventTap, // 监听范围：全局
                kCGHeadInsertEventTap, // 插入位置：头部
                kCGEventTapOptionDefault, // 选项
                CGEventMaskBit(kCGEventKeyDown) |
                CGEventMaskBit(kCGEventKeyUp) |
                CGEventMaskBit(kCGEventFlagsChanged) |
                CGEventMaskBit(kCGEventMouseMoved) |
                CGEventMaskBit(kCGEventLeftMouseDown) |
                CGEventMaskBit(kCGEventLeftMouseUp) |
                CGEventMaskBit(kCGEventLeftMouseDragged) |
                CGEventMaskBit(kCGEventRightMouseUp) |
                CGEventMaskBit(kCGEventRightMouseDown) |
                CGEventMaskBit(kCGEventRightMouseDragged) |
                CGEventMaskBit(kCGEventOtherMouseUp) |
                CGEventMaskBit(kCGEventOtherMouseDown) |
                CGEventMaskBit(kCGEventOtherMouseDragged) |
                CGEventMaskBit(kCGEventScrollWheel), // 监听事件类型
                eventCallback, // 回调函数
                this // 用户数据，传递当前对象指针
        );

        if (!eventTap) {
            std::cerr << "注册失败" << std::endl;
            return;
        }

        // 创建运行循环源
        runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);

        if (!eventTap || isRunning) return;

        // 添加源到运行循环
        CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

        // 启动事件监听
        CGEventTapEnable(eventTap, true);
        isRunning = true;

        // 运行事件循环
        CFRunLoopRun();
    }

    //取消注册
    void unRegisterCoreGraphics() {
        if (!isRunning) return;

        // 停止事件循环
        CFRunLoopStop(CFRunLoopGetCurrent());
        isRunning = false;
    }

    //添加按键监听器
    void addKeyListener(KeyboardListener &listener) {
        keyEventDispatcher.addKeyListener(listener);
    }

    //删除按键监听器
    void removeKeyListener(KeyboardListener &listener) {
        keyEventDispatcher.removeKeyListener(&listener);
    }


    //添加鼠标指针监听器
    void addPointerListener(PointerListener &listener) {
        pointerEventDispatcher.addPointerListener(listener);
    }

    //删除鼠标指针监听器
    void removePointerListener(PointerListener &listener) {
        pointerEventDispatcher.removePointerListener(&listener);
    }

    //添加鼠标指针监听器
    void addPointerMotionListener(PointerMotionListener &listener) {
        pointerEventDispatcher.addPointerMotionListener(listener);
    }

    //删除鼠标指针监听器
    void removePointerMotionListener(PointerMotionListener &listener) {
        pointerEventDispatcher.removePointerMotionListener(&listener);
    }


private:
    //鼠标指针事件分派器
    PointerEventDispatcher pointerEventDispatcher;
    //键盘事件分派器
    KeyEventDispatcher keyEventDispatcher;

    //事件监听器
    CFMachPortRef eventTap{};
    //行循环源
    CFRunLoopSourceRef runLoopSource{};
    //运行标志符
    bool isRunning{};

    //初始化
    static void open() {
        globalScreenVal = GlobalScreen();
        globalScreenVal.init();
    }

    // 静态回调函数
    static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
        auto *self = static_cast<GlobalScreen *>(refcon);

        auto keyCode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
        //鼠标指针位置
        CGPoint mouseLocation = CGEventGetLocation(event);

        int64_t scrollPhase = CGEventGetIntegerValueField(event, kCGScrollWheelEventScrollPhase);
        double fixedPtDeltaY = CGEventGetDoubleValueField(event, kCGScrollWheelEventFixedPtDeltaAxis1);
        double pointDeltaY = CGEventGetDoubleValueField(event, kCGScrollWheelEventPointDeltaAxis1);

        double fixedPtDeltaX = CGEventGetDoubleValueField(event, kCGScrollWheelEventFixedPtDeltaAxis2);
        double pointDeltaX = CGEventGetDoubleValueField(event, kCGScrollWheelEventPointDeltaAxis2);
        // 累积滚动量
        static double accumulatedDeltaY = 0.0;
        static double accumulatedDeltaX = 0.0;

        switch (type) {
            case kCGEventKeyDown: {
                //按键按下
                sendKeyEvent(self, keyCode, KeyboardEventType::PRESS);
                //防止按下列表反复增加
                auto it = std::find(pressCode.begin(), pressCode.end(), keyCode);
                if (it == pressCode.end()) {
                    pressCode.push_back(keyCode);
                }
                break;
            }
            case kCGEventKeyUp: {
                //按键释放
                sendKeyEvent(self, keyCode, KeyboardEventType::RELEASE);
                //检查是否按完
                auto it = std::find(pressCode.begin(), pressCode.end(), keyCode);
                if (it != pressCode.end()) {
                    long index = distance(pressCode.begin(), it);
                    //从列表按下列表中删除并发送按了（按完-按下+松开）事件
                    pressCode.erase(pressCode.begin() + index, pressCode.begin() + index + 1);
                    sendKeyEvent(self, keyCode, KeyboardEventType::PRESSED);
                }
            }
            case kCGEventFlagsChanged: {
                //控制键状态改变
                CGEventFlags flags = CGEventGetFlags(event);
                if (flags & kCGEventFlagMaskCommand ||  //command
                    flags & kCGEventFlagMaskAlternate ||    //alt(option)
                    flags & kCGEventFlagMaskShift ||            //shift
                    flags & kCGEventFlagMaskControl         //ctrl
                        ) {
                    //发送按下事件
                    sendKeyEvent(self, keyCode, KeyboardEventType::PRESS);
                    //添加到按下列表
                    controlsCode.push_back(keyCode);
                } else {
                    //控制键释放
                    auto it = std::find(controlsCode.begin(), controlsCode.end(), keyCode);
                    //在控制键按下列表中查询（防止常规按键复触发）
                    if (it != controlsCode.end()) {
                        long index = distance(controlsCode.begin(), it);
                        controlsCode.erase(controlsCode.begin() + index, controlsCode.begin() + index + 1);
                        sendKeyEvent(self, keyCode, KeyboardEventType::RELEASE);
                        sendKeyEvent(self, keyCode, KeyboardEventType::PRESSED);
                    }
                }
            }

                //以下为鼠标事件
            case kCGEventLeftMouseDown: {
                //鼠标左键按下 code set 1
                sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y, PointerEventType::PRESS);
                break;
            }

            case kCGEventLeftMouseUp: {
                //鼠标左键释放
                sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y, PointerEventType::RELEASE);
                break;
            }

            case kCGEventRightMouseDown: {
                //鼠标右键按下 code set 2
                sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y, PointerEventType::PRESS);
                break;
            }
            case kCGEventRightMouseUp: {
                //右键释放
                sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y, PointerEventType::RELEASE);
                break;
            }
            case kCGEventMouseMoved: {
                //鼠标移动
                sendPointerEvent(self, 0, mouseLocation.x, mouseLocation.y, PointerEventType::MOVE);
                break;
            }
            case kCGEventLeftMouseDragged: {
                //左键拖动
                sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y, PointerEventType::DRAG);
                break;
            }
            case kCGEventRightMouseDragged: {
                //右键拖动
                sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y, PointerEventType::DRAG);
                break;
            }
            case kCGEventScrollWheel: {
                //可以发送滚动事件
                //滚轮滚动
                if (scrollPhase == kCGScrollPhaseBegan) {
                    // 滚动开始
                    accumulatedDeltaY = 0.0;
                    accumulatedDeltaX = 0.0;
                } else if (scrollPhase == kCGScrollPhaseChanged) {
                    // 滚动变化
                    accumulatedDeltaY += fixedPtDeltaY;
                    accumulatedDeltaX += fixedPtDeltaX;
                } else if (scrollPhase == kCGScrollPhaseEnded || scrollPhase == kCGMomentumScrollPhaseEnd) {
                    // 滚动结束
                    std::cout << "Y累计: " << accumulatedDeltaY << std::endl;
                    std::cout << "X累计: " << accumulatedDeltaX << std::endl;
                }

                break;
            }
            case kCGEventNull://空事件，防止空指针，没用
            case kCGEventTabletPointer://数位板输入信息（包括位置，压力等信息）
            case kCGEventTabletProximity:
            case kCGEventOtherMouseUp://中键，自定义按键，dpi调节按键等、
            case kCGEventOtherMouseDown://中键，自定义按键，dpi调节按键等、
            case kCGEventOtherMouseDragged:
            case kCGEventTapDisabledByTimeout://超时保护，macos会自动停用
            case kCGEventTapDisabledByUserInput:
                break;
        }
        return event; // 必须返回事件
    };

    static void sendKeyEvent(GlobalScreen *s, int code, KeyboardEventType t) {
        auto e = KeyboardEvent(code, t);
        s->keyEventDispatcher.dispatchEvent(e);
    }

    static void sendPointerEvent(GlobalScreen *s, int code, int x, int y, PointerEventType t) {
        auto e = PointerEvent(code, x, y, t);
        s->pointerEventDispatcher.dispatchEvent(e);
    }

    static void sendPointerEvent(GlobalScreen *s, int code, double x, double y, PointerEventType t) {
        auto e = PointerEvent(code, x, y, t);
        s->pointerEventDispatcher.dispatchEvent(e);
    }
};

#endif //PTR_TOOLS_GLOBALSCREEN_H
