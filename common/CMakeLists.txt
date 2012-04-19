# CMake targets for stxxl/common

stxxl_test(test_random)
stxxl_test(test_manyunits2)
stxxl_test(test_globals)

add_executable(stxxl_info stxxl_info.cpp)
target_link_libraries(stxxl_info ${STXXL_LIBS})

# Left-overs from GNUmakefile

# ifneq (,$(wildcard .svn))
# version.$(lo): STXXL_COMPILER_OPTIONS += -DHAVE_VERSION_SVN_DEFS
# endif

# ifneq (,$(wildcard version.defs))
# version.$(lo): STXXL_COMPILER_OPTIONS += -DHAVE_VERSION_DEFS
# endif
