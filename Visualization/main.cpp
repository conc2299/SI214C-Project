#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cmath>

const double PI = 3.14159265358979323846;

// 生成二维电磁场数据
std::vector<std::vector<std::complex<double> > > generateFieldMatrix(int nx, int ny) {
    std::vector<std::vector<std::complex<double> > > field(ny, std::vector<std::complex<double> >(nx));
    
    // 创建坐标网格
    double dx = 10.0 / (nx - 1);
    double dy = 10.0 / (ny - 1);
    
    for (int i = 0; i < ny; ++i) {
        for (int j = 0; j < nx; ++j) {
            // 将坐标转换为中心化的坐标系统
            double x = -5.0 + j * dx;
            double y = -5.0 + i * dy;
            
            // 计算到原点的距离
            double r = std::sqrt(x*x + y*y);
            double eps = 0.1; // 避免除零
            
            // 点电荷场
            std::complex<double> E_point(x / (std::pow(r + eps, 2)), 
                                       y / (std::pow(r + eps, 2)));
            
            // 波场参数
            double k1 = 2.0; // 波数
            double sigma = 2.0; // 高斯包络宽度
            
            // 计算两个相向传播的波
            std::complex<double> wave1 = std::exp(-((x-2)*(x-2) + y*y)/(2*sigma*sigma)) * 
                                       std::exp(std::complex<double>(0, k1*x));
            std::complex<double> wave2 = std::exp(-((x+2)*(x+2) + y*y)/(2*sigma*sigma)) * 
                                       std::exp(std::complex<double>(0, -k1*x));
            
            // 合成场
            field[i][j] = E_point + 0.5 * (wave1 + wave2);
        }
    }
    
    // 归一化场
    double max_magnitude = 0.0;
    for (const auto& row : field) {
        for (const auto& val : row) {
            max_magnitude = std::max(max_magnitude, std::abs(val));
        }
    }
    
    for (auto& row : field) {
        for (auto& val : row) {
            val /= max_magnitude;
        }
    }
    
    return field;
}

int main() {
    const int nx = 100;
    const int ny = 100;
    
    // 生成场数据
    auto field_matrix = generateFieldMatrix(nx, ny);
    
    // 将数据保存到文件
    std::ofstream outFile("field_matrix.txt");
    if (!outFile) {
        std::cerr << "无法创建输出文件！" << std::endl;
        return 1;
    }
    
    // 首先写入矩阵维度
    outFile << ny << " " << nx << "\n";
    
    // 写入数据，每行一个复数，格式：实部 虚部
    for (const auto& row : field_matrix) {
        for (const auto& val : row) {
            outFile << val.real() << " " << val.imag() << "\n";
        }
    }
    
    std::cout << "场数据已成功生成并保存到 field_matrix.txt" << std::endl;
    return 0;
}
