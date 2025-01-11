#include <armadillo>
#include <complex>
#include <iostream>

using namespace arma;
using namespace std;

class ComplexSolver {
public:
    // 默认构造函数，使用预设的示例
    ComplexSolver() {
        // 创建一个3x3的复数矩阵作为默认例子
        A = cx_mat(3, 3);
        A(0,0) = complex<double>(2.0, 1.0);  A(0,1) = complex<double>(1.0, 0.5);  A(0,2) = complex<double>(0.0, 0.3);
        A(1,0) = complex<double>(1.0, -0.5); A(1,1) = complex<double>(3.0, 0.0);  A(1,2) = complex<double>(2.0, 0.0);
        A(2,0) = complex<double>(0.0, -0.3); A(2,1) = complex<double>(2.0, 0.0);  A(2,2) = complex<double>(4.0, -1.0);

        // 创建默认的右端向量
        b = cx_vec(3);
        b(0) = complex<double>(1.0, 0.5);
        b(1) = complex<double>(2.0, -1.0);
        b(2) = complex<double>(3.0, 0.0);
    }

    // 使用给定的矩阵和向量构造
    ComplexSolver(const cx_mat& A_in, const cx_vec& b_in) : A(A_in), b(b_in) {
        if (A_in.n_rows != A_in.n_cols) {
            throw runtime_error("矩阵A必须是方阵");
        }
        if (A_in.n_rows != b_in.n_elem) {
            throw runtime_error("矩阵A的维度必须与向量b匹配");
        }
    }

    // 求解方程 Ax = b
    cx_vec solve() {
        cout << "\n=== 开始求解复数线性方程组 Ax = b ===\n\n";
        
        // 打印原始数据
        printSystem();

        // 修复：直接使用 arma::solve
        cx_vec x = arma::solve(A, b);

        // 检查解是否有效
        if (x.is_finite()) {
            cout << "\n求解成功！\n";
            printSolution(x);
            verifyResult(x);
        } else {
            cout << "\n求解失败！矩阵可能是奇异的。\n";
        }

        return x;
    }

private:
    cx_mat A;  // 系数矩阵
    cx_vec b;  // 右端向量

    // 打印方程系统
    void printSystem() {
        cout << "系数矩阵 A:\n" << A << "\n";
        cout << "右端向量 b:\n" << b << "\n";
    }

    // 打印解向量
    void printSolution(const cx_vec& x) {
        cout << "\n解向量 x:\n" << x << "\n";
    }

    // 验证结果
    void verifyResult(const cx_vec& x) {
        cx_vec residual = A * x - b;
        double rel_error = norm(residual) / norm(b);
        
        cout << "\n验证结果:\n";
        cout << "Ax = \n" << A * x << "\n";
        cout << "相对误差 ||Ax-b||/||b|| = " << rel_error << "\n";
    }
};

// 示例用法
int main() {
    try {
        // 使用默认例子
        cout << "=== 使用默认的复数矩阵示例 ===\n";
        ComplexSolver default_solver;
        cx_vec x1 = default_solver.solve();

        // 使用自定义的例子
        cout << "\n\n=== 使用自定义的复数矩阵示例 ===\n";
        cx_mat custom_A(2, 2);
        custom_A(0,0) = complex<double>(1.0, 0.0);  custom_A(0,1) = complex<double>(0.0, 1.0);
        custom_A(1,0) = complex<double>(0.0, -1.0); custom_A(1,1) = complex<double>(1.0, 0.0);

        cx_vec custom_b(2);
        custom_b(0) = complex<double>(1.0, 1.0);
        custom_b(1) = complex<double>(1.0, -1.0);

        ComplexSolver custom_solver(custom_A, custom_b);
        cx_vec x2 = custom_solver.solve();

    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }

    return 0;
}
