# CMake targets for stxxl/algo

stxxl_test(test_scan)
stxxl_test(test_sort)
stxxl_test(test_ksort)
stxxl_test(test_stable_ksort)
stxxl_test(sort_file)
stxxl_test(copy_and_sort_file)
stxxl_test(test_random_shuffle)
stxxl_test(test_asch)
stxxl_test(test_bad_cmp)

#TESTS_LONG_COMPILE	 = test_sort_all_parameters test_ksort_all_parameters test_stable_ksort_all_parameters

stxxl_test(test_sort_all_parameters)
stxxl_test(test_ksort_all_parameters)
stxxl_test(test_stable_ksort_all_parameters)

#TESTS_NON_MSVC		 = test_parallel_sort

stxxl_test(test_parallel_sort)
