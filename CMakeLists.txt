cmake_minimum_required(VERSION 3.10)
project(SwigGoDemo)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# 设置包名和源目录
set(PACKAGE_NAME calculator)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 添加包含目录
include_directories(${SRC_DIR})

# 添加C++源文件
set(CPP_SOURCES
    ${SRC_DIR}/calculator.cpp
)

# 设置SWIG选项
set_source_files_properties(${SRC_DIR}/calculator.i PROPERTIES
    CPLUSPLUS ON
    SWIG_FLAGS "-intgosize;64"
)

set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}")

# 添加SWIG模块
swig_add_library(${PACKAGE_NAME}
    LANGUAGE go
    TYPE SHARED
    SOURCES ${SRC_DIR}/calculator.i ${CPP_SOURCES}
)

# 设置输出目录
set_target_properties(${PACKAGE_NAME} PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}"
    SWIG_OUTDIR "${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}"
)

add_custom_command(
    TARGET ${PACKAGE_NAME}
    POST_BUILD

    # 确保目标目录存在
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}

    # 使用更明确的源路径进行复制
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/src/calculator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/go/${PACKAGE_NAME}/calculator.h
    COMMENT "Copying calculator.h to Go package directory"
)
