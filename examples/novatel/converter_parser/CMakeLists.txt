add_executable(converter_parser converter_parser.cpp)
target_link_libraries(converter_parser common novatel stream_interface)
set_property(TARGET converter_parser PROPERTY FOLDER "examples")
