//
// Created by 2333 xiang on 2024/8/27.
//

#ifndef PTR_TOOLS_POINTEREVENT_H
#define PTR_TOOLS_POINTEREVENT_H

#include "eventtype/PointerEventType.h"
#include "../Coordinate.h"

class PointerEvent {
public:
    //构造
    PointerEvent(int rawCode,int x,int y, PointerEventType type) : button(rawCode), eventType(type), coordinate(x,y) {};

    PointerEvent(int rawCode,double x,double y, PointerEventType type) : button(rawCode), eventType(type), coordinate(x,y) {};

    //虚析构（标记继承）
    virtual ~PointerEvent() = default;

    //获取键值
    [[nodiscard]] int getButton() const {
        return button;
    }

    //获取坐标
    [[nodiscard]] Coordinate<double> getCoordinate() const {
        return coordinate;
    }

    //获取类型
    [[nodiscard]] PointerEventType getEventType() const {
        return eventType;
    }

private:
    //鼠标按键
    int button;

    Coordinate<double> coordinate;

    //事件类型
    PointerEventType eventType;
};
#endif //PTR_TOOLS_POINTEREVENT_H
