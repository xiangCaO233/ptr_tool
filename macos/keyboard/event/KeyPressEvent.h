//
// Created by 2333 xiang on 2024/8/26.
// 键盘按下事件
//
#include "KeyboardEvent.h"

#ifndef PTR_TOOLS_KEYPRESSEVENT_H
#define PTR_TOOLS_KEYPRESSEVENT_H

class KeyPressEvent : public KeyboardEvent {
public:
    //构造
    explicit KeyPressEvent(int rawCode) : KeyboardEvent(rawCode, KeyboardEventType::PRESS) {};

};

#endif //PTR_TOOLS_KEYPRESSEVENT_H
