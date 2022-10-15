set(target_id "task-3")
add_executable(${target_id} main.cpp)
target_link_libraries(${target_id} PRIVATE common)
target_compile_options(${target_id} PRIVATE -Wall -Wextra -pedantic -Werror)