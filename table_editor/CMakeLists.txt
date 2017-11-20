project(CsvTableEditor)

cmake_minimum_required(VERSION 3.2)

find_package(Qt5Widgets REQUIRED)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_cpp(MOC_WRAPPERS
    tablemodel.h
    win/main_window.h
    combo-delegate.h
    )

qt5_wrap_ui(UIC_WRAPPERS
    ui/mainwindow.ui
    )

set(SRC_LIST
    data.h
    data.cpp
    main.cpp
    tablemodel.cpp
    win/main_window.cpp
    combo-delegate.cpp
    ${UIC_WRAPPERS}
    ${MOC_WRAPPERS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(CsvTableEditor Qt5::Widgets)
