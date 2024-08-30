//
// Created by 2333 xiang on 2024/8/26.
//

#ifndef PTR_TOOLS_GLOBALSCREEN_H
#define PTR_TOOLS_GLOBALSCREEN_H

#include <ApplicationServices/ApplicationServices.h>
#include "keyboard/dispatcher/KeyEventDispatcher.h"
#include "pointer/dispatcher/PointerEventDispatcher.h"
#include "pointer/dispatcher/WheelEventDispatcher.h"
#include <iostream>
#include <thread>

class GlobalScreen {
public:
    static GlobalScreen globalScreenVal;
    static std::vector<int> controlsCode;
    static std::vector<int> dragsCode;

    //开始监听
    static void startListen();

    //注册监听
    void init();

    //取消注册
    void unRegisterCoreGraphics();

    //添加按键监听器
    void addKeyListener(KeyboardListener &listener);

    //删除按键监听器
    void removeKeyListener(KeyboardListener &listener);

    //添加鼠标指针监听器
    void addPointerListener(PointerListener &listener);

    //删除鼠标指针监听器
    void removePointerListener(PointerListener &listener);

    //添加鼠标指针监听器
    void addPointerMotionListener(PointerMotionListener &listener);

    //删除鼠标指针监听器
    void removePointerMotionListener(PointerMotionListener &listener);

    //添加鼠标指针监听器
    void addPointerWheelListener(PointerWheelListener &listener);

    //删除鼠标指针监听器
    void removePointerWheelListener(PointerWheelListener &listener);

private:
    //滚轮滚动事件分派器
    WheelEventDispatcher wheelEventDispatcher;
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
    static void open();

    // 静态回调函数
    static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

    //发送键盘事件
    static void sendKeyEvent(GlobalScreen *s, int code,bool isShiftDown, bool isControlDown, bool isOptionDown, bool isCommandDown, KeyboardEventType t);

    //发送指针事件（无需精确）
    static void sendPointerEvent(GlobalScreen *s, int code, int x, int y,bool isShiftDown, bool isControlDown, bool isOptionDown, bool isCommandDown, PointerEventType t);

    //发送指针事件
    static void sendPointerEvent(GlobalScreen *s, int code, double x, double y,bool isShiftDown, bool isControlDown, bool isOptionDown, bool isCommandDown, PointerEventType t);

    //发送滚轮滚动事件
    static void sendWheelEvent(GlobalScreen *s, double dx, double dy, double sx, double sy,bool isShiftDown, bool isControlDown, bool isOptionDown, bool isCommandDown, PointerWheelEventType t);
};

#endif //PTR_TOOLS_GLOBALSCREEN_H
