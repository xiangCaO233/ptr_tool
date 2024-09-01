cmake_minimum_required(VERSION 3.10)
project(GlobalScreenLibrary)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加库的源文件
set(SOURCES
        keyboard/dispatcher/KeyEventDispatcher.cpp
        pointer/dispatcher/PointerEventDispatcher.cpp
        pointer/dispatcher/WheelEventDispatcher.cpp
        GlobalScreen.cpp
        keyboard/KeyMaps.h)

# 添加库的头文件目录
include_directories(
        keyboard/dispatcher
        keyboard/event
        keyboard/event/eventtype
        keyboard/listener
        pointer/dispatcher
        pointer/event
        pointer/event/eventtype
        pointer/listener
)

# 添加动态库目标
add_library(GlobalScreenLibrary SHARED ${SOURCES})

# 链接 CoreFoundation 和 CoreGraphics 框架
target_link_libraries(GlobalScreenLibrary
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        )

# 设置编译输出目录
set_target_properties(GlobalScreenLibrary PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        )
