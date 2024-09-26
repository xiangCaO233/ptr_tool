#ifndef GLOBALSCREEN_GLOBALSCREEN_H
#define GLOBALSCREEN_GLOBALSCREEN_H

#include "dispatcher/KeyEventDispatcher.h"
#include "dispatcher/MouseEventDispatcher.h"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CoreText.h>
#include <iostream>
#include <thread>

class GlobalScreen {
  // 事件派遣器
  static KeyEventDispatcher keyEventDispatcher;
  static MouseEventDispatcher mouseEventDispatcher;
  // 循环线程
  static std::thread loopThread;
  // api事件触
  static CFMachPortRef eventTap;
  // api循环源
  static CFRunLoopSourceRef runLoopSource;

public:
  // 注册全局钩子
  static void registerScreenHook();
  // api事件回调
  static CGEventRef callback(CGEventTapProxy proxy, CGEventType type,
                             CGEventRef event, void *refcon);
  // 添加按键监听器
  static void addKeyListener(KeyListener *listener);
  // 移除按键监听器
  static void removeKeyListener(KeyListener *listener);
  // 添加鼠标监听器
  static void addMouseListener(MouseListener *listener);
  // 移除鼠标监听器
  static void removeMouseListener(MouseListener *listener);
  // 停止捕获
  static void unRegisterScreenHook();
  // 获取按下按键的字符
  static const char *GetCharacterFromKeyCode(CGKeyCode keyCode,
                                             bool shiftPressed);
  // 发送按键事件到派遣器
  static void sendKeyEvent(CGKeyCode rawCode, const char *key,
                           KeyEventType type, Modifiers &modifiers);
  // 发送鼠标事件到派遣器
  static void sendMouseEvent(int button, MouseEventType type,
                             Modifiers &modifiers, CGPoint &location);
};

#endif // GLOBALSCREEN_GLOBALSCREEN_H
