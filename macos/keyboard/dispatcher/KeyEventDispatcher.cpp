//
// Created by 2333 xiang on 2024/8/28.
//
#include "KeyEventDispatcher.h"

void KeyEventDispatcher::addKeyListener(KeyboardListener &listener) {
    listeners.push_back(&listener);
}

void KeyEventDispatcher::dispatchEvent(const KeyboardEvent &event) const {
    switch (event.getEventType()) {
        case KeyboardEventType::PRESS: {
            // 类型为按下
            for (KeyboardListener *listener: listeners) listener->onPress(event);
            break;
        }

        case KeyboardEventType::RELEASE: {
            //类型为松开
            for (KeyboardListener *listener: listeners) listener->onRelease(event);
            break;
        }

        case KeyboardEventType::PRESSED: {
            //类型为按了
            for (KeyboardListener *listener: listeners) listener->onPressed(event);
            break;
        }
    }
}

void KeyEventDispatcher::removeKeyListener(KeyboardListener *listener) {
    listeners.erase(remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

