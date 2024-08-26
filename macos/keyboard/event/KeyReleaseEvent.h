//
// Created by 2333 xiang on 2024/8/26.
// 按键释放事件
//
#include "KeyboardEvent.h"

#ifndef PTR_TOOLS_KEYRELEASEEVENT_H
#define PTR_TOOLS_KEYRELEASEEVENT_H

class KeyReleaseEvent : public KeyboardEvent {
public:
    //构造
    explicit KeyReleaseEvent(int rawCode) : KeyboardEvent(rawCode, KeyboardEventType::RELEASE) {};

};

#endif //PTR_TOOLS_KEYRELEASEEVENT_H
