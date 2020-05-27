# teensy-cpp-template
teensy-cpp-template aims to be a lightweight modern C++ hello-world starter project for Teensy 4.0 that.  The project supports modern C++17, C99, ASM and yet also gives the developer flexibility to use an IDE & OS of his or her choice.

People who have used C++ with CMake extensively to write cross-platform code will feel right at home using this approach to write code for Teensy 4.0.

## Why CMake?
I chose CMake because it's what I'm familiar with. I like to switch between macOS, Linux and Windows frequently, I use multiple IDEs on a daily basis, and I couldn't find any other C++17 bare metal templates for Teensy 4.0.

## Features

- [x] Bare low-level access to programming on the Teensy 4.0 MCU
- [x] C++17 compiling support (exceptions not supported)
- [x] Write Teensy 4.0 C++ code on any OS and IDE
- [x] Load your code onto the Teensy 4.0 directly from the IDE
- [ ] TODO: Easy onboarding to build and load your first bit of code
- [ ] TODO: Easy debugging with JTAG instrument (seems to not be possible at the moment)

## Project Layout

The project consists of 3 components:

1. The source code:  
    * **src**      - The `main.cpp` file, which has the code, and `teensy` subfolder containing startup/boot code  
    * **include**  - `chrono.h` functions for delaying code execution based on accurate cycle-counting  
    * **3rdparty** - Header for the imxrt1062 MCU on the Teensy 4.0 and some support code    
    * **etc**      - Contains the necessary linker script for the imxrt1062 MCU  
    * **build**    - Convenience scripts that call the `cmake` command using proper arguments to generate a project, build and flash the binary to your Teensy 4.0 device
    
2. The loader:
    * **submodules/teensy_loader_cli** - The code for the loader.
    This must be properly compiled if you plan on actually *using* the code you've compiled on your Teensy 4.0
        
3. The CMake toolchain:
    * **submodules/cmake-arm-embedded** A GCC for Embedded ARM CMake Toolchain.
    This is just reference code that the CMakeLists.txt file uses to generate the project.
        
## Getting Started (Windows)

To compile and run code on the Teensy 4.0, you will first need to do 3 things on your development PC:

1. Install the [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. Install the latest [CMake](https://cmake.org/download/) and make sure the `cmake` command is in your path
3. Install [MinGW](http://www.mingw.org/) - this is needed for compiling Unix Makefiles

Now you're ready to get started!

1. First step is to clone this repo **RECURSIVELY** so that the submodules get cloned as well:

        git clone --recursive https://github.com/itsermo/teensy-cpp-template

2. A simple script is provided to generate the project: 

        cd teensy-cpp-template\build
        generate.bat  
        
3. Build using the command:

        build.bat
        
4. Finally you can flash using the command:

        flash.bat
        
*NOTE: If you run build.bat, it will automatically generate a new project if necessary. Likewise, flash.bat will generate, build and flash!*
    
