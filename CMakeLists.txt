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
)

target_link_libraries(${APP_NAME} PUBLIC
  Qt::Multimedia
  Qt::Widgets
)

# if(MSVC)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /Zc:__cplusplus /std:c++latest /permissive-")
# endif()

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
    set(CPACK_PACKAGE_VERSION_MAJOR "${APP_VERSION}")
    set(CPACK_PACKAGE_VERSION_MINOR "")
    set(CPACK_PACKAGE_VERSION_PATCH "")
    if(WIN32)
      set(CPACK_GENERATOR "ZIP")
      find_program(MAKENSIS_EXE makensis.exe PATHS "$ENV{PROGRAMFILES}/NSIS" "$ENV{PROGRAMFILES\(X86\)}/NSIS")
      if(MAKENSIS_EXE)
        message(STATUS "NSIS: ${MAKENSIS_EXE}")
        list(APPEND CPACK_GENERATOR "NSIS")
        set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
        set(CPACK_NSIS_MANIFEST_DPI_AWARE ON)
      endif()
      #list(APPEND CPACK_GENERATOR "WIX")
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

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

    find_program(LCOV lcov REQUIRED)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CTEST_COVERAGE_TARGET coverage)
    add_custom_target(${CTEST_COVERAGE_TARGET})

    # message(STATUS "setup LCOV coverage report")
    # add_custom_command(TARGET ${CTEST_COVERAGE_TARGET} POST_BUILD
    #   COMMAND lcov
    #   --capture
    #   --output-file coverage.info
    #   --no-external
    #   --exclude "*.moc"
    #   --exclude "moc_*"
    #   --exclude "qrc_*"
    #   --base-directory ${PROJECT_SOURCE_DIR}
    #   --directory ${PROJECT_BINARY_DIR}
    #   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    #   COMMENT "code coverage report by lcov")

    # message(STATUS "setup GCOV coverage report")
    # add_custom_command(TARGET ${CTEST_COVERAGE_TARGET} POST_BUILD
    #   COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/gcovr
    #   COMMAND gcovr
    #   --html --html-details
    #   --output gcovr/index.html
    #   --root ${PROJECT_SOURCE_DIR}
    #   --object-directory ${PROJECT_BINARY_DIR}
    #   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    #   COMMENT "code coverage report by gcovr")

    message(STATUS "setup GCOV coverage report")
    add_custom_command(TARGET ${CTEST_COVERAGE_TARGET} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/gcovr
      COMMAND gcovr
      --coveralls coverage.json
      --root ${PROJECT_SOURCE_DIR}
      --object-directory ${PROJECT_BINARY_DIR}
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      COMMENT "code coverage report by gcovr")

endif()
