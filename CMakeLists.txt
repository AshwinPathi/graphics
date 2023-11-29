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
add_compile_options(-Wall)
add_compile_options(-Wno-missing-braces)
add_compile_options(-Wmissing-field-initializers )
add_compile_options(-std=c++2a) # To use experimental C++20 features


option(DEBUG "Turn on debugging" OFF) #OFF by default
# For debugging
if(DEBUG)
    message("Debugging turned ON.")
    # add_compile_options(-fsanitize=address) # address sanitizer
    add_compile_options(-g) # flags
    add_compile_options(-O0) # optimizations turned off
    add_compile_options(-fno-lto) # no lto for debug symbols in lldb
else()
    message("Debugging turned OFF.")
    add_compile_options(-O3)
endif(DEBUG)
unset(DEBUG CACHE)

# Executable
add_executable(rayTracer ${RAY_TRACER})
