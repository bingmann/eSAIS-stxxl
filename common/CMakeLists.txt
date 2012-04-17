# CMake targets for stxxl/common

stxxl_test(test_random)
stxxl_test(test_manyunits2)
stxxl_test(test_globals)

add_executable(stxxl_info stxxl_info.cpp)
target_link_libraries(stxxl_info ${STXXL_LIBS})
