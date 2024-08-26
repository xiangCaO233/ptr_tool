//
// Created by 2333 xiang on 2024/8/26.
//鼠标指针事件类型
//

#ifndef PTR_TOOLS_POINTEREVENTTYPE_H
#define PTR_TOOLS_POINTEREVENTTYPE_H
enum class PointerEventType{
    PRESS,          //按下(id:0)
    RELEASE,    //释放(id:1)
    CLICKED,    //点击(id:2)
    SCROLL       //滚动(id:3)
};
#endif //PTR_TOOLS_POINTEREVENTTYPE_H
