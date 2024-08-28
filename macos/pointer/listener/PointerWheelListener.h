//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef PTR_TOOLS_POINTERWHEELLISTENER_H
#define PTR_TOOLS_POINTERWHEELLISTENER_H

#include "../event/PointerWheelEvent.h"

class PointerWheelListener{
public:
    //滚动
    virtual void onScroll(const PointerWheelEvent &e) = 0;

    //滚动完成
    virtual void onScrolled(const PointerWheelEvent &e) = 0;

    virtual ~PointerWheelListener()=default;
};
#endif //PTR_TOOLS_POINTERWHEELLISTENER_H
