cmake_minimum_required( VERSION 3.20 )
project( huawei_coding_test )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/run" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/run" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/run" )

option( huawei_coding_test_BUILD_TESTS "Build tests" ON )
if( ${huawei_coding_test_BUILD_TESTS} )
	enable_testing()
endif()

add_subdirectory( common )
add_subdirectory( task-1 )
add_subdirectory( task-2 )
add_subdirectory( task-3 )
