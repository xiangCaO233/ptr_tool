//
// Created by 2333 xiang on 2024/8/26.
// 键盘监听器
//

#ifndef PTR_TOOLS_KEYBOARDLISTENER_H
#define PTR_TOOLS_KEYBOARDLISTENER_H

#include "../event/KeyboardEvent.h"

class KeyboardListener {
public:
    //键盘按下
    virtual void onPress(const KeyboardEvent &e) = 0;

    //键盘释放
    virtual void onRelease(const KeyboardEvent &e) = 0;

    //键盘按了
    virtual void onPressed(const KeyboardEvent &e) = 0;

    virtual ~KeyboardListener()=default;
};

#endif //PTR_TOOLS_KEYBOARDLISTENER_H
