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
    PointerEventDispatcher() =default;

    //添加鼠标指针监听器
    void addPointerListener(PointerListener &listener) {
        pointerListeners.push_back(&listener);
    }

    //添加鼠标指针运动监听器
    void addPointerMotionListener(PointerMotionListener &listener) {
        motionListeners.push_back(&listener);
    }

    //分派事件
    void dispatchEvent(const PointerEvent &event) const {
        switch (event.getEventType()) {
            case PointerEventType::PRESS: {
                // 类型为按下
                for (PointerListener *listener: pointerListeners) listener->onPress(event);
                break;
            }

            case PointerEventType::RELEASE: {
                //类型为松开
                for (PointerListener *listener: pointerListeners) listener->onRelease(event);
                break;
            }

            case PointerEventType::CLICKED: {
                //类型为点击
                for (PointerListener *listener: pointerListeners) listener->onClicked(event);
                break;
            }

            case PointerEventType::DRAGGED: {
                //类型为拖动完成

                break;
            }

            case PointerEventType::MOVE: {
                //类型为移动
                for (PointerMotionListener *listener: motionListeners) listener->onMove(event);
                break;
            }

            case PointerEventType::DRAG: {
                //类型为拖动
                for (PointerMotionListener *listener: motionListeners) listener->onDrag(event);
                break;
            }
        }
    }

    //删除鼠标指针监听器
    void removePointerListener(PointerListener *listener) {
        pointerListeners.erase(remove(pointerListeners.begin(), pointerListeners.end(), listener), pointerListeners.end());
        delete listener;
        listener = nullptr;
    }

    //删除鼠标指针监听器
    void removePointerMotionListener(PointerMotionListener *listener) {
        motionListeners.erase(remove(motionListeners.begin(), motionListeners.end(), listener), motionListeners.end());
        delete listener;
        listener = nullptr;
    }

private:
    std::vector<PointerListener *> pointerListeners;

    std::vector<PointerMotionListener *> motionListeners;
};

#endif //PTR_TOOLS_POINTEVENTDISPATCHER_H
