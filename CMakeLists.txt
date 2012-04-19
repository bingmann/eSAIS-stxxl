# Base CMake file for STXXL

project(stxxl)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# disallow in-source builds

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(SEND_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

###############################################################################
# compilation options 

option(USE_BOOST "Use Boost libraries for threads,config,filesystem,random and date_time" OFF)

option(USE_GNU_PARALLEL "Use GNU parallel STL extensions" OFF)

###############################################################################
# enable use of "make test"

enable_testing()

###############################################################################
# enable warnings

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall")
endif()

###############################################################################
# find thread library

find_package(Threads)

###############################################################################
# determine large file support

include(gmxTestLargeFiles)
GMX_TEST_LARGE_FILES (GMX_LARGEFILES)

if (GMX_LARGEFILES)
  add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES)
else (NOT GMX_LARGEFILES)
  message(FATAL_ERROR "Large file support was not detectable.")
endif (GMX_LARGEFILES)

###############################################################################
# optional Boost libraries

if(USE_BOOST)

  find_package( Boost 1.36.0 COMPONENTS thread date_time iostreams system filesystem )

  if(Boost_FOUND)
    # globally add boost include directories
    include_directories(${Boost_INCLUDE_DIRS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTXXL_BOOST_CONFIG -DSTXXL_BOOST_FILESYSTEM -DSTXXL_BOOST_RANDOM -DSTXXL_BOOST_THREADS -DSTXXL_BOOST_TIMESTAMP")
  else()
    message(FATAL_ERROR "Boost libraries not found. Try compilation without them.")
  endif()
  
endif(USE_BOOST)

###############################################################################
# optional GNU parallel STL mode

if(USE_GNU_PARALLEL)

  include(FindOpenMP)

  if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_PARALLEL")
  else()
    message(FATAL_ERROR "OpenMP not found. Try compilation without them.")
  endif()

endif(USE_GNU_PARALLEL)

###############################################################################
# optional CppUnit for more tests
# -- from http://www.cmake.org/pipermail/cmake/2006-October/011446.html

find_path(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h
  /usr/local/include
  /usr/include
  )

# With Win32, important to have both
if(WIN32)
  find_library(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  find_library(CPPUNIT_DEBUG_LIBRARY cppunitd
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
else(WIN32)
  # On unix system, debug and release have the same name
  find_library(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  find_library(CPPUNIT_DEBUG_LIBRARY cppunit
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
endif(WIN32)

if(CPPUNIT_INCLUDE_DIR)
  if(CPPUNIT_LIBRARY)
    set(CPPUNIT_FOUND "YES")
    set(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})
    set(CPPUNIT_DEBUG_LIBRARIES ${CPPUNIT_DEBUG_LIBRARY} ${CMAKE_DL_LIBS})
  endif(CPPUNIT_LIBRARY)
endif(CPPUNIT_INCLUDE_DIR)

if (NOT CPPUNIT_FOUND)
  message("CppUnit libraries not found. Some tests will not be compiled.")
else (CPPUNIT_FOUND)
  message("CppUnit libraries found: ${CPPUNIT_INCLUDE_DIR}.")
endif (NOT CPPUNIT_FOUND)

###############################################################################
# configure environment for building

# globally adds top-level include directory
include_directories( "${PROJECT_SOURCE_DIR}/include" )

# for targets using stxxl library
set(STXXL_LIBS ${STXXL_LIBS} stxxl ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# build libstxxl in /lib
add_subdirectory(lib)

# macro for building stxxl programs

macro (stxxl_build PROGNAME)

  add_executable(${PROGNAME} ${PROGNAME}.cpp)
  target_link_libraries(${PROGNAME} ${STXXL_LIBS})

endmacro (stxxl_build)

# macro for building stxxl tests

macro (stxxl_test TESTNAME)

  stxxl_build(${TESTNAME})
  add_test(${TESTNAME} ${TESTNAME})

endmacro (stxxl_test)

# macro for setting additional defines for targets

macro (add_define PROGNAME)

  set_property(TARGET ${PROGNAME} APPEND PROPERTY COMPILE_DEFINITIONS ${ARGN})

endmacro (add_define TESTNAME)

# build extra binaries and tests
add_subdirectory(common)
add_subdirectory(algo)
add_subdirectory(containers)
add_subdirectory(io)
add_subdirectory(mng)
add_subdirectory(stream)
add_subdirectory(utils)

# copy template headers to build directory

macro(copy_files GLOBPAT DESTINATION)
  file(GLOB_RECURSE COPY_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${GLOBPAT})
  add_custom_target(copy ALL COMMENT "Copying files: ${GLOBPAT}")

  foreach(FILENAME ${COPY_FILES})
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}")
    set(DST "${PROJECT_BINARY_DIR}/${FILENAME}")

    add_custom_command(TARGET copy COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST})
  endforeach(FILENAME)
endmacro(copy_files)

copy_files(include/* include/)
