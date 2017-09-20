project(complex_lib)


add_library(complex SHARED complex_num.cpp)


target_include_directories(complex INTERFACE .)

install(TARGETS complex 
        COMPONENT user
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)


set_target_properties(complex PROPERTIES PUBLIC_HEADER "complex_num.h")

install(TARGETS complex 
        COMPONENT developer
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        ARCHIVE DESTINATION lib
)
