cmake_minimum_required(VERSION 3.16)

set(APP_NAME "audio-loop")

project(${APP_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Multimedia)
find_package(Qt6 COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Test)

qt_add_executable(${APP_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    track.cpp
    track.h
)

set_target_properties(${APP_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${APP_NAME} PUBLIC
    Qt::Multimedia
    Qt::Widgets
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(TARGETS ${APP_NAME})
    install(
      FILES ${APP_NAME}.desktop
      DESTINATION share/applications/
      )
    install(
      FILES ${APP_NAME}.png
      DESTINATION share/icons/hicolor/128x128/apps
      )
endif()


if(WIN32)
    get_target_property(_qmake_executable Qt::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

    message(STATUS "windeploy: ${WINDEPLOYQT_EXECUTABLE}")
    message(STATUS "install prefix: ${CMAKE_INSTALL_PREFIX}")

    set(CMAKE_INSTALL_BINDIR "")
    message(STATUS "bin dir: ${CMAKE_INSTALL_BINDIR}")

    set(APP_TARGET_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
    message(STATUS "target  dir: ${APP_TARGET_DIR}")

    install(TARGETS ${APP_NAME} DESTINATION ${APP_TARGET_DIR})
    install(CODE "execute_process(COMMAND \"${WINDEPLOYQT_EXECUTABLE}\" --compiler-runtime --verbose 3 \"${APP_TARGET_DIR}\")")
endif(WIN32)

enable_testing(true)
add_executable(mytest
  mytest.cpp
  track.cpp
)
add_test(NAME mytest COMMAND mytest)

target_link_libraries(mytest PRIVATE
  Qt::Test
  Qt::Multimedia
  Qt::Widgets
)

