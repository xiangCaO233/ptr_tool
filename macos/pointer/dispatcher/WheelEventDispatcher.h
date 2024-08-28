//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef PTR_TOOLS_WHEELEVENTDISPATCHER_H
#define PTR_TOOLS_WHEELEVENTDISPATCHER_H
#include "../listener/PointerWheelListener.h"
#include <vector>

class WheelEventDispatcher{
public:
    //构造(初始化)
    WheelEventDispatcher() =default;

    //添加鼠标指针监听器
    void addPointerWheelListener(PointerWheelListener &listener);

    //分派事件
    void dispatchEvent(const PointerWheelEvent &event) const ;

    //删除鼠标指针监听器
    void removePointerWheelListener(PointerWheelListener *listener);

private:
    std::vector<PointerWheelListener *> listeners;
};
#endif //PTR_TOOLS_WHEELEVENTDISPATCHER_H
