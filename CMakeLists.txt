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

#find_package(Qt6 COMPONENTS Multimedia)
find_package(Qt6 COMPONENTS Widgets)

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
#    Qt::Multimedia
    Qt::Widgets
)

install(TARGETS ${APP_NAME})
if(WIN32)
    install(CODE "
        message(STATUS \"run windeployqt at \${CMAKE_INSTALL_PREFIX}\${CMAKE_INSTALL_BINDIR}\")
        execute_process(COMMAND \"${Qt6_Dir}/bin/windeployqt.exe\" --verbose 3 \${CMAKE_INSTALL_PREFIX}\${CMAKE_INSTALL_BINDIR})
    ")
endif(WIN32)
