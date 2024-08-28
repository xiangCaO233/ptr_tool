//
// Created by 2333 xiang on 2024/8/26.
//  键盘事件分派器
//

#ifndef PTR_TOOLS_POINTEVENTDISPATCHER_H
#define PTR_TOOLS_POINTEVENTDISPATCHER_H

#include <vector>
#include "../listener/PointerListener.h"
#include "../listener/PointerMotionListener.h"

class PointerEventDispatcher {
public:
    //构造(初始化)
    PointerEventDispatcher() = default;

    //添加鼠标指针监听器
    void addPointerListener(PointerListener &listener);

    //添加鼠标指针运动监听器
    void addPointerMotionListener(PointerMotionListener &listener);

    //分派事件
    void dispatchEvent(const PointerEvent &event) const;

    //删除鼠标指针监听器
    void removePointerListener(PointerListener *listener);

    //删除鼠标指针监听器
    void removePointerMotionListener(PointerMotionListener *listener);

private:
    std::vector<PointerListener *> pointerListeners;

    std::vector<PointerMotionListener *> motionListeners;
};

#endif //PTR_TOOLS_POINTEVENTDISPATCHER_H
