add_executable(test_stacka test_stacka.cpp)
target_link_libraries(test_stacka stacka)
set_property(TARGET test_stacka PROPERTY CXX_STANDARD 17)