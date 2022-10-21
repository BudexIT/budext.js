# minimum version of cmake this will work on
cmake_minimum_required(VERSION 3.0.0)

# project's name and version
set(project_name hcssml)
project(${project_name} VERSION 1.0.0)

# add ./include/ as an include directory
include_directories(include)

# recursively search the include and src directories
file(GLOB_RECURSE srcs
	"include/*.hpp"
	"include/*.h"
	"src/*.cpp"
	"src/*.c"
)

# create an executable app out of the sources
add_executable(${project_name} ${srcs})
