//
// Created by 2333 xiang on 2024/8/27.
//

#ifndef PTR_TOOLS_POINTERMOTIONLISTENER_H
#define PTR_TOOLS_POINTERMOTIONLISTENER_H

#include "../event/PointerEvent.h"

class PointerMotionListener{
public:
    //键盘按下
    virtual void onMove(const PointerEvent &e) = 0;

    //键盘释放
    virtual void onDrag(const PointerEvent &e) = 0;

    virtual ~PointerMotionListener()=default;
};
#endif //PTR_TOOLS_POINTERMOTIONLISTENER_H
