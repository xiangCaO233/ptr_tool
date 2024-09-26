#include "../headers/GlobalScreen.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include <CoreGraphics/CoreGraphics.h>

KeyEventDispatcher GlobalScreen::keyEventDispatcher;
MouseEventDispatcher GlobalScreen::mouseEventDispatcher;

std::thread GlobalScreen::loopThread;

CFRunLoopSourceRef GlobalScreen::runLoopSource;
CFMachPortRef GlobalScreen::eventTap;

void GlobalScreen::registerScreenHook() {
  // 注册事件api
  eventTap = CGEventTapCreate(
      kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault,
      CGEventMaskBit(kCGEventKeyDown) |               // 键盘按下
          CGEventMaskBit(kCGEventKeyUp) |             // 键盘释放
          CGEventMaskBit(kCGEventFlagsChanged) |      // 捕获修饰键变化
          CGEventMaskBit(kCGEventLeftMouseDown) |     // 鼠标左键按下
          CGEventMaskBit(kCGEventLeftMouseUp) |       // 鼠标左键释放
          CGEventMaskBit(kCGEventRightMouseDown) |    // 鼠标右键按下
          CGEventMaskBit(kCGEventRightMouseUp) |      // 鼠标右键释放
          CGEventMaskBit(kCGEventOtherMouseDown) |    // 鼠标其他键按下
          CGEventMaskBit(kCGEventOtherMouseUp) |      // 鼠标其他键释放
          CGEventMaskBit(kCGEventLeftMouseDragged) |  // 鼠标左键拖动
          CGEventMaskBit(kCGEventRightMouseDragged) | // 鼠标右键拖动
          CGEventMaskBit(kCGEventOtherMouseDragged) | // 鼠标其他键拖动
          CGEventMaskBit(kCGEventMouseMoved),         // 鼠标移动
      callback,                                       // 事件回调
      NULL);

  if (!eventTap) {
    std::cout << "a?" << std::endl;
    return;
  }

  // 创建循环源
  runLoopSource =
      CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
                     kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  // 创建循环线程
  loopThread = std::thread(CFRunLoopRun);
  // 分离线程
  loopThread.detach();
}

CGEventRef GlobalScreen::callback(CGEventTapProxy proxy, CGEventType type,
                                  CGEventRef event, void *refcon) {
  // 获取按键码
  CGKeyCode keyCode =
      (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  // 获取原生修饰符
  CGEventFlags flags = (CGEventFlags)CGEventGetFlags(event);
  // 获取字符
  auto ks = GetCharacterFromKeyCode(keyCode, flags & kCGEventFlagMaskShift);
  // 获取鼠标位置
  CGPoint mouseLocation = CGEventGetLocation(event);
  // 初始化修饰符
  Modifiers modifiers;
  modifiers.shift = flags & kCGEventFlagMaskShift;
  modifiers.command = flags & kCGEventFlagMaskCommand;
  modifiers.control = flags & kCGEventFlagMaskControl;
  modifiers.option = flags & kCGEventFlagMaskAlternate;
  if (type == kCGEventMouseMoved) {
    // 鼠标运动
    sendMouseEvent(0, MouseEventType::MOVE, modifiers, mouseLocation);
  } else if (type == kCGEventLeftMouseDragged) {
    sendMouseEvent(1, MouseEventType::DRAG, modifiers, mouseLocation);
  } else if (type == kCGEventRightMouseDragged) {
    sendMouseEvent(2, MouseEventType::DRAG, modifiers, mouseLocation);
  } else if (type == kCGEventOtherMouseDragged) {
    sendMouseEvent(3, MouseEventType::DRAG, modifiers, mouseLocation);
  }
  // 处理键盘事件
  else if (type == kCGEventKeyDown) {
    // 按键按下
    // std::cout << "按键按下" << std::endl;
    sendKeyEvent(keyCode, ks, KeyEventType::PRESS, modifiers);
  } else if (type == kCGEventKeyUp) {
    // 按键释放
    sendKeyEvent(keyCode, ks, KeyEventType::RELEASE, modifiers);
    sendKeyEvent(keyCode, ks, KeyEventType::PRESSED, modifiers);
  } else if (type == kCGEventFlagsChanged) {
    //    std::cout << "修饰符变化" << std::endl;

    // 检查 Shift 键
    if (flags & kCGEventFlagMaskShift) {
      sendKeyEvent(keyCode, ks, KeyEventType::PRESS, modifiers);
    } else {
      sendKeyEvent(keyCode, ks, KeyEventType::RELEASE, modifiers);
      sendKeyEvent(keyCode, ks, KeyEventType::PRESSED, modifiers);
    }

    // 检查 Control 键
    if (flags & kCGEventFlagMaskControl) {
      sendKeyEvent(keyCode, ks, KeyEventType::PRESS, modifiers);
    } else {
      sendKeyEvent(keyCode, ks, KeyEventType::RELEASE, modifiers);
      sendKeyEvent(keyCode, ks, KeyEventType::PRESSED, modifiers);
    }

    // 检查 Option 键
    if (flags & kCGEventFlagMaskAlternate) {
      sendKeyEvent(keyCode, ks, KeyEventType::PRESS, modifiers);
    } else {
      sendKeyEvent(keyCode, ks, KeyEventType::RELEASE, modifiers);
      sendKeyEvent(keyCode, ks, KeyEventType::PRESSED, modifiers);
    }

    // 检查 Command 键
    if (flags & kCGEventFlagMaskCommand) {
      sendKeyEvent(keyCode, ks, KeyEventType::PRESS, modifiers);
    } else {
      sendKeyEvent(keyCode, ks, KeyEventType::RELEASE, modifiers);
      sendKeyEvent(keyCode, ks, KeyEventType::PRESSED, modifiers);
    }
  }
  // 处理鼠标事件
  else if (type == kCGEventLeftMouseDown) {
    sendMouseEvent(1, MouseEventType::PRESS, modifiers, mouseLocation);
  } else if (type == kCGEventLeftMouseUp) {
    sendMouseEvent(1, MouseEventType::RELEASE, modifiers, mouseLocation);
    sendMouseEvent(1, MouseEventType::PRESSED, modifiers, mouseLocation);
  } else if (type == kCGEventRightMouseDown) {
    sendMouseEvent(2, MouseEventType::PRESS, modifiers, mouseLocation);
  } else if (type == kCGEventRightMouseUp) {
    sendMouseEvent(1, MouseEventType::RELEASE, modifiers, mouseLocation);
    sendMouseEvent(1, MouseEventType::PRESSED, modifiers, mouseLocation);
  } else if (type == kCGEventOtherMouseDown) {
    sendMouseEvent(3, MouseEventType::PRESS, modifiers, mouseLocation);
  } else if (type == kCGEventOtherMouseUp) {
    sendMouseEvent(3, MouseEventType::RELEASE, modifiers, mouseLocation);
    sendMouseEvent(3, MouseEventType::PRESSED, modifiers, mouseLocation);
  }
  // 返回事件，允许事件继续传播
  return event;
}

void GlobalScreen::addKeyListener(KeyListener *listener) {
  keyEventDispatcher.addListener(listener);
}

void GlobalScreen::addMouseListener(MouseListener *listener) {
  mouseEventDispatcher.addListener(listener);
}

const char *GlobalScreen::GetCharacterFromKeyCode(CGKeyCode keycode,
                                                  bool shiftPressed) {
  if (shiftPressed) {
    return Mapping::shiftKeyMap.at(keycode);
  } else {
    return Mapping::normalKeyMap.at(keycode);
  }
}

void GlobalScreen::unRegisterScreenHook() {
  CFRelease(runLoopSource);
  CFRelease(eventTap);
}

void GlobalScreen::sendKeyEvent(CGKeyCode rawCode, const char *key,
                                KeyEventType type, Modifiers &modifiers) {

  auto e = new KeyEvent(rawCode, key, modifiers, type);
  keyEventDispatcher.dispachEvent(*e);
}

void GlobalScreen::sendMouseEvent(int button, MouseEventType type,
                                  Modifiers &modifiers, CGPoint &location) {
  auto e = new MouseEvent(button, modifiers, type, (int)location.x,
                          (int)location.y, location.x, location.y);
  mouseEventDispatcher.dispatchEvent(*e);
}
