//
// Created by 2333 xiang on 2024/8/25.
// CF使用示例
//

#include <ApplicationServices/ApplicationServices.h>
#include <iostream>

#ifndef PTR_TOOLS_GLOBALLISTENER_H
#define PTR_TOOLS_GLOBALLISTENER_H


class Example {
public:
    Example(): eventTap(nullptr), runLoopSource(nullptr), isRunning(false) {
        setupEventTap();
    };   // 构造函数
    ~Example(){
        stop();
        releaseEventTap();
    };  // 析构函数

    void start(){
        if (!eventTap || isRunning) return;

        // 添加源到运行循环
        CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

        // 启动事件监听
        CGEventTapEnable(eventTap, true);
        isRunning = true;

        // 运行事件循环
        CFRunLoopRun();
    };      // 启动事件监听
    void stop(){
        if (!isRunning) return;

        // 停止事件循环
        CFRunLoopStop(CFRunLoopGetCurrent());
        isRunning = false;
    };       // 停止事件监听

private:
    // 静态回调函数
    static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon){
        auto* self = static_cast<Example*>(refcon);

        if (type == kCGEventKeyDown || type == kCGEventFlagsChanged) {
            auto keyCode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
            std::cout << "Key Event: " << keyCode << std::endl;

            // 检测修饰键的状态
            CGEventFlags flags = CGEventGetFlags(event);
            if (flags & kCGEventFlagMaskCommand) {
                std::cout << "Command key is pressed" << std::endl;
            }
            if (flags & kCGEventFlagMaskAlternate) {
                std::cout << "Option key is pressed" << std::endl;
            }
            if (flags & kCGEventFlagMaskShift) {
                std::cout << "Shift key is pressed" << std::endl;
            }
            if (flags & kCGEventFlagMaskControl) {
                std::cout << "Control key is pressed" << std::endl;
            }
        } else if (type == kCGEventMouseMoved) {
            CGPoint mouseLocation = CGEventGetLocation(event);
            std::cout << "Mouse Moved: x = " << mouseLocation.x << ", y = " << mouseLocation.y << std::endl;
        } else if (type == kCGEventLeftMouseDown) {
            std::cout << "Left Mouse Button Down" << std::endl;
        } else if (type == kCGEventRightMouseDown) {
            std::cout << "Right Mouse Button Down" << std::endl;
        } else if (type == kCGEventScrollWheel) {
            int64_t scrollDelta = CGEventGetIntegerValueField(event, kCGScrollWheelEventDeltaAxis1);
            std::cout << "Scroll Wheel Event: delta = " << scrollDelta << std::endl;
        }

        return event; // 必须返回事件
    };

    // 设置事件监听器
    void setupEventTap(){
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
            std::cerr << "Failed to create event tap" << std::endl;
            return;
        }

        // 创建运行循环源
        runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    };

    // 释放事件监听器
    void releaseEventTap(){
        if (runLoopSource) {
            CFRelease(runLoopSource);
            runLoopSource = nullptr;
        }
        if (eventTap) {
            CFRelease(eventTap);
            eventTap = nullptr;
        }
    };

    CFMachPortRef eventTap;
    CFRunLoopSourceRef runLoopSource;
    bool isRunning;
};



#endif //PTR_TOOLS_GLOBALLISTENER_H
