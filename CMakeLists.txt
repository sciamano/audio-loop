cmake_minimum_required(VERSION 3.16)

set(APP_NAME "audio-loop")

project(${APP_NAME} LANGUAGES CXX)

add_subdirectory(app)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  add_subdirectory(linux)
endif()
