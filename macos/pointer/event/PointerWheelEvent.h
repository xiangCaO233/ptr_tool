//
// Created by 2333 xiang on 2024/8/28.
//

#ifndef PTR_TOOLS_POINTERWHEELEVENT_H
#define PTR_TOOLS_POINTERWHEELEVENT_H

#include "eventtype/PointerWheelEventType.h"

class PointerWheelEvent {
public:
    //构造
    PointerWheelEvent(
            double deltaX, double deltaY, double sumX, double sumY,
            bool isShiftDown, bool isControlDown, bool isAltDown, bool isCommandDown,
            PointerWheelEventType eventType)
            : dx(deltaX), dy(deltaY), sx(sumX), sy(sumY), type(eventType),
              isShift(isShiftDown), isControl(isControlDown), isAlt(isAltDown), isCommand(isCommandDown) {};

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

    [[nodiscard]] bool isShiftDown() const { return isShift; };

    [[nodiscard]] bool isControlDown() const { return isControl; };

    [[nodiscard]] bool isAltDown() const { return isAlt; };

    [[nodiscard]] bool isCommandDown() const { return isCommand; };

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
    bool isShift;
    bool isControl;
    bool isAlt;
    bool isCommand;

    PointerWheelEventType type;
};

#endif //PTR_TOOLS_POINTERWHEELEVENT_H
