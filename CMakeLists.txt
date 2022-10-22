# minimum version of cmake this will work on
cmake_minimum_required(VERSION 3.0.0)

project(budextjs VERSION 0.1.0)

execute_process(COMMAND python ./innard_prep/preparator.py)


add_subdirectory(hssml)

# add_custom_target(
# 	always_run_target ALL
# 	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/header.h
# )

# add_custom_command(
# 	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/header.h
# 	COMMAND python ${py_cmd}
# )

