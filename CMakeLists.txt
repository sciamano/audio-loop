cmake_minimum_required(VERSION 3.16)

set(APP_NAME "audio-loop")

project(${APP_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 COMPONENTS
  Multimedia
  Test
  Widgets
  REQUIRED)
message(STATUS "Using Qt ${Qt6_VERSION} from ${Qt6_DIR}")

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

message(STATUS "system name: ${CMAKE_SYSTEM_NAME}")

qt_add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE
  main.cpp
  mainwindow.cpp
  mainwindow.h
  track.cpp
  track.h
  main.qrc
)

# set_target_properties(${APP_NAME} PROPERTIES
#     WIN32_EXECUTABLE TRUE
#     MACOSX_BUNDLE TRUE
# )

target_link_libraries(${APP_NAME} PUBLIC
  Qt::Multimedia
  Qt::Widgets
)

if((CMAKE_SYSTEM_NAME MATCHES "Windows" AND Qt6_VERSION VERSION_GREATER_EQUAL 6.4)
  OR (CMAKE_SYSTEM_NAME MATCHES "Darwin" AND Qt6_VERSION VERSION_GREATER_EQUAL 6.4)
  OR (CMAKE_SYSTEM_NAME MATCHES "Linux" AND Qt6_VERSION VERSION_GREATER_EQUAL 6.5))

    install(TARGETS ${APP_NAME}
      BUNDLE  DESTINATION .
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    qt_generate_deploy_app_script(TARGET ${APP_NAME} FILENAME_VARIABLE deploy_script)
    install(SCRIPT ${deploy_script})

    install(FILES
      "${PROJECT_SOURCE_DIR}/tone.wav"
      DESTINATION "${APP_NAME}.app/Contents/Data")

    find_package(Git)
    execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_VERSION
    )
    string(STRIP ${GIT_VERSION} GIT_VERSION)
    message(STATUS "git version: ${GIT_VERSION}")

    include(InstallRequiredSystemLibraries)
    set(CPACK_PACKAGE_VERSION_MAJOR "${GIT_VERSION}")
    set(CPACK_PACKAGE_VERSION_MINOR "")
    set(CPACK_PACKAGE_VERSION_PATCH "")
    if(WIN32)
      set(CPACK_GENERATOR "ZIP")
    elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
      set(CPACK_GENERATOR "DragNDrop")
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
      set(CPACK_GENERATOR "TGZ")
    endif()
    include(CPack)

endif()



enable_testing(true)
add_executable(mytest
  mytest.cpp
  track.cpp
  test.qrc
)
add_test(NAME mytest COMMAND mytest)

target_link_libraries(mytest PRIVATE
  Qt::Multimedia
  Qt::Test
  Qt::Widgets
)
