# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\CLion 2020.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\CLion 2020.1.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\CLionProjects\Instrument

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\CLionProjects\Instrument\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Instrument.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Instrument.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Instrument.dir/flags.make

CMakeFiles/Instrument.dir/main.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Instrument.dir/main.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\main.cpp.obj -c E:\CLionProjects\Instrument\main.cpp

CMakeFiles/Instrument.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/main.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\main.cpp > CMakeFiles\Instrument.dir\main.cpp.i

CMakeFiles/Instrument.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/main.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\main.cpp -o CMakeFiles\Instrument.dir\main.cpp.s

CMakeFiles/Instrument.dir/net/kcp.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/net/kcp.cpp.obj: ../net/kcp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Instrument.dir/net/kcp.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\net\kcp.cpp.obj -c E:\CLionProjects\Instrument\net\kcp.cpp

CMakeFiles/Instrument.dir/net/kcp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/net/kcp.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\net\kcp.cpp > CMakeFiles\Instrument.dir\net\kcp.cpp.i

CMakeFiles/Instrument.dir/net/kcp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/net/kcp.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\net\kcp.cpp -o CMakeFiles\Instrument.dir\net\kcp.cpp.s

CMakeFiles/Instrument.dir/net/tcp.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/net/tcp.cpp.obj: ../net/tcp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Instrument.dir/net/tcp.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\net\tcp.cpp.obj -c E:\CLionProjects\Instrument\net\tcp.cpp

CMakeFiles/Instrument.dir/net/tcp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/net/tcp.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\net\tcp.cpp > CMakeFiles\Instrument.dir\net\tcp.cpp.i

CMakeFiles/Instrument.dir/net/tcp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/net/tcp.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\net\tcp.cpp -o CMakeFiles\Instrument.dir\net\tcp.cpp.s

CMakeFiles/Instrument.dir/net/udp.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/net/udp.cpp.obj: ../net/udp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Instrument.dir/net/udp.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\net\udp.cpp.obj -c E:\CLionProjects\Instrument\net\udp.cpp

CMakeFiles/Instrument.dir/net/udp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/net/udp.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\net\udp.cpp > CMakeFiles\Instrument.dir\net\udp.cpp.i

CMakeFiles/Instrument.dir/net/udp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/net/udp.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\net\udp.cpp -o CMakeFiles\Instrument.dir\net\udp.cpp.s

CMakeFiles/Instrument.dir/plugin/ikcp.c.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/plugin/ikcp.c.obj: ../plugin/ikcp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Instrument.dir/plugin/ikcp.c.obj"
	E:\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Instrument.dir\plugin\ikcp.c.obj   -c E:\CLionProjects\Instrument\plugin\ikcp.c

CMakeFiles/Instrument.dir/plugin/ikcp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Instrument.dir/plugin/ikcp.c.i"
	E:\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\CLionProjects\Instrument\plugin\ikcp.c > CMakeFiles\Instrument.dir\plugin\ikcp.c.i

CMakeFiles/Instrument.dir/plugin/ikcp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Instrument.dir/plugin/ikcp.c.s"
	E:\MinGW64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\CLionProjects\Instrument\plugin\ikcp.c -o CMakeFiles\Instrument.dir\plugin\ikcp.c.s

CMakeFiles/Instrument.dir/structure/rbt.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/structure/rbt.cpp.obj: ../structure/rbt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Instrument.dir/structure/rbt.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\structure\rbt.cpp.obj -c E:\CLionProjects\Instrument\structure\rbt.cpp

CMakeFiles/Instrument.dir/structure/rbt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/structure/rbt.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\structure\rbt.cpp > CMakeFiles\Instrument.dir\structure\rbt.cpp.i

CMakeFiles/Instrument.dir/structure/rbt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/structure/rbt.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\structure\rbt.cpp -o CMakeFiles\Instrument.dir\structure\rbt.cpp.s

CMakeFiles/Instrument.dir/sys/clock.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/sys/clock.cpp.obj: ../sys/clock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Instrument.dir/sys/clock.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\sys\clock.cpp.obj -c E:\CLionProjects\Instrument\sys\clock.cpp

CMakeFiles/Instrument.dir/sys/clock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/sys/clock.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\sys\clock.cpp > CMakeFiles\Instrument.dir\sys\clock.cpp.i

CMakeFiles/Instrument.dir/sys/clock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/sys/clock.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\sys\clock.cpp -o CMakeFiles\Instrument.dir\sys\clock.cpp.s

CMakeFiles/Instrument.dir/sys/deal.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/sys/deal.cpp.obj: ../sys/deal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Instrument.dir/sys/deal.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\sys\deal.cpp.obj -c E:\CLionProjects\Instrument\sys\deal.cpp

CMakeFiles/Instrument.dir/sys/deal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/sys/deal.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\sys\deal.cpp > CMakeFiles\Instrument.dir\sys\deal.cpp.i

CMakeFiles/Instrument.dir/sys/deal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/sys/deal.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\sys\deal.cpp -o CMakeFiles\Instrument.dir\sys\deal.cpp.s

CMakeFiles/Instrument.dir/sys/number.cpp.obj: CMakeFiles/Instrument.dir/flags.make
CMakeFiles/Instrument.dir/sys/number.cpp.obj: ../sys/number.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Instrument.dir/sys/number.cpp.obj"
	E:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Instrument.dir\sys\number.cpp.obj -c E:\CLionProjects\Instrument\sys\number.cpp

CMakeFiles/Instrument.dir/sys/number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Instrument.dir/sys/number.cpp.i"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CLionProjects\Instrument\sys\number.cpp > CMakeFiles\Instrument.dir\sys\number.cpp.i

CMakeFiles/Instrument.dir/sys/number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Instrument.dir/sys/number.cpp.s"
	E:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CLionProjects\Instrument\sys\number.cpp -o CMakeFiles\Instrument.dir\sys\number.cpp.s

# Object files for target Instrument
Instrument_OBJECTS = \
"CMakeFiles/Instrument.dir/main.cpp.obj" \
"CMakeFiles/Instrument.dir/net/kcp.cpp.obj" \
"CMakeFiles/Instrument.dir/net/tcp.cpp.obj" \
"CMakeFiles/Instrument.dir/net/udp.cpp.obj" \
"CMakeFiles/Instrument.dir/plugin/ikcp.c.obj" \
"CMakeFiles/Instrument.dir/structure/rbt.cpp.obj" \
"CMakeFiles/Instrument.dir/sys/clock.cpp.obj" \
"CMakeFiles/Instrument.dir/sys/deal.cpp.obj" \
"CMakeFiles/Instrument.dir/sys/number.cpp.obj"

# External object files for target Instrument
Instrument_EXTERNAL_OBJECTS =

Instrument.exe: CMakeFiles/Instrument.dir/main.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/net/kcp.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/net/tcp.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/net/udp.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/plugin/ikcp.c.obj
Instrument.exe: CMakeFiles/Instrument.dir/structure/rbt.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/sys/clock.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/sys/deal.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/sys/number.cpp.obj
Instrument.exe: CMakeFiles/Instrument.dir/build.make
Instrument.exe: CMakeFiles/Instrument.dir/linklibs.rsp
Instrument.exe: CMakeFiles/Instrument.dir/objects1.rsp
Instrument.exe: CMakeFiles/Instrument.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable Instrument.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Instrument.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Instrument.dir/build: Instrument.exe

.PHONY : CMakeFiles/Instrument.dir/build

CMakeFiles/Instrument.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Instrument.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Instrument.dir/clean

CMakeFiles/Instrument.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\CLionProjects\Instrument E:\CLionProjects\Instrument E:\CLionProjects\Instrument\cmake-build-debug E:\CLionProjects\Instrument\cmake-build-debug E:\CLionProjects\Instrument\cmake-build-debug\CMakeFiles\Instrument.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Instrument.dir/depend

