cmake_minimum_required(VERSION 3.0.0)
project(CppCommon VERSION 0.1.0)
enable_language(ASM_MASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
# 1. 设置编译变量
set(INCLUDE_PATH ../include)
set(SRC_PATH ../src)
set(UNITS_TEST_PATH ../unittest)
set(RELEASE_PATH ../Build/bin)
set(Lib_Path ../Build/lib)
# 2. 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${RELEASE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${RELEASE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${Lib_Path})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RLEASE 	${Lib_Path})
# 3. 添加文件目录
include_directories(${INCLUDE_PATH})
include_directories(${SRC_PATH})
# 4. 添加Common源码
file(GLOB CommonSrc ${SRC_PATH}/*.hpp ${SRC_PATH}/*.cpp)
# 5. 编译d2hackmap
include(d2hackmap.cmake)


