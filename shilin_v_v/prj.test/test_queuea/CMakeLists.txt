add_executable(test_queuea test_queuea.cpp)
target_link_libraries(test_queuea queuea)
set_property(TARGET test_queuea PROPERTY CXX_STANDARD 17)