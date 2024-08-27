//
// Created by 2333 xiang on 2024/8/26.
//鼠标指针事件类型
//

#ifndef POINTER_EVENT_TYPE_H
#define POINTER_EVENT_TYPE_H

enum class PointerEventType {
    PRESS,          //按下(id:0)
    RELEASE,    //释放(id:1)
    CLICKED,    //点击(id:2)
    DRAGGED,    //点击(id:2)
    MOVE,          //移动(id:3)
    DRAG            //拖动(id:4)
};
#endif //POINTER_EVENT_TYPE_H
