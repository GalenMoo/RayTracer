# Ray Tracer
Ray tracer program that uses a camera point and rays to different material spheres

![cam](https://user-images.githubusercontent.com/25444917/108950916-eb5f0680-761b-11eb-9b2a-1a8b738a9db3.png) ![test_grey2](https://user-images.githubusercontent.com/25444917/108950867-d4201900-761b-11eb-952b-7e6b58317224.png)

<img src="https://user-images.githubusercontent.com/25444917/108958498-ed2ec700-7627-11eb-8b42-ee9c2f4d614d.png" width="800">




Due to the complex math of ray tracing, this project follows and uses the math of https://raytracing.github.io/.
The main difference between this project and the link is that I migrated logic from the .h files to a new respected .cpp.
CMake was also added.

# Rubric
## Loops, Functions, I/O
* The project demonstrates an understanding of C++ functions and control structures.
* The project reads data from a file and process the data, or the program writes data to a file.
* The project uses Object Oriented Programming techniques.

## Object Oriented Programming
* Classes use appropriate access specifiers for class members.
* Class constructors utilize member initialization lists.
* Classes abstract implementation details from their interfaces.
* Classes encapsulate behavior.

## Memory Management
* The project makes use of references in function declarations.
* The project uses smart pointers instead of raw pointers.

## Concurrency
No concurrency concepts were used.

# Features
* Customizable camera with adjustible height, aperature, focus distance, and vertical field of view
* Generatable spheres that can vary in size and position
* Dielectric and Metal material

# Build Requirements
* CMake/Make
* GCC

# Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

# Build Instructions
1. `make build`
2. `./raytracing > ../images/pic.ppm`
