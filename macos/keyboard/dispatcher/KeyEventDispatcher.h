//
// Created by 2333 xiang on 2024/8/26.
//  键盘事件分派器
//

#ifndef PTR_TOOLS_KEYEVENTDISPATCHER_H
#define PTR_TOOLS_KEYEVENTDISPATCHER_H

#include <vector>
#include "../listener/KeyboardListener.h"

class KeyEventDispatcher {
public:
    //构造(初始化)
    KeyEventDispatcher()=default;

    //添加监听器
    void addKeyListener(KeyboardListener &listener) {
        listeners.push_back(&listener);
    }

    //分派事件
    void dispatchEvent(const KeyboardEvent &event) const {
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

    //删除监听器
    void removeKeyListener(KeyboardListener *listener) {
        listeners.erase(remove(listeners.begin(), listeners.end(), listener), listeners.end());
        delete listener;
        listener = nullptr;
    }

private:
    std::vector<KeyboardListener *> listeners;
};

#endif //PTR_TOOLS_KEYEVENTDISPATCHER_H
