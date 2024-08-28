//
// Created by 2333 xiang on 2024/8/27.
//

#ifndef PTR_TOOLS_COORDINATE_H
#define PTR_TOOLS_COORDINATE_H

#include <type_traits>

template<class T>
class Coordinate {
public:
    Coordinate(T xVal, T yVal) : x(xVal), y(yVal) {
        static_assert(std::is_same<T, int>::value || std::is_same<T, double>::value, "Type must be int or double");
    };

    Coordinate() : x(0), y(0) {
        static_assert(std::is_same<T, int>::value || std::is_same<T, double>::value, "Type must be int or double");
    }

    T x;
    T y;
};

#endif //PTR_TOOLS_COORDINATE_H
