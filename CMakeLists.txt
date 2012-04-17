# Base CMake file for STXXL

project(stxxl)

cmake_minimum_required(VERSION 2.8)

# compilation options 

option(USE_BOOST "Use Boost libraries for threads,config,filesystem,random and date_time" ON)

option(USE_GNU_PARALLEL "Use GNU parallel STL extensions" ON)

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

# find required dependencies

find_package(Threads)

# optional Boost libraries

if(USE_BOOST)

  find_package( Boost 1.36.0 COMPONENTS thread date_time iostreams system filesystem )

  if(Boost_FOUND)
    # globally add boost include directories
    include_directories(${Boost_INCLUDE_DIRS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTXXL_BOOST_CONFIG -DSTXXL_BOOST_FILESYSTEM -DSTXXL_BOOST_RANDOM -DSTXXL_BOOST_THREADS")
  else()
    message(FATAL_ERROR "Boost libraries not found. Try compilation without them.")
  endif()
  
endif(USE_BOOST)

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

# enable use of "make test"
enable_testing()

# globally adds top-level include directory
include_directories( "${PROJECT_SOURCE_DIR}/include" )

# for targets using stxxl library
set(STXXL_LIBS ${STXXL_LIBS} stxxl ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# build libstxxl in /lib
add_subdirectory(lib)

# macro for building stxxl tests

macro (stxxl_test TESTNAME)

  add_executable(${TESTNAME} ${TESTNAME}.cpp)
  target_link_libraries(${TESTNAME} ${STXXL_LIBS})
  add_test(${TESTNAME} ${TESTNAME})

endmacro (stxxl_test)

# build extra binaries and tests
add_subdirectory(common)
add_subdirectory(algo)
add_subdirectory(containers)
add_subdirectory(io)
add_subdirectory(mng)
add_subdirectory(stream)
add_subdirectory(utils)
