cmake_minimum_required(VERSION 3.2)
                                                    
set (CMAKE_CXX_STANDARD 11)

project(phone_book)

find_package(Qt5 REQUIRED Core Gui Qml Quick)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_add_resources(
    QRC_WRAPPERS
    phone_book.qrc)


qt5_wrap_cpp(MOC_WRAPPERS
    phonemodel.h
    )

#qt5_wrap_ui(UIC_WRAPPERS
#    )

set(SRC_LIST
    resources/Main.qml
    resources/phonebook.json
    phone_book.cpp
    phonemodel.cpp
    ${UIC_WRAPPERS}
    ${MOC_WRAPPERS}
    ${QRC_WRAPPERS})



add_executable(${PROJECT_NAME} ${SRC_LIST} )

target_link_libraries(${PROJECT_NAME}  Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)

