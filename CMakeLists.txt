CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT("ovx_1.1")

###########################################################
# Building Options
###########################################################
option(BUILD_UNITTEST      "Build unittest"                     ON)
option(BUILD_DEBUG         "Build debug information"            ON)
option(BUILD_MEM_ANALYSIS  "Build memory analysis profiling"    ON)
option(BUILD_C_MODEL       "Build c_model target"               ON)
option(BUILD_OPENCL        "Build OpenCL target"                OFF)

###########################################################
# Android Platform
###########################################################
IF(${TARGET} MATCHES "aarch64")
SET(NDK_STANDALONE_TOOLCHAIN /home/tixlo/OpenVX/standalone-toolchain)
SET(CMAKE_SYSTEM_NAME Android)
SET(CMAKE_C_COMPILER ${NDK_STANDALONE_TOOLCHAIN}/bin/aarch64-linux-android-gcc)
SET(CMAKE_CXX_COMPILER ${NDK_STANDALONE_TOOLCHAIN}/bin/aarch64-linux-android-g++)
SET(SYSROOT ${NDK_STANDALONE_TOOLCHAIN}/sysroot)
SET(CMAKE_FIND_ROOT_PATH ${NDK_STANDALONE_TOOLCHAIN})
ENDIF()

###########################################################
# Android Platform
###########################################################
IF(${CMAKE_SYSTEM_NAME} MATCHES "Android")
ADD_DEFINITIONS("--sysroot=${SYSROOT}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -fPIE -D__ANDROID__")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIE -pie -D__ANDROID__")

SET(INCLUDE_INDEPENDENT_DIR ${CMAKE_CURRENT_LIST_DIR}/platforms/linux)
SET(LINK_LIBS linux-platform)
SET(PLATFORM_INDEPENDENT_DIR platforms/linux)
ENDIF()

###########################################################
# Linux-x86 Platform
###########################################################
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -D__LINUX__")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -D__LINUX__")
SET(INCLUDE_INDEPENDENT_DIR ${CMAKE_CURRENT_LIST_DIR}/platforms/linux)
SET(LINK_LIBS linux-platform)
SET(PLATFORM_INDEPENDENT_DIR platforms/linux)
ENDIF()

###########################################################
# windows Platform
###########################################################
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
SET(INCLUDE_INDEPENDENT_DIR ${CMAKE_CURRENT_LIST_DIR}/platforms/win)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__WIN32__")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__WIN32__")
SET(LINK_LIBS win-platform)
SET(PLATFORM_INDEPENDENT_DIR platforms/win)
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/platforms/include
                    ${CMAKE_CURRENT_LIST_DIR}/include/internal
                    ${CMAKE_CURRENT_LIST_DIR}/include
                    ${INCLUDE_INDEPENDENT_DIR})

SET(LINK_LIBS -Wl,--start-group
              ${LINK_LIBS} 
              openvx
              -Wl,--end-group)

###########################################################
# Add specific compiling flags for different options
###########################################################
IF(BUILD_DEBUG)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_DEBUG -g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_DEBUG -g")
ENDIF()

IF(BUILD_MEM_ANALYSIS)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_MEM_ANALYSIS")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_MEM_ANALYSIS")
ENDIF()

###########################################################
# Add all target subdirectories
###########################################################
IF(BUILD_C_MODEL)
ADD_SUBDIRECTORY(targets/c_model)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_C_MODEL")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_C_MODEL")
SET(LINK_LIBS ${LINK_LIBS} openvx-c_model)
ENDIF()

IF(BUILD_OPENCL)
ADD_SUBDIRECTORY(targets/opencl)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_OPENCL")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_OPENCL")
SET(LINK_LIBS ${LINK_LIBS} openvx-opencl)
ENDIF()

IF(BUILD_UNITTEST)
ADD_SUBDIRECTORY(unittest)
ENDIF()

###########################################################
# Add all subdirectories
###########################################################
ADD_SUBDIRECTORY(framework)
ADD_SUBDIRECTORY(${PLATFORM_INDEPENDENT_DIR})
ADD_SUBDIRECTORY(sample)

###########################################################
# show configuration
###########################################################
MESSAGE("-- General configuration for mtkovx --")
MESSAGE("-- Version : 1.0 ")
MESSAGE("-- Platform :")
MESSAGE("    Host                  :" ${CMAKE_HOST_SYSTEM_NAME} ${CMAKE_HOST_SYSTEM_VERSION} ${CMAKE_HOST_SYSTEM_PROCESSOR})
MESSAGE("    Target                :" ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION} ${CMAKE_SYSTEM_PROCESSOR})
MESSAGE("    C++ Compiler          :" ${CMAKE_CXX_COMPILER})
MESSAGE("    C Compiler            :" ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1})
MESSAGE("")
MESSAGE("-- Options :")
MESSAGE("    build debug           :" ${BUILD_DEBUG})
MESSAGE("    build memory analysis :" ${BUILD_MEM_ANALYSIS})
MESSAGE("    build unittest        :" ${BUILD_UNITTEST})
MESSAGE("    build c_model         :" ${BUILD_C_MODEL})
MESSAGE("    build OpenCL          :" ${BUILD_OPENCL})
