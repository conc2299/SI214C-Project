#include "complex_solver.h"
#include <sstream>
#include <iomanip>

ComplexSolver::ComplexSolver() {
    createDefaultExample();
}

ComplexSolver::ComplexSolver(const arma::cx_mat& A, const arma::cx_vec& b) {
    setSystem(A, b);
}

void ComplexSolver::setSystem(const arma::cx_mat& A, const arma::cx_vec& b) {
    A_ = A;
    b_ = b;
    if (!checkDimensions()) {
        throw std::runtime_error("矩阵维度不匹配");
    }
}

arma::cx_vec ComplexSolver::solve(bool verbose) {
    if (verbose) {
        std::cout << getSystemInfo() << std::endl;
    }
    
    arma::cx_vec x = arma::solve(A_, b_);
    
    if (!x.is_finite()) {
        throw std::runtime_error("求解失败：矩阵可能是奇异的");
    }
    
    if (verbose) {
        std::cout << "\n求解成功！" << std::endl;
        std::cout << "解向量 x:\n" << x << std::endl;
    }
    
    verifyResult(x);
    return x;
}

bool ComplexSolver::verifyResult(const arma::cx_vec& x, double tol) {
    arma::cx_vec residual = A_ * x - b_;
    last_error_ = arma::norm(residual) / arma::norm(b_);
    
    return last_error_ < tol;
}

std::string ComplexSolver::getSystemInfo() const {
    std::ostringstream oss;
    oss << "系统信息:\n"
        << "矩阵大小: " << A_.n_rows << "x" << A_.n_cols << "\n"
        << "条件数: " << arma::cond(A_) << "\n"
        << "系数矩阵 A:\n" << A_ << "\n"
        << "右端向量 b:\n" << b_ << "\n";
    return oss.str();
}

bool ComplexSolver::checkDimensions() const {
    return (A_.n_rows == A_.n_cols) && (A_.n_rows == b_.n_elem);
}

void ComplexSolver::createDefaultExample() {
    // 创建一个3x3的复数矩阵作为默认例子
    A_ = arma::cx_mat(3, 3);
    A_(0,0) = std::complex<double>(2.0, 1.0);
    A_(0,1) = std::complex<double>(1.0, 0.5);
    A_(0,2) = std::complex<double>(0.0, 0.3);
    A_(1,0) = std::complex<double>(1.0, -0.5);
    A_(1,1) = std::complex<double>(3.0, 0.0);
    A_(1,2) = std::complex<double>(2.0, 0.0);
    A_(2,0) = std::complex<double>(0.0, -0.3);
    A_(2,1) = std::complex<double>(2.0, 0.0);
    A_(2,2) = std::complex<double>(4.0, -1.0);

    b_ = arma::cx_vec(3);
    b_(0) = std::complex<double>(1.0, 0.5);
    b_(1) = std::complex<double>(2.0, -1.0);
    b_(2) = std::complex<double>(3.0, 0.0);
} 