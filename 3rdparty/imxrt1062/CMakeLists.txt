project(imxrt1062 LANGUAGES C CXX ASM)

# create a library from a 3rdparty code
add_library(imxrt1062 STATIC)
target_include_directories(imxrt1062 PUBLIC ${IMXRT1062_INCLUDE_DIR})
target_sources(imxrt1062 PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/include/imxrt1062.h         # the MCU include file, this holds all the register definitions, etc.
                                 ${CMAKE_CURRENT_LIST_DIR}/include/imxrt1062-memory.h  # fast assembly-based definitions of memset() and memcpy()

                         PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/memcpy-armv7m.S         # fast memcpy() replacement specific to armv7m architecture
                                 ${CMAKE_CURRENT_LIST_DIR}/src/memset.S                # fast memset() replacement specific to arm architecture
)
target_include_directories(imxrt1062 PUBLIC include)