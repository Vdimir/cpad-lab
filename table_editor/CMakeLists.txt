project(CsvTableEditor)

cmake_minimum_required(VERSION 3.2)

find_package(Qt5 REQUIRED Widgets LinguistTools)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_cpp(MOC_WRAPPERS
    tablemodel.h
    win/table_window.h
    win/main_window.h
    combo-delegate.h
    )

qt5_wrap_ui(UIC_WRAPPERS
    ui/tablewindow.ui
    ui/mainwindow.ui
    )

set(SRC_LIST
    data.h
    data.cpp
    main.cpp
    tablemodel.cpp
    win/table_window.cpp
    win/main_window.cpp
    combo-delegate.cpp
    ${UIC_WRAPPERS}
    ${MOC_WRAPPERS})

#add_definitions(-DQT_NO_CAST_FROM_ASCII)
set(FILES_TO_TRANSLATE ${SRC_LIST})

set(TS_FILES translations/lang_ru_RU.ts translations/lang_en_US.ts)

option(UPDATE_TRANSLATIONS "Update source translation (files translations/*.ts)." ON)

if(UPDATE_TRANSLATIONS)
    message(STATUS "UPDATE_TRANSLATIONS option is set.")
    qt5_create_translation(QM_FILES ${FILES_TO_TRANSLATE} ${TS_FILES})
else()
    qt5_add_translation(QM_FILES ${TS_FILES})
endif()

add_custom_target(translations DEPENDS ${QM_FILES})
set_property(DIRECTORY PROPERTY CLEAN_NO_CUSTOM TRUE)

qt5_add_resources(QRC_WRAPPERS resources.qrc OPTIONS -no-compress)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${QRC_WRAPPERS})

target_link_libraries(CsvTableEditor Qt5::Widgets)

install(TARGETS CsvTableEditor RUNTIME DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION translations)

get_property(LIB_QT5CORE_PATH TARGET Qt5::Core PROPERTY IMPORTED_LOCATION_RELEASE)
get_filename_component(QT_LIBRARY_DIR "${LIB_QT5CORE_PATH}" DIRECTORY)
set(EXE_PATH bin/CsvTableEditor${CMAKE_EXECUTABLE_SUFFIX})
include(DeployQt4)
install_qt4_executable(
        "${EXE_PATH}" # executable file
        "" # modules
        "" # libraries
        "${QT_LIBRARY_DIR}") # directories for libraries search

