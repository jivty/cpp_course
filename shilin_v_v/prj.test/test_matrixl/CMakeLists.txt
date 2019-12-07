add_executable(test_matrixl test_matrixl.cpp)
target_link_libraries(test_matrixl matrixl)
set_property(TARGET test_matrixl PROPERTY CXX_STANDARD 17)