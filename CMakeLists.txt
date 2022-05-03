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

if(WIN32)
    message(STATUS ${WINDEPLOYQT_EXECUTABLE})
    message(STATUS ${CMAKE_INSTALL_PREFIX})

    set(CMAKE_INSTALL_BINDIR "")
    message(STATUS ${CMAKE_INSTALL_BINDIR})

    set(APP_TARGET_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
    message(STATUS ${APP_TARGET_DIR})

    install(TARGETS ${APP_NAME} DESTINATION ${APP_TARGET_DIR})
    install(CODE "execute_process(COMMAND \"${WINDEPLOYQT_EXECUTABLE}\" \"${APP_TARGET_DIR}\")")
endif(WIN32)
