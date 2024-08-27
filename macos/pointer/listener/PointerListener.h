//
// Created by 2333 xiang on 2024/8/27.
//

#ifndef PTR_TOOLS_POINTERLISTENER_H
#define PTR_TOOLS_POINTERLISTENER_H

#include "../event/PointerEvent.h"

class PointerListener {
public:
    //鼠标按下
    virtual void onPress(const PointerEvent &e) = 0;

    //鼠标释放
    virtual void onRelease(const PointerEvent &e) = 0;

    //鼠标点击
    virtual void onClicked(const PointerEvent &e) = 0;

    //键盘按了
    virtual void onDragged(const PointerEvent &e) = 0;

    virtual ~PointerListener()=default;
};

#endif //PTR_TOOLS_POINTERLISTENER_H
