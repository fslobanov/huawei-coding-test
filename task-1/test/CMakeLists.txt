enable_testing()
find_package( GTest REQUIRED )

set( "target_id" test_solver-1 )

add_executable( ${target_id} SolverTest.cpp )
target_link_libraries( ${target_id} PRIVATE solver-1 GTest::gtest_main )

include( GoogleTest )
gtest_discover_tests( ${target_id} )