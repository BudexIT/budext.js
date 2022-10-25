# minimum version of cmake this will work on
cmake_minimum_required(VERSION 3.0.0)

# project's name and version
set(project_name hssml)
project(${project_name} VERSION 1.0.0)

# add ./include/ and ./innards_build/ as an include directory
include_directories(include)

# prepare innards
innard_prepare(
	${CMAKE_CURRENT_SOURCE_DIR}/innards/index.html
	${CMAKE_CURRENT_SOURCE_DIR}/include/innards/index.html.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/innards/index.html.c
)

# recursively search the include and src directories
file(GLOB_RECURSE srcs
	"include/*.hpp"
	"include/*.h"
	"src/*.cpp"
	"src/*.c"
)

# create an executable app out of the sources
add_executable(${project_name} ${srcs})

# if compiled to a static application, link statically
if(LIBTYPE STREQUAL "STATIC")
	target_link_options(${project_name} PRIVATE -static)
endif()