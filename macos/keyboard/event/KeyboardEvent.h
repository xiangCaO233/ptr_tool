//
// Created by 2333 xiang on 2024/8/26.
//  按键事件
//


#ifndef PTR_TOOLS_KEYBOARDEVENT_H
#define PTR_TOOLS_KEYBOARDEVENT_H

#include "eventtype/KeyboardEventType.h"

class KeyboardEvent {
public:
    //构造
    KeyboardEvent(
            int rawCode,
            bool isShiftDown, bool isControlDown, bool isAltDown, bool isCommandDown,
            KeyboardEventType type)
            : raw_keycode(rawCode), eventType(type),
              isShift(isShiftDown), isControl(isControlDown), isAlt(isAltDown), isCommand(isCommandDown) {};

    //虚析构（标记继承）
    virtual ~KeyboardEvent() = default;

    //获取键值
    [[nodiscard]] int getRawKeyCode() const {
        return raw_keycode;
    }

    [[nodiscard]] bool isShiftDown() const { return isShift; };

    [[nodiscard]] bool isControlDown() const { return isControl; };

    [[nodiscard]] bool isAltDown() const { return isAlt; };

    [[nodiscard]] bool isCommandDown() const { return isCommand; };

    //获取类型
    [[nodiscard]] KeyboardEventType getEventType() const {
        return eventType;
    }

private:
    //原始键值
    int raw_keycode;
    bool isShift;
    bool isControl;
    bool isAlt;
    bool isCommand;

    //事件类型
    KeyboardEventType eventType;
};

#endif //PTR_TOOLS_KEYBOARDEVENT_H
