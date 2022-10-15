set(target_id "task-2")
add_executable(${target_id} main.cpp Solver.cpp)

target_compile_options(${target_id} PRIVATE -Wall -Wextra -pedantic -Werror)
target_include_directories(${target_id} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target_id} PRIVATE common)
