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
    KeyEventDispatcher() = default;

    //添加监听器
    void addKeyListener(KeyboardListener &listener);

    //分派事件
    void dispatchEvent(const KeyboardEvent &event) const;

    //删除监听器
    void removeKeyListener(KeyboardListener *listener);

private:
    std::vector<KeyboardListener *> listeners;
};

#endif //PTR_TOOLS_KEYEVENTDISPATCHER_H
