cmake_minimum_required(VERSION 3.10.0)
project(system_space LANGUAGES CXX)

include($ENV{FLUTTER_ROOT}/cmake/flutter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(PLUGIN_NAME ${PROJECT_NAME}_plugin)

add_library(${PLUGIN_NAME} SHARED
  ${PLUGIN_NAME}.cpp
)

target_link_libraries(${PLUGIN_NAME} PRIVATE
  flutter
  flutter_wrapper_plugin
)

target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_target_properties(${PLUGIN_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

flutter_create_linux_plugin(${PLUGIN_NAME}
  "main.cc"
)

# Add the system_space.cc file to the plugin's source files
target_sources(${PLUGIN_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/system_space.cc
)
