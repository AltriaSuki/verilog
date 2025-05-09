cmake_minimum_required(VERSION 3.10)
project(VerilogCompiler)

# 设置 C++20 标准并强制启用
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # <-- 推荐添加，防止降级
set(CMAKE_CXX_EXTENSIONS OFF)        # <-- 可选：禁止 GNU 扩展（如 -std=gnu++20）

# 设置 Debug 模式
set(CMAKE_BUILD_TYPE Debug)

# 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 收集源文件
file(GLOB SRC_FILES src/*.cpp)

# 可执行文件
add_executable(verilog_compiler ${SRC_FILES})

# 编译选项：开启调试符号和警告信息
target_compile_options(verilog_compiler PRIVATE -g -Wall)
