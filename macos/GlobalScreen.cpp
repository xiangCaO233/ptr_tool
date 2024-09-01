#include "GlobalScreen.h"

//
// Created by 2333 xiang on 2024/8/27.
//
using namespace std;

GlobalScreen GlobalScreen::globalScreenVal;
vector<int> GlobalScreen::controlsCode;
vector<int> GlobalScreen::dragsCode;

void GlobalScreen::startListen() {
    std::thread listenThread(open);
    listenThread.detach();
    usleep(20 * 1000);
}

void GlobalScreen::init() {
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

void GlobalScreen::unRegisterCoreGraphics() {
    if (!isRunning) return;
    // 停止事件循环
    CFRunLoopStop(CFRunLoopGetCurrent());
    isRunning = false;
}

void GlobalScreen::addKeyListener(KeyboardListener &listener) {
    keyEventDispatcher.addKeyListener(listener);
}

void GlobalScreen::removeKeyListener(KeyboardListener &listener) {
    keyEventDispatcher.removeKeyListener(&listener);
}

void GlobalScreen::addPointerListener(PointerListener &listener) {
    pointerEventDispatcher.addPointerListener(listener);
}

void GlobalScreen::removePointerListener(PointerListener &listener) {
    pointerEventDispatcher.removePointerListener(&listener);
}

void GlobalScreen::addPointerMotionListener(PointerMotionListener &listener) {
    pointerEventDispatcher.addPointerMotionListener(listener);
}

void GlobalScreen::removePointerMotionListener(PointerMotionListener &listener) {
    pointerEventDispatcher.removePointerMotionListener(&listener);
}

void GlobalScreen::addPointerWheelListener(PointerWheelListener &listener) {
    wheelEventDispatcher.addPointerWheelListener(listener);
}

void GlobalScreen::removePointerWheelListener(PointerWheelListener &listener) {
    wheelEventDispatcher.removePointerWheelListener(&listener);
}

void GlobalScreen::open() {
    globalScreenVal = GlobalScreen();
    globalScreenVal.init();
}

void GlobalScreen::sendKeyEvent(GlobalScreen *s, int code, bool isShiftDown, bool isControlDown, bool isOptionDown,
                                bool isCommandDown, KeyboardEventType t) {
    auto e = KeyboardEvent(code, isShiftDown, isControlDown, isOptionDown, isCommandDown, t);
    s->keyEventDispatcher.dispatchEvent(e);
}

void GlobalScreen::sendPointerEvent(GlobalScreen *s, int code, int x, int y, bool isShiftDown, bool isControlDown,
                                    bool isOptionDown, bool isCommandDown, PointerEventType t) {
    auto e = PointerEvent(code, x, y, isShiftDown, isControlDown, isOptionDown, isCommandDown, t);
    s->pointerEventDispatcher.dispatchEvent(e);
}

void GlobalScreen::sendPointerEvent(GlobalScreen *s, int code, double x, double y, bool isShiftDown, bool isControlDown,
                                    bool isOptionDown, bool isCommandDown, PointerEventType t) {
    auto e = PointerEvent(code, x, y, isShiftDown, isControlDown, isOptionDown, isCommandDown, t);
    s->pointerEventDispatcher.dispatchEvent(e);
}

void
GlobalScreen::sendWheelEvent(GlobalScreen *s, double dx, double dy, double sx, double sy, bool isShiftDown,
                             bool isControlDown, bool isOptionDown, bool isCommandDown, PointerWheelEventType t) {
    auto e = PointerWheelEvent(dx, dy, sx, sy, isShiftDown, isControlDown, isOptionDown, isCommandDown, t);
    s->wheelEventDispatcher.dispatchEvent(e);
}

CGEventRef GlobalScreen::eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    auto *self = static_cast<GlobalScreen *>(refcon);
    auto keyCode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
    //鼠标指针位置
    CGPoint mouseLocation = CGEventGetLocation(event);

    int64_t scrollPhase = CGEventGetIntegerValueField(event, kCGScrollWheelEventScrollPhase);
    double fixedPtDeltaY = CGEventGetDoubleValueField(event, kCGScrollWheelEventFixedPtDeltaAxis1);
    //double pointDeltaY = CGEventGetDoubleValueField(event, kCGScrollWheelEventPointDeltaAxis1);

    double fixedPtDeltaX = CGEventGetDoubleValueField(event, kCGScrollWheelEventFixedPtDeltaAxis2);
    //double pointDeltaX = CGEventGetDoubleValueField(event, kCGScrollWheelEventPointDeltaAxis2);
    // 累积滚动量
    static double accumulatedDeltaY = 0.0;
    static double accumulatedDeltaX = 0.0;
    CGEventFlags flags = CGEventGetFlags(event);

    switch (type) {
        case kCGEventKeyDown: {
            //按键按下
            sendKeyEvent(self, keyCode,
                         flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                         flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand, KeyboardEventType::PRESS);
            break;
        }
        case kCGEventKeyUp: {
            //按键释放
            sendKeyEvent(self, keyCode,
                         flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                         flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                         KeyboardEventType::RELEASE);
            sendKeyEvent(self, keyCode,
                         flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                         flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                         KeyboardEventType::PRESSED);
        }
        case kCGEventFlagsChanged: {
            //控制键状态改变
            if (flags & kCGEventFlagMaskCommand ||  //command
                flags & kCGEventFlagMaskAlternate ||    //alt(option)
                flags & kCGEventFlagMaskShift ||            //shift
                flags & kCGEventFlagMaskControl         //ctrl
                    ) {
                //发送按下事件
                sendKeyEvent(self, keyCode,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             KeyboardEventType::PRESS);
                //添加到按下列表
                controlsCode.push_back(keyCode);
            } else {
                //控制键释放

                auto it = std::find(controlsCode.begin(), controlsCode.end(), keyCode);
                //在控制键按下列表中查询（防止常规按键复触发）
                if (it != controlsCode.end()) {
                    long index = distance(controlsCode.begin(), it);
                    controlsCode.erase(controlsCode.begin() + index, controlsCode.begin() + index + 1);
                    sendKeyEvent(self, keyCode,
                                 flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                                 flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                                 KeyboardEventType::RELEASE);
                    sendKeyEvent(self, keyCode,
                                 flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                                 flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                                 KeyboardEventType::PRESSED);
                }
            }
            break;
        }

            //以下为鼠标事件
        case kCGEventLeftMouseDown: {
            //鼠标左键按下 code set 1
            sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::PRESS);
            break;
        }

        case kCGEventLeftMouseUp: {
            //鼠标左键释放
            sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::RELEASE);
            sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::CLICKED);

            auto it = std::find(dragsCode.begin(), dragsCode.end(), 1);
            if (it != dragsCode.end()) {
                //如果拖动列表中含有此按键，擦除并发送拖动完成事件
                long index = distance(dragsCode.begin(), it);
                dragsCode.erase(dragsCode.begin() + index, dragsCode.begin() + index + 1);
                sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y,
                                 flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                                 flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                                 PointerEventType::DRAGGED);
            }
            break;
        }

        case kCGEventRightMouseDown: {
            //鼠标右键按下 code set 2
            sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::PRESS);
            break;
        }
        case kCGEventRightMouseUp: {
            //右键释放
            sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::RELEASE);
            sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::CLICKED);
            auto it = std::find(dragsCode.begin(), dragsCode.end(), 2);
            if (it != dragsCode.end()) {
                //如果拖动列表中含有此按键，擦除并发送拖动完成事件
                long index = distance(dragsCode.begin(), it);
                dragsCode.erase(dragsCode.begin() + index, dragsCode.begin() + index + 1);
                sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y,
                                 flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                                 flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                                 PointerEventType::DRAGGED);
            }
            break;
        }
        case kCGEventMouseMoved: {
            //鼠标移动
            sendPointerEvent(self, 0, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::MOVE);
            break;
        }
        case kCGEventLeftMouseDragged: {
            //左键拖动
            sendPointerEvent(self, 1, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::DRAG);
            auto it = std::find(dragsCode.begin(), dragsCode.end(), 1);
            if (it == dragsCode.end()) dragsCode.push_back(1);//拖动列表中不包含时加入
            break;
        }
        case kCGEventRightMouseDragged: {
            //右键拖动
            sendPointerEvent(self, 2, mouseLocation.x, mouseLocation.y,
                             flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                             flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                             PointerEventType::DRAG);
            auto it = std::find(dragsCode.begin(), dragsCode.end(), 2);
            if (it == dragsCode.end()) dragsCode.push_back(2);//拖动列表中不包含时加入
            break;
        }
        case kCGEventScrollWheel: {
            //可以发送滚动事件
            sendWheelEvent(self, fixedPtDeltaX, fixedPtDeltaY, accumulatedDeltaX, accumulatedDeltaY,
                           flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                           flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                           PointerWheelEventType::SCROLL);
            //滚轮滚动
            switch (scrollPhase) {
                case kCGScrollPhaseBegan: {
                    // 滚动开始
                    accumulatedDeltaY = 0.0;
                    accumulatedDeltaX = 0.0;
                    break;
                }
                case kCGScrollPhaseChanged: {
                    // 滚动变化
                    accumulatedDeltaY += fixedPtDeltaY;
                    accumulatedDeltaX += fixedPtDeltaX;
                    break;
                }
                case kCGScrollPhaseEnded:
                case kCGMomentumScrollPhaseEnd: {
                    // 滚动结束
                    sendWheelEvent(self, fixedPtDeltaX, fixedPtDeltaY, accumulatedDeltaX, accumulatedDeltaY,
                                   flags & kCGEventFlagMaskShift, flags & kCGEventFlagMaskControl,
                                   flags & kCGEventFlagMaskAlternate, flags & kCGEventFlagMaskCommand,
                                   PointerWheelEventType::SCROLLED);
                    break;
                }
                default:
                    break;
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
}

void GlobalScreen::clickedMouse(CGPoint &point, CGMouseButton &button, long timeContinued) {
    triggerMouse(kCGEventLeftMouseDown, point, button);
    if (timeContinued)
        usleep(timeContinued); // 睡眠
    triggerMouse(kCGEventLeftMouseUp, point, button);
}

void GlobalScreen::moveMouse(CGPoint &point) {
    triggerMouse(kCGEventMouseMoved, point, kCGMouseButtonLeft);
}

void GlobalScreen::triggerMouse(CGEventType mouseEventType, CGPoint &point, CGMouseButton button) {
    // 创建一个鼠标事件
    CGEventRef event = CGEventCreateMouseEvent(
            nullptr, // NULL = kCGNullDirectDisplay
            mouseEventType, // 鼠标移动事件
            point,
            button // 鼠标按键
    );
    // 发送鼠标事件
    CGEventPost(kCGHIDEventTap, event);
    // 释放事件对象
    CFRelease(event);
}
















