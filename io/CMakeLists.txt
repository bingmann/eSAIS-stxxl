# CMake targets for stxxl/io

stxxl_test(benchmark_configured_disks)
stxxl_test(benchmark_disk_and_flash)
stxxl_test(benchmark_random_block_access)
stxxl_test(flushbuffers)
stxxl_test(gen_file)
stxxl_test(iobench_scatter_in_place)
stxxl_test(test_cancel)
stxxl_test(test_io)
stxxl_test(test_io_sizes)
stxxl_test(verify_disks)

add_executable(benchmark_disks benchmark_disks.cpp)
target_link_libraries(benchmark_disks ${STXXL_LIBS})

#TESTS_NON_MSVC		 = sd_test

stxxl_test(sd_test)

#TESTS_UNITTEST		 = unittest

