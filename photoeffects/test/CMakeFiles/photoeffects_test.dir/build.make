# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kustikova/Documents/itlab-vision/photoeffects

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kustikova/Documents/itlab-vision/photoeffects

# Include any dependencies generated for this target.
include test/CMakeFiles/photoeffects_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/photoeffects_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/photoeffects_test.dir/flags.make

test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o: test/CMakeFiles/photoeffects_test.dir/flags.make
test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o: test/photoeffects_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kustikova/Documents/itlab-vision/photoeffects/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o -c /home/kustikova/Documents/itlab-vision/photoeffects/test/photoeffects_test.cpp

test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.i"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kustikova/Documents/itlab-vision/photoeffects/test/photoeffects_test.cpp > CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.i

test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.s"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kustikova/Documents/itlab-vision/photoeffects/test/photoeffects_test.cpp -o CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.s

test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.requires:
.PHONY : test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.requires

test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.provides: test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/photoeffects_test.dir/build.make test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.provides.build
.PHONY : test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.provides

test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.provides.build: test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o

test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o: test/CMakeFiles/photoeffects_test.dir/flags.make
test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o: test/test_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kustikova/Documents/itlab-vision/photoeffects/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/photoeffects_test.dir/test_main.cpp.o -c /home/kustikova/Documents/itlab-vision/photoeffects/test/test_main.cpp

test/CMakeFiles/photoeffects_test.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/photoeffects_test.dir/test_main.cpp.i"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kustikova/Documents/itlab-vision/photoeffects/test/test_main.cpp > CMakeFiles/photoeffects_test.dir/test_main.cpp.i

test/CMakeFiles/photoeffects_test.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/photoeffects_test.dir/test_main.cpp.s"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kustikova/Documents/itlab-vision/photoeffects/test/test_main.cpp -o CMakeFiles/photoeffects_test.dir/test_main.cpp.s

test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.requires:
.PHONY : test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.requires

test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.provides: test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/photoeffects_test.dir/build.make test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.provides.build
.PHONY : test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.provides

test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.provides.build: test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o

# Object files for target photoeffects_test
photoeffects_test_OBJECTS = \
"CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o" \
"CMakeFiles/photoeffects_test.dir/test_main.cpp.o"

# External object files for target photoeffects_test
photoeffects_test_EXTERNAL_OBJECTS =

photoeffects_test: test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o
photoeffects_test: test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o
photoeffects_test: 3rdparty/libgtest.a
photoeffects_test: src/libphotoeffects.a
photoeffects_test: test/CMakeFiles/photoeffects_test.dir/build.make
photoeffects_test: test/CMakeFiles/photoeffects_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../photoeffects_test"
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/photoeffects_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/photoeffects_test.dir/build: photoeffects_test
.PHONY : test/CMakeFiles/photoeffects_test.dir/build

test/CMakeFiles/photoeffects_test.dir/requires: test/CMakeFiles/photoeffects_test.dir/photoeffects_test.cpp.o.requires
test/CMakeFiles/photoeffects_test.dir/requires: test/CMakeFiles/photoeffects_test.dir/test_main.cpp.o.requires
.PHONY : test/CMakeFiles/photoeffects_test.dir/requires

test/CMakeFiles/photoeffects_test.dir/clean:
	cd /home/kustikova/Documents/itlab-vision/photoeffects/test && $(CMAKE_COMMAND) -P CMakeFiles/photoeffects_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/photoeffects_test.dir/clean

test/CMakeFiles/photoeffects_test.dir/depend:
	cd /home/kustikova/Documents/itlab-vision/photoeffects && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kustikova/Documents/itlab-vision/photoeffects /home/kustikova/Documents/itlab-vision/photoeffects/test /home/kustikova/Documents/itlab-vision/photoeffects /home/kustikova/Documents/itlab-vision/photoeffects/test /home/kustikova/Documents/itlab-vision/photoeffects/test/CMakeFiles/photoeffects_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/photoeffects_test.dir/depend
