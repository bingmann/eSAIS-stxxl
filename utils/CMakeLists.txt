# CMake targets for stxxl/utils

stxxl_test(pq_param)
stxxl_test(log2)

#TESTS_NON_MSVC		 = malloc

stxxl_test(malloc)

#UTIL_BINARIES		 = createdisks

add_executable(createdisks createdisks.cpp)
target_link_libraries(createdisks ${STXXL_LIBS})

#UTIL_BINARIES_NON_MSVC	 = mlock

add_executable(mlock mlock.cpp)
target_link_libraries(mlock ${STXXL_LIBS})
