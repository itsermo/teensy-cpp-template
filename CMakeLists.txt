cmake_minimum_required(VERSION 3.10)

# declare project name
project(teensy-cpp VERSION 0.1 LANGUAGES C CXX ASM)

# options
option(PRINT_SIZE_INFO_AFTER_LINK    "Prints verbose size info to stdout"       ON)

# Teensy Loader CLI command arguments options
option(TEENSY_LOADER_WAIT_TO_FLASH   "Waits on Teensy detection to flash"       ON)
option(TEENSY_LOADER_USE_HARD_REBOOT "Use hard reboot if Teensy is not online" OFF)
option(TEENSY_LOADER_USE_SOFT_REBOOT "Use soft reboot if device is not online" OFF)
option(TEENSY_LOADER_NO_REBOOT       "Do not reboot Teensy after programming"  OFF)
option(TEENSY_LOADER_BOOT_ONLY       "Boot Teensy only, do not program"        OFF)
option(TEENSY_LOADER_VERBOSE         "Enables or disables verbose output"       ON) 

# how to generate the flash command
# POST_BUILD     - adds a post-build command to your executable
# UTILITY_TARGET - creates a utility target with a post-build command
# NONE           - does not generate a flash command
set(TEENSY_LOADER_CLI_GENERATOR_TYPE "UTILITY_TARGET")

# set output path to /bin, /lib, etc.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY${${CMAKE_BUILD_TYPE}} ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${${CMAKE_BUILD_TYPE}} ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY${${CMAKE_BUILD_TYPE}} ${CMAKE_CURRENT_LIST_DIR}/lib)

# set the paths for our teensy firmware loader
# and the cmake arm embedded toolchain path
set(TEENSY_LOADER_SUBMODULE_PATH      ${CMAKE_CURRENT_LIST_DIR}/submodules/teensy_loader_cli)
set(CMAKE_ARM_EMBEDDED_SUBMODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/submodules/cmake-arm-embedded)

# set the linker script for our teensy 4.0 and include that beeoch's cmake toolchain flags
set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/etc/imxrt1062.ld")
include(${CMAKE_ARM_EMBEDDED_SUBMODULE_PATH}/teensy40.cmake)

set(IMXRT1062_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdparty/imxrt1062/include)
set(IMXRT1062_SRC_DIR     ${CMAKE_CURRENT_LIST_DIR}/3rdparty/imxrt1062/src)

# create a library from a 3rdparty code
add_library(imxrt1062 STATIC)
target_include_directories(imxrt1062 PUBLIC ${IMXRT1062_INCLUDE_DIR})
target_sources(imxrt1062 PUBLIC 
    ${IMXRT1062_INCLUDE_DIR}/imxrt1062.h        # the MCU include file, this holds all the register definitions, etc.
    ${IMXRT1062_INCLUDE_DIR}/imxrt1062-memory.h # fast assembly-based definitions of memset() and memcpy()

    PRIVATE
    ${IMXRT1062_SRC_DIR}/memcpy-armv7m.S        # fast memcpy() replacement specific to armv7m architecture
    ${IMXRT1062_SRC_DIR}/memset.S               # fast memset() replacement specific to arm architecture
)

# add our executable
add_embedded_arm_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} imxrt1062)

# our sources
set(PROJ_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(PROJ_SRC_DIR     ${CMAKE_CURRENT_LIST_DIR}/src)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJ_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJ_SRC_DIR}/teensy/bootdata.c       # lookup tables and memory signatures for booting
    ${PROJ_SRC_DIR}/teensy/startup.c        # the first C code that is run on the MCU, calls main()

    ${PROJ_SRC_DIR}/teensy/cpp-compat.cpp   # adds some missing primitive C++ functions
    ${PROJ_INCLUDE_DIR}/imxrt1062-chrono.h            # adds some primitive timer/delay functions based on CPU counter
    ${PROJ_SRC_DIR}/main.cpp                # our hello world code
)

if("${TEENSY_LOADER_CLI_GENERATOR_TYPE}" STREQUAL "POST_BUILD" OR "${TEENSY_LOADER_CLI_GENERATOR_TYPE}" STREQUAL "UTILITY_TARGET")
    include(${TEENSY_LOADER_SUBMODULE_PATH}/cmake/TeensyFlashTarget.cmake)
    if(WIN32)
        get_filename_component(TEENSY_LOADER_COMMAND ${TEENSY_LOADER_SUBMODULE_PATH}/bin/teensy_loader_cli.exe ABSOLUTE)
    else()
        get_filename_component(TEENSY_LOADER_COMMAND ${TEENSY_LOADER_SUBMODULE_PATH}/bin/teensy_loader_cli ABSOLUTE)
    endif()

    if("${TEENSY_LOADER_CLI_GENERATOR_TYPE}" STREQUAL "UTILITY_TARGET")
        add_teensy_flash_target(
            ${PROJECT_NAME}
            "imxrt1062"
            ${TEENSY_LOADER_WAIT_TO_FLASH}
            ${TEENSY_LOADER_USE_HARD_REBOOT}
            ${TEENSY_LOADER_USE_SOFT_REBOOT}
            ${TEENSY_LOADER_NO_REBOOT}
            ${TEENSY_LOADER_BOOT_ONLY}
            ${TEENSY_LOADER_VERBOSE}
        )
    elseif("${TEENSY_LOADER_CLI_GENERATOR_TYPE}" STREQUAL "POST_BUILD")
        add_teensy_flash_command(
            ${PROJECT_NAME}
            "imxrt1062"
            ${TEENSY_LOADER_WAIT_TO_FLASH}
            ${TEENSY_LOADER_USE_HARD_REBOOT}
            ${TEENSY_LOADER_USE_SOFT_REBOOT}
            ${TEENSY_LOADER_NO_REBOOT}
            ${TEENSY_LOADER_BOOT_ONLY}
            ${TEENSY_LOADER_VERBOSE}
        )
    endif()
endif()

