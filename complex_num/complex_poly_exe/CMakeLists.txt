project(complex_poly)
add_executable(complex_poly main.cpp)

find_path(COMPLEX_NUM_H_DIR complex_num.h)

set_property(TARGET complex_poly PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${COMPLEX_NUM_H_DIR})

target_link_libraries(complex_poly complex)

install(TARGETS complex_poly DESTINATION bin)
