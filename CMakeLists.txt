cmake_minimum_required(VERSION 3.25)
project(ptr_tools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ptr_tools main.cpp macos/pointer/event/eventtype/PointerEventType.h macos/keyboard/event/eventtype/KeyboardEventType.h macos/GlobalScreen.h macos/keyboard/event/KeyboardEvent.h macos/keyboard/listener/KeyboardListener.h macos/keyboard/dispatcher/KeyEventDispatcher.h macos/GlobalScreen.cpp macos/pointer/event/eventtype/PointerWheelEventType.h macos/pointer/event/PointerEvent.h macos/pointer/listener/PointerListener.h macos/pointer/dispatcher/PointerEventDispatcher.h macos/pointer/Coordinate.h macos/pointer/listener/PointerMotionListener.h macos/pointer/event/PointerWheelEvent.h macos/pointer/listener/PointerWheelListener.h macos/pointer/dispatcher/WheelEventDispatcher.h)
target_link_libraries(ptr_tools
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
