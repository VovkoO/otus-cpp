# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_3f27b.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmTC_3f27b.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_3f27b.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_3f27b.dir/flags.make

CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o: CMakeFiles/cmTC_3f27b.dir/flags.make
CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o: /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.29/Modules/CMakeCCompilerABI.c
CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o: CMakeFiles/cmTC_3f27b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --progress-dir=/Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o -MF CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o.d -o CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o -c /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.29/Modules/CMakeCCompilerABI.c

CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.29/Modules/CMakeCCompilerABI.c > CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.i

CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/share/cmake-3.29/Modules/CMakeCCompilerABI.c -o CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.s

# Object files for target cmTC_3f27b
cmTC_3f27b_OBJECTS = \
"CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o"

# External object files for target cmTC_3f27b
cmTC_3f27b_EXTERNAL_OBJECTS =

cmTC_3f27b: CMakeFiles/cmTC_3f27b.dir/CMakeCCompilerABI.c.o
cmTC_3f27b: CMakeFiles/cmTC_3f27b.dir/build.make
cmTC_3f27b: CMakeFiles/cmTC_3f27b.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --progress-dir=/Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmTC_3f27b"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmTC_3f27b.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_3f27b.dir/build: cmTC_3f27b
.PHONY : CMakeFiles/cmTC_3f27b.dir/build

CMakeFiles/cmTC_3f27b.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmTC_3f27b.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_3f27b.dir/clean

CMakeFiles/cmTC_3f27b.dir/depend:
	cd /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN /Users/vladimir.razdrogin/dev/otus-cpp/cmake-build-debug/CMakeFiles/CMakeScratch/TryCompile-E4yMSN/CMakeFiles/cmTC_3f27b.dir/DependInfo.cmake
.PHONY : CMakeFiles/cmTC_3f27b.dir/depend

