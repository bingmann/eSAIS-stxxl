# CMake targets for stxxl/io

stxxl_build(benchmark_configured_disks)
stxxl_build(benchmark_disk_and_flash)
stxxl_build(benchmark_random_block_access)
stxxl_build(flushbuffers)
stxxl_build(gen_file)
stxxl_build(iobench_scatter_in_place)
stxxl_build(test_cancel)
stxxl_build(test_io)
stxxl_build(test_io_sizes)
stxxl_build(verify_disks)

add_executable(benchmark_disks benchmark_disks.cpp)
target_link_libraries(benchmark_disks ${STXXL_LIBS})

if (NOT MSVC)
  stxxl_build(sd_test)
endif (NOT MSVC)

if (CPPUNIT_FOUND)

  add_executable(unittest_io unittest.cpp)
  target_link_libraries(unittest_io ${STXXL_LIBS} ${CPPUNIT_LIBRARIES})
  add_test(unittest_io unittest_io)

endif (CPPUNIT_FOUND)
