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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/klames/CPPProjects/Arduino/FullDuplex2/Computer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Computer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Computer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Computer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Computer.dir/flags.make

CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o: CMakeFiles/Computer.dir/flags.make
CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o: /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/FullDuplexComputer.cpp
CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o: CMakeFiles/Computer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o -MF CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o.d -o CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o -c /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/FullDuplexComputer.cpp

CMakeFiles/Computer.dir/FullDuplexComputer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Computer.dir/FullDuplexComputer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/FullDuplexComputer.cpp > CMakeFiles/Computer.dir/FullDuplexComputer.cpp.i

CMakeFiles/Computer.dir/FullDuplexComputer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Computer.dir/FullDuplexComputer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/FullDuplexComputer.cpp -o CMakeFiles/Computer.dir/FullDuplexComputer.cpp.s

CMakeFiles/Computer.dir/SerialPort.cpp.o: CMakeFiles/Computer.dir/flags.make
CMakeFiles/Computer.dir/SerialPort.cpp.o: /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/SerialPort.cpp
CMakeFiles/Computer.dir/SerialPort.cpp.o: CMakeFiles/Computer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Computer.dir/SerialPort.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Computer.dir/SerialPort.cpp.o -MF CMakeFiles/Computer.dir/SerialPort.cpp.o.d -o CMakeFiles/Computer.dir/SerialPort.cpp.o -c /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/SerialPort.cpp

CMakeFiles/Computer.dir/SerialPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Computer.dir/SerialPort.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/SerialPort.cpp > CMakeFiles/Computer.dir/SerialPort.cpp.i

CMakeFiles/Computer.dir/SerialPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Computer.dir/SerialPort.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/SerialPort.cpp -o CMakeFiles/Computer.dir/SerialPort.cpp.s

CMakeFiles/Computer.dir/Frame.cpp.o: CMakeFiles/Computer.dir/flags.make
CMakeFiles/Computer.dir/Frame.cpp.o: /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Frame.cpp
CMakeFiles/Computer.dir/Frame.cpp.o: CMakeFiles/Computer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Computer.dir/Frame.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Computer.dir/Frame.cpp.o -MF CMakeFiles/Computer.dir/Frame.cpp.o.d -o CMakeFiles/Computer.dir/Frame.cpp.o -c /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Frame.cpp

CMakeFiles/Computer.dir/Frame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Computer.dir/Frame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Frame.cpp > CMakeFiles/Computer.dir/Frame.cpp.i

CMakeFiles/Computer.dir/Frame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Computer.dir/Frame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Frame.cpp -o CMakeFiles/Computer.dir/Frame.cpp.s

CMakeFiles/Computer.dir/Queue.cpp.o: CMakeFiles/Computer.dir/flags.make
CMakeFiles/Computer.dir/Queue.cpp.o: /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Queue.cpp
CMakeFiles/Computer.dir/Queue.cpp.o: CMakeFiles/Computer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Computer.dir/Queue.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Computer.dir/Queue.cpp.o -MF CMakeFiles/Computer.dir/Queue.cpp.o.d -o CMakeFiles/Computer.dir/Queue.cpp.o -c /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Queue.cpp

CMakeFiles/Computer.dir/Queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Computer.dir/Queue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Queue.cpp > CMakeFiles/Computer.dir/Queue.cpp.i

CMakeFiles/Computer.dir/Queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Computer.dir/Queue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/Queue.cpp -o CMakeFiles/Computer.dir/Queue.cpp.s

CMakeFiles/Computer.dir/HardWareReferenz.cpp.o: CMakeFiles/Computer.dir/flags.make
CMakeFiles/Computer.dir/HardWareReferenz.cpp.o: /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/HardWareReferenz.cpp
CMakeFiles/Computer.dir/HardWareReferenz.cpp.o: CMakeFiles/Computer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Computer.dir/HardWareReferenz.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Computer.dir/HardWareReferenz.cpp.o -MF CMakeFiles/Computer.dir/HardWareReferenz.cpp.o.d -o CMakeFiles/Computer.dir/HardWareReferenz.cpp.o -c /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/HardWareReferenz.cpp

CMakeFiles/Computer.dir/HardWareReferenz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Computer.dir/HardWareReferenz.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/HardWareReferenz.cpp > CMakeFiles/Computer.dir/HardWareReferenz.cpp.i

CMakeFiles/Computer.dir/HardWareReferenz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Computer.dir/HardWareReferenz.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/HardWareReferenz.cpp -o CMakeFiles/Computer.dir/HardWareReferenz.cpp.s

# Object files for target Computer
Computer_OBJECTS = \
"CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o" \
"CMakeFiles/Computer.dir/SerialPort.cpp.o" \
"CMakeFiles/Computer.dir/Frame.cpp.o" \
"CMakeFiles/Computer.dir/Queue.cpp.o" \
"CMakeFiles/Computer.dir/HardWareReferenz.cpp.o"

# External object files for target Computer
Computer_EXTERNAL_OBJECTS =

Computer: CMakeFiles/Computer.dir/FullDuplexComputer.cpp.o
Computer: CMakeFiles/Computer.dir/SerialPort.cpp.o
Computer: CMakeFiles/Computer.dir/Frame.cpp.o
Computer: CMakeFiles/Computer.dir/Queue.cpp.o
Computer: CMakeFiles/Computer.dir/HardWareReferenz.cpp.o
Computer: CMakeFiles/Computer.dir/build.make
Computer: CMakeFiles/Computer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Computer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Computer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Computer.dir/build: Computer
.PHONY : CMakeFiles/Computer.dir/build

CMakeFiles/Computer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Computer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Computer.dir/clean

CMakeFiles/Computer.dir/depend:
	cd /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/klames/CPPProjects/Arduino/FullDuplex2/Computer /home/klames/CPPProjects/Arduino/FullDuplex2/Computer /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug /home/klames/CPPProjects/Arduino/FullDuplex2/Computer/cmake-build-debug/CMakeFiles/Computer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Computer.dir/depend

