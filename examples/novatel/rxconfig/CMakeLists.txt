add_executable(rxconfig rxconfig_example.cpp)
target_link_libraries(rxconfig common novatel stream_interface)
set_property(TARGET rxconfig PROPERTY FOLDER "examples")
