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

add_executable(ptr_tools main.cpp Example.h macos/pointer/PointerEventType.h macos/keyboard/KeyboardEventType.h macos/pointer/PointerMoveEventType.h macos/GlobalScreen.h macos/keyboard/event/KeyboardEvent.h macos/keyboard/listener/KeyboardListener.h macos/keyboard/KeyEventDispatcher.h)
target_link_libraries(ptr_tools
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

