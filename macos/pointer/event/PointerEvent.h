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
    PointerEvent(
            int rawCode, int x, int y,
            bool isShiftDown, bool isControlDown, bool isAltDown, bool isCommandDown,
            PointerEventType type)
            : button(rawCode), eventType(type), coordinate(x, y),
              isShift(isShiftDown), isControl(isControlDown), isAlt(isAltDown), isCommand(isCommandDown) {};

    PointerEvent(
            int rawCode, double x, double y,
            bool isShiftDown, bool isControlDown, bool isOptionDown, bool isCommandDown,
            PointerEventType type)
            : button(rawCode), eventType(type), coordinate(x, y),
              isShift(isShiftDown), isControl(isControlDown), isAlt(isOptionDown), isCommand(isCommandDown) {};

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

    [[nodiscard]] bool isShiftDown() const { return isShift; };

    [[nodiscard]] bool isControlDown() const { return isControl; };

    [[nodiscard]] bool isAltDown() const { return isAlt; };

    [[nodiscard]] bool isCommandDown() const { return isCommand; };

    //获取类型
    [[nodiscard]] PointerEventType getEventType() const {
        return eventType;
    }

private:
    //鼠标按键
    int button;
    Coordinate<double> coordinate;
    bool isShift;
    bool isControl;
    bool isAlt;
    bool isCommand;

    //事件类型
    PointerEventType eventType;
};

#endif //PTR_TOOLS_POINTEREVENT_H
