# teensy-cpp-template
teensy-cpp-template aims to be a lightweight, hello-world template project for Teensy 4.0.

The project aims to support modern C++17, C99, & ASM code, while giving the developer the flexibility to use an IDE & OS of his or her choice.

People who are familiar with C++ CMake projects will feel right at home using this approach.

## Why CMake?
I chose CMake because it's what I'm familiar with. I like to switch between macOS, Linux and Windows frequently, I use multiple IDEs on a daily basis, and I couldn't find any other C++17 bare metal templates for Teensy 4.0.

## Features

- [x] Bare, low-level access to programming on the Teensy 4.0 MCU
- [x] C++17 compiling support (exceptions not supported)
- [x] C99 & ASM language & linking support
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

### Prerequisites

To compile and run code on the Teensy 4.0, you will first need to do 3 things on your development PC:

1. Install the [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. Install the latest [CMake](https://cmake.org/download/) and make sure the `cmake` command is in your path
3. Install [MinGW](http://www.mingw.org/) - this is needed for compiling Unix Makefiles

## Getting Started (macOS)  

### Prerequisites

Instead of downloading and installing all the prerequisite components manually, you can just use `brew` to install them.

To install homebrew, open up Terminal and type in the following command:  

      /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
      
Once homebrew is installed, you can continue and use the `brew` command to install the GNU Arm Embedded Toolchain and the `cmake` command:  

      brew tap ArmMbed/homebrew-formulae  
      brew install cmake arm-none-eabi-gcc

-OR-

You can install these components manually:

1. [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. [CMake](https://cmake.org/download/) and make sure the `cmake` command is in your path
3. [XCode](https://apps.apple.com/us/app/xcode/id497799835?mt=12) - Open the XCode app and install the additional command-line tools. This is needed for compiling Unix Makefiles (and actually, the XCode command-line tools are technically all that is needed, not the XCode app itself)

## Getting Started (Linux)  

### Prerequisites

Instead of downloading and installing all the prerequisite components manually, you can just use your distro's package manager to install them.

On Ubuntu or Debian-based distro:  

      sudo apt-get install cmake gcc-arm-none-eabi
      
On Fedora or RHL-based distro:

      sudo dnf install cmake gcc-arm-none-eabi binutils-arm-none-eabi

-OR-

You can install these components manually:

1. [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
2. [CMake](https://cmake.org/download/) and make sure the `cmake` command is in your path

## Compiling and Loading

Now you're ready to start coding! 

1. First step is to clone this repo **RECURSIVELY** so that the submodules get cloned as well:

        git clone --recursive https://github.com/itsermo/teensy-cpp-template

2. A simple script is provided to generate the project (macOS & Linux): 

        cd teensy-cpp-template/build
        ./generate.sh 
    
    or on Windows:
    
         cd teensy-cpp-template/build
         generate.bat
    
        
3. Build using the command (macOS & Linux):

        ./build.sh  
            
    or on Windows:
   
         build.bat
        
4. Finally you can load the program onto your Teensy 4.0 device using the command:

        ./flash.sh
        
      or on Windows:
   
         flash.bat
        
*NOTE: If you run `build.sh`, it will automatically generate a new project, if necessary, by calling `generate.sh` first.  
Likewise, `flash.sh` will call `generate.sh`, then `build.sh` and load your program onto the Teensy 4.0 using `teensy_loader_cli` binary in `submodules/teensy_loader_cli/bin` folder!*
    
