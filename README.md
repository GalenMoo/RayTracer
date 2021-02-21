# Linux System Monitor
htop system monitor clone for Linux.
Starter code provided by Udacity. GUI framework from ncurses library

# Features
* Displays OS, kernel, CPU utilization, memory utilization
  total processes, running processes, and up time.
* Process window displaying process stats organized based on CPU usaged

# Build Requirements
* Linux machine (ideally Ubuntu)
* C++
* CMake/Make
* ncurses

# Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts
