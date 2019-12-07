add_executable(test_stackl test_stackl.cpp)
target_link_libraries(test_stackl stackl)
set_property(TARGET test_stackl PROPERTY CXX_STANDARD 17)