# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ashwin/Downloads/coding/projects/graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ashwin/Downloads/coding/projects/graphics/build

# Include any dependencies generated for this target.
include CMakeFiles/raytrace.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raytrace.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raytrace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raytrace.dir/flags.make

CMakeFiles/raytrace.dir/src/main.cpp.o: CMakeFiles/raytrace.dir/flags.make
CMakeFiles/raytrace.dir/src/main.cpp.o: /Users/ashwin/Downloads/coding/projects/graphics/src/main.cpp
CMakeFiles/raytrace.dir/src/main.cpp.o: CMakeFiles/raytrace.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ashwin/Downloads/coding/projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raytrace.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytrace.dir/src/main.cpp.o -MF CMakeFiles/raytrace.dir/src/main.cpp.o.d -o CMakeFiles/raytrace.dir/src/main.cpp.o -c /Users/ashwin/Downloads/coding/projects/graphics/src/main.cpp

CMakeFiles/raytrace.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raytrace.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ashwin/Downloads/coding/projects/graphics/src/main.cpp > CMakeFiles/raytrace.dir/src/main.cpp.i

CMakeFiles/raytrace.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raytrace.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ashwin/Downloads/coding/projects/graphics/src/main.cpp -o CMakeFiles/raytrace.dir/src/main.cpp.s

CMakeFiles/raytrace.dir/src/utils/image.cpp.o: CMakeFiles/raytrace.dir/flags.make
CMakeFiles/raytrace.dir/src/utils/image.cpp.o: /Users/ashwin/Downloads/coding/projects/graphics/src/utils/image.cpp
CMakeFiles/raytrace.dir/src/utils/image.cpp.o: CMakeFiles/raytrace.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ashwin/Downloads/coding/projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raytrace.dir/src/utils/image.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raytrace.dir/src/utils/image.cpp.o -MF CMakeFiles/raytrace.dir/src/utils/image.cpp.o.d -o CMakeFiles/raytrace.dir/src/utils/image.cpp.o -c /Users/ashwin/Downloads/coding/projects/graphics/src/utils/image.cpp

CMakeFiles/raytrace.dir/src/utils/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raytrace.dir/src/utils/image.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ashwin/Downloads/coding/projects/graphics/src/utils/image.cpp > CMakeFiles/raytrace.dir/src/utils/image.cpp.i

CMakeFiles/raytrace.dir/src/utils/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raytrace.dir/src/utils/image.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ashwin/Downloads/coding/projects/graphics/src/utils/image.cpp -o CMakeFiles/raytrace.dir/src/utils/image.cpp.s

# Object files for target raytrace
raytrace_OBJECTS = \
"CMakeFiles/raytrace.dir/src/main.cpp.o" \
"CMakeFiles/raytrace.dir/src/utils/image.cpp.o"

# External object files for target raytrace
raytrace_EXTERNAL_OBJECTS =

raytrace: CMakeFiles/raytrace.dir/src/main.cpp.o
raytrace: CMakeFiles/raytrace.dir/src/utils/image.cpp.o
raytrace: CMakeFiles/raytrace.dir/build.make
raytrace: CMakeFiles/raytrace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ashwin/Downloads/coding/projects/graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable raytrace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytrace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raytrace.dir/build: raytrace
.PHONY : CMakeFiles/raytrace.dir/build

CMakeFiles/raytrace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raytrace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raytrace.dir/clean

CMakeFiles/raytrace.dir/depend:
	cd /Users/ashwin/Downloads/coding/projects/graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ashwin/Downloads/coding/projects/graphics /Users/ashwin/Downloads/coding/projects/graphics /Users/ashwin/Downloads/coding/projects/graphics/build /Users/ashwin/Downloads/coding/projects/graphics/build /Users/ashwin/Downloads/coding/projects/graphics/build/CMakeFiles/raytrace.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/raytrace.dir/depend
