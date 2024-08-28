//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef PTR_TOOLS_POINTERWHEELEVENT_H
#define PTR_TOOLS_POINTERWHEELEVENT_H

#include "eventtype/PointerWheelEventType.h"

class PointerWheelEvent {
public:
    //构造
    PointerWheelEvent(double deltaX, double deltaY, double sumX, double sumY, PointerWheelEventType eventType) :
            dx(deltaX), dy(deltaY), sx(sumX), sy(sumY), type(eventType) {};

    //虚析构（标记继承）
    virtual ~PointerWheelEvent() = default;

    [[nodiscard]] double getDx() const {
        return dx;
    }

    [[nodiscard]] double getDy() const {
        return dy;
    }

    [[nodiscard]] double getSx() const {
        return sx;
    }

    [[nodiscard]] double getSy() const {
        return sy;
    }

    [[nodiscard]] PointerWheelEventType getEventType() const {
        return type;
    }

private:
    //delta x
    double dx;
    //delta y
    double dy;
    //sum x
    double sx;
    //sum y
    double sy;
    PointerWheelEventType type;
};

#endif //PTR_TOOLS_POINTERWHEELEVENT_H
