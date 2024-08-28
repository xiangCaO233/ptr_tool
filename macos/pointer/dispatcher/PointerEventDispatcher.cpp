//
// Created by 2333 xiang on 2024/8/28.
//
#include "PointerEventDispatcher.h"

void PointerEventDispatcher::addPointerListener(PointerListener &listener) {
    pointerListeners.push_back(&listener);
}

void PointerEventDispatcher::addPointerMotionListener(PointerMotionListener &listener) {
    motionListeners.push_back(&listener);
}

void PointerEventDispatcher::dispatchEvent(const PointerEvent &event) const {
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
            for (PointerListener *listener: pointerListeners) listener->onDragged(event);
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

void PointerEventDispatcher::removePointerListener(PointerListener *listener) {
    pointerListeners.erase(remove(pointerListeners.begin(), pointerListeners.end(), listener), pointerListeners.end());
}

void PointerEventDispatcher::removePointerMotionListener(PointerMotionListener *listener) {
    motionListeners.erase(remove(motionListeners.begin(), motionListeners.end(), listener), motionListeners.end());
}

