//
// Created by 2333 xiang on 2024/8/26.
//  键盘事件分派器
//

#ifndef PTR_TOOLS_KEYEVENTDISPATCHER_H
#define PTR_TOOLS_KEYEVENTDISPATCHER_H

#include "listener/KeyboardListener.h"
#include "vector"

using namespace std;

class KeyEventDispatcher {
public:
    //构造(初始化)
    KeyEventDispatcher() : listeners(vector<KeyboardListener *>()) {};

    //添加监听器
    void addKeyListener(KeyboardListener &listener) {
        listeners.push_back(&listener);
    }

    //分派事件
    void dispatchEvent(const KeyboardEvent &event) const {
        switch (event.getEventType()) {
            case KeyboardEventType::PRESS: {
                // 类型为按下
                if (auto e = dynamic_cast<const KeyPressEvent*>(&event)) for (KeyboardListener *listener : listeners) listener->onPress(*e);
                break;
            }

            case KeyboardEventType::RELEASE: {
                //类型为松开
                if (auto e = dynamic_cast<const KeyReleaseEvent*>(&event)) for (KeyboardListener *listener : listeners) listener->onRelease(*e);
                break;
            }

            case KeyboardEventType::PRESSED: {
                //类型为按了
                if (auto e = dynamic_cast<const KeyPressedEvent*>(&event)) for (KeyboardListener *listener : listeners) listener->onPressed(*e);
                break;
            }
        }
    }

    //删除监听器
    void removeKeyListener(KeyboardListener *listener) {
        listeners.erase(remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

private:
    vector<KeyboardListener *> listeners;
};

#endif //PTR_TOOLS_KEYEVENTDISPATCHER_H
