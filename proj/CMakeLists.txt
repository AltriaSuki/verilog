cmake_minimum_required(VERSION 3.10)
project(VerilogCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug) # 启用Debug模式

# 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 收集所有 .cpp 文件
file(GLOB SRC_FILES src/*.cpp)

# 生成可执行文件
add_executable(verilog_compiler ${SRC_FILES})

# 添加调试符号和编译选项
target_compile_options(verilog_compiler PRIVATE -g -Wall)
