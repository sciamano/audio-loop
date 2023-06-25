cmake_minimum_required(VERSION 3.16)

set(APP_NAME "audio-loop")

project(${APP_NAME} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS
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

if(NOT DEFINED APP_VERSION)
  find_package(Git)
  if(Git_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE APP_VERSION)
  elseif()
    set(APP_VERSION "unknown")
  endif()
endif()
string(STRIP ${APP_VERSION} APP_VERSION)
message(STATUS "version: ${APP_VERSION}")

install(TARGETS ${APP_NAME} RUNTIME BUNDLE DESTINATION ".")

option(USE_DEPLOY "run Qt deploy script." OFF)

if(USE_DEPLOY)
  if((CMAKE_SYSTEM_NAME MATCHES "Windows" AND Qt6_VERSION VERSION_GREATER_EQUAL 6.4)
      OR (CMAKE_SYSTEM_NAME MATCHES "Darwin" AND Qt6_VERSION VERSION_GREATER_EQUAL 6.4)
      OR (CMAKE_SYSTEM_NAME MATCHES "Linux" AND Qt6_VERSION VERSION_GREATER_EQUAL 6.5))

    set(CMAKE_INSTALL_DATADIR "${APP_NAME}.app/Contents/Resources")
    if(NOT CMAKE_SYSTEM_NAME MATCHES "Darwin")
      set(CMAKE_INSTALL_DATADIR ".")
    endif()
    set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATADIR})

    qt_generate_deploy_app_script(TARGET ${APP_NAME} FILENAME_VARIABLE deploy_script)
    install(SCRIPT ${deploy_script})

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
endif()

install(FILES
  "${PROJECT_SOURCE_DIR}/tone.wav"
  TYPE DATA)

install(FILES
  "${PROJECT_SOURCE_DIR}/README.md"
  TYPE DOC)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  add_subdirectory(linux)
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
