cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PROJECT_TEST)

#----------------------------------------------------------------------------

set(useROTEST false)
set(TEST_SOURCE_DIRECTORIES src)
set(TEST_EXECUTABLES example)
set(TEST_SCRIPTS vis.mac)

#----------------------------------------------------------------------------

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

if(useROTEST)
  list(APPEND TEST_SOURCE_DIRECTORIES)
  list(APPEND TEST_EXECUTABLES)
endif(useROTEST)

set(TEST_SOURCES_DIRECTORIES_FULL)
foreach(_directory ${TEST_SOURCE_DIRECTORIES})
  list(APPEND TEST_SOURCE_DIRECTORIES_FULL ${PROJECT_SOURCE_DIR}/${_directory})
endforeach(_directory)

set(TEST_SOURCES)
foreach(_directory ${TEST_SOURCE_DIRECTORIES_FULL})
  list(APPEND TEST_SOURCES ${_directory}/*.cc)
endforeach(_directory)

set(TEST_HEADERS)
foreach(_directory ${TEST_SOURCE_DIRECTORIES_FULL})
  list(APPEND TEST_HEADERS ${_directory}/*.hh)
endforeach(_directory)

include(${Geant4_USE_FILE})
include_directories(${TEST_SOURCE_DIRECTORIES_FULL})

if(useROTEST)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROTEST_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROTEST_CXX_FLAGS}")
endif(useROTEST)

file(GLOB sources ${TEST_SOURCES})
file(GLOB headers ${TEST_HEADERS})

foreach(_executable ${TEST_EXECUTABLES})
  add_executable(${_executable} ${_executable}.cc ${sources} ${headers})
if(useROTEST)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROTEST_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROTEST_LD_FLAGS})
endif(useROTEST)
  target_link_libraries(${_executable} ${Geant4_LIBRARIES})
endforeach(_executable)

foreach(_script ${TEST_SCRIPTS})
  configure_file( ${PROJECT_SOURCE_DIR}/${_script} ${PROJECT_BINARY_DIR}/${_script} COPYONLY)
endforeach(_script)

add_custom_target(PROJECT_TEST DEPENDS ${TEST_EXECUTABLES})

foreach(_executable ${TEST_EXECUTABLES})
  install(TARGETS ${_executable} DESTINATION bin)
endforeach(_executable)
