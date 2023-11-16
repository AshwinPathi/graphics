cmake_minimum_required ( VERSION 3.1.0...3.27.0 )

project ( RayTracer LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD          20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )


##################### Old way of including stuff
# set ( RAY_TRACER 
#    src/math/vec.h
#
#    src/utils/image.h
#    src/utils/image.cpp
#
#    src/main.cpp
# )
# include_directories(src)
#####################

# Include all files in src. Make sure all the files are either pure header or header/cpp files.
file(GLOB_RECURSE RAY_TRACER CONFIGURE_DEPENDS "src/*.cpp")
add_executable(raytrace ${RAY_TRACER})

# Compile options
add_compile_options(-Werror)
add_compile_options(-std=c++2a) # To use experimental C++20 features

# Executable
add_executable(rayTracer ${RAY_TRACER})
