//
// Created by 2333 xiang on 2024/8/26.
// 键盘监听器
//

#ifndef PTR_TOOLS_KEYBOARDLISTENER_H
#define PTR_TOOLS_KEYBOARDLISTENER_H

#include "../event/KeyPressEvent.h"
#include "../event/KeyReleaseEvent.h"
#include "../event/KeyPressedEvent.h"

class KeyboardListener {
public:
    //键盘按下
    virtual void onPress(const KeyPressEvent &e) = 0;

    //键盘释放
    virtual void onRelease(const KeyReleaseEvent &e) = 0;

    //键盘按了
    virtual void onPressed(const KeyPressedEvent &e) = 0;
};

#endif //PTR_TOOLS_KEYBOARDLISTENER_H
