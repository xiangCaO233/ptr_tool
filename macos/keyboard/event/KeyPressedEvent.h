//
// Created by 2333 xiang on 2024/8/26.
// 键盘按了事件
//

#ifndef PTR_TOOLS_KEYPRESSEDEVENT_H
#define PTR_TOOLS_KEYPRESSEDEVENT_H

#include "KeyboardEvent.h"

class KeyPressedEvent : public KeyboardEvent {
public:
    //构造
    explicit KeyPressedEvent(int rawCode) : KeyboardEvent(rawCode, KeyboardEventType::PRESSED) {};

};

#endif //PTR_TOOLS_KEYPRESSEDEVENT_H
