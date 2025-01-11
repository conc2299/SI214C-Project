cmake_minimum_required(VERSION 3.10)
project(ComplexMatrixSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 设置不同平台的默认搜索路径
if(WIN32)
    # Windows平台的路径设置
    list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/armadillo")
    list(APPEND CMAKE_PREFIX_PATH "C:/Program Files/OpenBLAS")
    set(BLA_VENDOR OpenBLAS)  # 使用OpenBLAS
elseif(APPLE)
    # macOS平台的路径设置
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/armadillo")
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/openblas")
else()
    # Linux平台的路径设置
    list(APPEND CMAKE_PREFIX_PATH "/usr/local")
    list(APPEND CMAKE_PREFIX_PATH "/usr/lib")
endif()

# 查找必要的依赖包
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(Armadillo QUIET)

# 如果没有找到Armadillo，尝试手动设置路径
if(NOT Armadillo_FOUND)
    if(WIN32)
        set(ARMADILLO_INCLUDE_DIRS "C:/Program Files/armadillo/include")
        set(ARMADILLO_LIBRARIES "C:/Program Files/armadillo/lib/libarmadillo.lib")
    elseif(APPLE)
        set(ARMADILLO_INCLUDE_DIRS "/opt/homebrew/include")
        set(ARMADILLO_LIBRARIES "/opt/homebrew/lib/libarmadillo.dylib")
    else()
        set(ARMADILLO_INCLUDE_DIRS "/usr/include")
        set(ARMADILLO_LIBRARIES "/usr/lib/libarmadillo.so")
    endif()
    message(WARNING "未找到Armadillo包，使用默认路径")
endif()

# 添加包含目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${ARMADILLO_INCLUDE_DIRS}
)

# 创建库
add_library(complex_solver STATIC
    src/complex_solver.cpp
)

# 设置库的属性
set_target_properties(complex_solver PROPERTIES
    VERSION 1.0
    SOVERSION 1
    PUBLIC_HEADER "include/complex_solver.h"
)

# 链接库的依赖
target_link_libraries(complex_solver
    ${ARMADILLO_LIBRARIES}
    ${BLAS_LIBRARIES}
    ${LAPACK_LIBRARIES}
)

# 添加示例可执行文件
add_executable(complex_solver_example examples/main.cpp)
target_link_libraries(complex_solver_example complex_solver)

# 安装规则
install(TARGETS complex_solver complex_solver_example
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

# 打印调试信息
message(STATUS "操作系统: ${CMAKE_SYSTEM_NAME}")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "ARMADILLO_INCLUDE_DIRS: ${ARMADILLO_INCLUDE_DIRS}")
message(STATUS "ARMADILLO_LIBRARIES: ${ARMADILLO_LIBRARIES}")
message(STATUS "BLAS_LIBRARIES: ${BLAS_LIBRARIES}")
message(STATUS "LAPACK_LIBRARIES: ${LAPACK_LIBRARIES}")