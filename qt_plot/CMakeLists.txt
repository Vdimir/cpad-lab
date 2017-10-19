project(qtplot)

cmake_minimum_required(VERSION 3.2)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_cpp(MOC_WRAPPERS win_main.h set_range_dialog.h)
qt5_wrap_ui(UIC_WRAPPERS
    ui/main_window.ui
    ui/set_range_dialog.ui
    )

set(SRC_LIST
    main.cpp
    win_main.cpp
    set_range_dialog.cpp
    context.h
    function_to_plot.h
    ${UIC_WRAPPERS}
    ${MOC_WRAPPERS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(qtplot Qt5::Widgets)

