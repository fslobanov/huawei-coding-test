set( lib_id "solver-1" )
set( app_id "task-1" )
add_library( ${lib_id} Solver.cpp )

target_compile_options( ${lib_id} PUBLIC -Wall -Wextra -pedantic -Werror )
target_include_directories( ${lib_id} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( ${lib_id} PUBLIC common )

add_executable( ${app_id} main.cpp )
target_link_libraries( ${app_id} PRIVATE ${lib_id} )

if( ${huawei_coding_test_BUILD_TESTS} )
	add_subdirectory( test )
endif()

