add_executable(test_queuel test_queuel.cpp)
target_link_libraries(test_queuel queuel)
set_property(TARGET test_queuel PROPERTY CXX_STANDARD 17)