project(complex_poly)
add_executable(complex_poly main.cpp)

find_path(COMPLEX_NUM_H_DIR complex_num.h PATH ${CMAKE_SOURCE_DIR}/complex_lib)

target_include_directories(complex_poly PRIVATE ${COMPLEX_NUM_H_DIR})

target_link_libraries(complex_poly complex)

install(TARGETS complex_poly
        DESTINATION bin
        COMPONENT user)
