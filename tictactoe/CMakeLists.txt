project(tictactoe)

cmake_minimum_required(VERSION 3.2)

find_package(Qt5 REQUIRED Widgets Network)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_cpp(MOC_WRAPPERS
mainwindow.h
)
qt5_wrap_ui(UIC_WRAPPERS
  mainwindow.ui
    )

set(SRC_LIST
    main.cpp
    mainwindow.cpp
    ${UIC_WRAPPERS}
    ${MOC_WRAPPERS})

add_executable(${PROJECT_NAME} ${SRC_LIST})


target_link_libraries(tictactoe Qt5::Widgets)
