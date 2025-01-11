#pragma once
#include <armadillo>
#include <complex>
#include <string>

class ComplexSolver {
public:
    // 默认构造函数
    ComplexSolver();
    
    // 使用给定的矩阵和向量构造
    ComplexSolver(const arma::cx_mat& A, const arma::cx_vec& b);
    
    // 设置系数矩阵和右端向量
    void setSystem(const arma::cx_mat& A, const arma::cx_vec& b);
    
    // 求解方程 Ax = b
    arma::cx_vec solve(bool verbose = true);
    
    // 获取最后一次求解的相对误差
    double getLastError() const { return last_error_; }
    
    // 获取系统信息的字符串表示
    std::string getSystemInfo() const;
    
    // 验证解的正确性
    bool verifyResult(const arma::cx_vec& x, double tol = 1e-10);

private:
    arma::cx_mat A_;  // 系数矩阵
    arma::cx_vec b_;  // 右端向量
    double last_error_;  // 最后一次求解的相对误差
    
    // 检查矩阵和向量的维度是否匹配
    bool checkDimensions() const;
    
    // 创建默认的测试数据
    void createDefaultExample();
}; 