#include "complex_solver.h"
#include <iostream>

int main() {
    try {
        // 使用默认例子
        std::cout << "=== 使用默认的复数矩阵示例 ===\n";
        ComplexSolver default_solver;
        arma::cx_vec x1 = default_solver.solve();
        
        // 使用自定义的例子
        std::cout << "\n=== 使用自定义的复数矩阵示例 ===\n";
        arma::cx_mat custom_A(2, 2);
        custom_A(0,0) = std::complex<double>(1.0, 0.0);
        custom_A(0,1) = std::complex<double>(0.0, 1.0);
        custom_A(1,0) = std::complex<double>(0.0, -1.0);
        custom_A(1,1) = std::complex<double>(1.0, 0.0);

        arma::cx_vec custom_b(2);
        custom_b(0) = std::complex<double>(1.0, 1.0);
        custom_b(1) = std::complex<double>(1.0, -1.0);

        ComplexSolver custom_solver(custom_A, custom_b);
        arma::cx_vec x2 = custom_solver.solve();
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 