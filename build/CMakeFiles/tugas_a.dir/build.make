# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build"

# Include any dependencies generated for this target.
include CMakeFiles/tugas_a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tugas_a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tugas_a.dir/flags.make

CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.o: CMakeFiles/tugas_a.dir/flags.make
CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.o: ../src/TugasA/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.o -c "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/src/TugasA/main.cpp"

CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/src/TugasA/main.cpp" > CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.i

CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/src/TugasA/main.cpp" -o CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.s

# Object files for target tugas_a
tugas_a_OBJECTS = \
"CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.o"

# External object files for target tugas_a
tugas_a_EXTERNAL_OBJECTS =

tugas_a: CMakeFiles/tugas_a.dir/src/TugasA/main.cpp.o
tugas_a: CMakeFiles/tugas_a.dir/build.make
tugas_a: /usr/local/lib/libopencv_gapi.so.4.6.0
tugas_a: /usr/local/lib/libopencv_highgui.so.4.6.0
tugas_a: /usr/local/lib/libopencv_ml.so.4.6.0
tugas_a: /usr/local/lib/libopencv_objdetect.so.4.6.0
tugas_a: /usr/local/lib/libopencv_photo.so.4.6.0
tugas_a: /usr/local/lib/libopencv_stitching.so.4.6.0
tugas_a: /usr/local/lib/libopencv_video.so.4.6.0
tugas_a: /usr/local/lib/libopencv_videoio.so.4.6.0
tugas_a: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
tugas_a: /usr/local/lib/libopencv_dnn.so.4.6.0
tugas_a: /usr/local/lib/libopencv_calib3d.so.4.6.0
tugas_a: /usr/local/lib/libopencv_features2d.so.4.6.0
tugas_a: /usr/local/lib/libopencv_flann.so.4.6.0
tugas_a: /usr/local/lib/libopencv_imgproc.so.4.6.0
tugas_a: /usr/local/lib/libopencv_core.so.4.6.0
tugas_a: CMakeFiles/tugas_a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tugas_a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tugas_a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tugas_a.dir/build: tugas_a

.PHONY : CMakeFiles/tugas_a.dir/build

CMakeFiles/tugas_a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tugas_a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tugas_a.dir/clean

CMakeFiles/tugas_a.dir/depend:
	cd "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dancoeks/Kuliah/DSEC/Tugas Akhir" "/home/dancoeks/Kuliah/DSEC/Tugas Akhir" "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build" "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build" "/home/dancoeks/Kuliah/DSEC/Tugas Akhir/build/CMakeFiles/tugas_a.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/tugas_a.dir/depend
