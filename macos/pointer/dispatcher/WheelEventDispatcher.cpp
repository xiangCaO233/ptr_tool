//
// Created by 2333 xiang on 2024/8/28.
//

#include "WheelEventDispatcher.h"

void WheelEventDispatcher::addPointerWheelListener(PointerWheelListener &listener) {
    listeners.push_back(&listener);
}

void WheelEventDispatcher::dispatchEvent(const PointerWheelEvent &event) const {
    switch (event.getEventType()) {
        case PointerWheelEventType::SCROLL: {
            // 类型为滚动
            for (PointerWheelListener *listener: listeners) listener->onScroll(event);
            break;
        }
        case PointerWheelEventType::SCROLLED: {
            //类型为滚动完成
            for (PointerWheelListener *listener: listeners) listener->onScrolled(event);
            break;
        }
    }
}

void WheelEventDispatcher::removePointerWheelListener(PointerWheelListener *listener) {
    listeners.erase(remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

