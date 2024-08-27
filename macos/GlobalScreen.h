//
// Created by 2333 xiang on 2024/8/26.
//

#ifndef PTR_TOOLS_GLOBALSCREEN_H
#define PTR_TOOLS_GLOBALSCREEN_H
#include <ApplicationServices/ApplicationServices.h>
#include "keyboard/KeyEventDispatcher.h"
#include "iostream"
class GlobalScreen{
public:
    //注册监听
    void registerCoreGraphics(){
        // 创建事件监听器
        eventTap = CGEventTapCreate(
                kCGSessionEventTap, // 监听范围：全局
                kCGHeadInsertEventTap, // 插入位置：头部
                kCGEventTapOptionDefault, // 选项
                CGEventMaskBit(kCGEventKeyDown) |
                CGEventMaskBit(kCGEventFlagsChanged) |
                CGEventMaskBit(kCGEventMouseMoved) |
                CGEventMaskBit(kCGEventLeftMouseDown) |
                CGEventMaskBit(kCGEventRightMouseDown) |
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
    void unRegisterCoreGraphics(){
        if (!isRunning) return;

        // 停止事件循环
        CFRunLoopStop(CFRunLoopGetCurrent());
        isRunning = false;
    }

    //添加监听器
    void addKeyListener(KeyboardListener &listener) {
        dispatcher.addKeyListener(listener);
    }

    //删除监听器
    void removeKeyListener(KeyboardListener &listener) {
        dispatcher.removeKeyListener(&listener);
    }


private:
    KeyEventDispatcher dispatcher;
    //事件监听器
    CFMachPortRef eventTap;
    //行循环源
    CFRunLoopSourceRef runLoopSource;
    //运行标志符
    bool isRunning;

    // 静态回调函数
    static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon){
        auto* self = static_cast<GlobalScreen*>(refcon);

        if (type == kCGEventKeyDown || type == kCGEventFlagsChanged) {

            auto keyCode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
            //std::cout << "Key Event: " << keyCode << std::endl;

            auto e = KeyboardEvent(keyCode,KeyboardEventType::PRESSED);
            self->dispatcher.dispatchEvent(e);


            // 检测修饰键的状态
            CGEventFlags flags = CGEventGetFlags(event);
            if (flags & kCGEventFlagMaskCommand) {
//                std::cout << "Command key is pressed" << std::endl;
            }
            if (flags & kCGEventFlagMaskAlternate) {
//                std::cout << "Option key is pressed" << std::endl;
            }
            if (flags & kCGEventFlagMaskShift) {
//                std::cout << "Shift key is pressed" << std::endl;
            }
            if (flags & kCGEventFlagMaskControl) {
//                std::cout << "Control key is pressed" << std::endl;
            }
        } else if (type == kCGEventMouseMoved) {
            CGPoint mouseLocation = CGEventGetLocation(event);
//            std::cout << "Mouse Moved: x = " << mouseLocation.x << ", y = " << mouseLocation.y << std::endl;
        } else if (type == kCGEventLeftMouseDown) {
//            std::cout << "Left Mouse Button Down" << std::endl;
        } else if (type == kCGEventRightMouseDown) {
//            std::cout << "Right Mouse Button Down" << std::endl;
        } else if (type == kCGEventScrollWheel) {
            int64_t scrollDelta = CGEventGetIntegerValueField(event, kCGScrollWheelEventDeltaAxis1);
//            std::cout << "Scroll Wheel Event: delta = " << scrollDelta << std::endl;
        }

        return event; // 必须返回事件
    };
};
#endif //PTR_TOOLS_GLOBALSCREEN_H
