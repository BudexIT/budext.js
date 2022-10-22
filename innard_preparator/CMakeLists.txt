# minimum version of cmake this will work on
cmake_minimum_required(VERSION 3.0.0)

project(innard_preparator VERSION 0.1.0)

function(innard_prepare file_in file_out_h file_out_c)
	execute_process(COMMAND python ${CMAKE_SOURCE_DIR}/innard_preparator/preparator.py ${file_in} ${file_out_h} ${file_out_c})
endfunction()
