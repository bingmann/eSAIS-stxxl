# CMake targets for stxxl/lib

add_library(stxxl

  ../common/exithandler.cpp
  ../common/log.cpp
  ../common/rand.cpp
  ../common/seed.cpp
  ../common/verbose.cpp
  ../common/version.cpp

  ../io/boostfd_file.cpp
  ../io/create_file.cpp
  ../io/disk_queued_file.cpp
  ../io/fileperblock_file.cpp
  ../io/iostats.cpp
  ../io/mem_file.cpp
  ../io/request.cpp
  ../io/request_queue_impl_1q.cpp
  ../io/request_queue_impl_qwqr.cpp
  ../io/request_queue_impl_worker.cpp
  ../io/request_with_state.cpp
  ../io/request_with_waiters.cpp
  ../io/serving_request.cpp
  ../io/syscall_file.cpp
  ../io/ufs_file_base.cpp
  ../io/wbtl_file.cpp
  ../io/wfs_file_base.cpp
  ../io/wincall_file.cpp

  ../mng/config.cpp
  ../mng/diskallocator.cpp
  ../mng/mng.cpp
  
  ../algo/async_schedule.cpp

# LIB_OBJECTS_NON_MSVC =
  ../io/mmap_file.cpp
  ../io/simdisk_file.cpp
  
  )

set_target_properties(stxxl PROPERTIES VERSION 1.3.2)
