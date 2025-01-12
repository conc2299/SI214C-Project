#include "nedelecp1.h"
#include "quadrature/gaussian.hpp"

#include <algorithm>
#include <iostream>

NedelecP1_2D::NedelecP1_2D(Pos2D p1, Pos2D p2, Pos2D p3,std::array<std::size_t,3> mapping)
{
    domain[0] = p1;
    domain[1] = p2;
    domain[2] = p3;
    dof_mapping = mapping;
    Pos2D v1 = p2 - p1;
    Pos2D v2 = p3 - p1;
    jacobian = Mat2d{{v1[0],v2[0]},{v1[1],v2[1]}};
}

/*
    three shape function
    phi1(x,y) = (1-y,x)
    phi2(x,y) = (-y,x)
    phi3(x,y) = (y,1-x)
*/
Mat3cd NedelecP1_2D::int_curl_dot_self() const
{
    double abs_det_jac = abs(jacobian.determinant());
    Mat3cd result;
    result(0,0) = 2 / abs_det_jac;
    result(0,1) = 2 / abs_det_jac;
    result(1,0) = result(0,1);
    result(0,2) = -2 / abs_det_jac;
    result(2,0) = result(0,2);
    result(1,1) = 2 / abs_det_jac;
    result(1,2) = -2 / abs_det_jac;
    result(2,1) = result(1,2);
    result(2,2) = 2 / abs_det_jac;
    return result;
}

Mat3cd NedelecP1_2D::int_dot_self() const
{
    double abs_det_jac = abs(jacobian.determinant());
    Mat2d inv_transpose_jac = jacobian.inverse().transpose();
    Eigen::Matrix<Complex,1,2> line0 = inv_transpose_jac(0,Eigen::placeholders::all);
    Eigen::Matrix<Complex,1,2> line1 = inv_transpose_jac(1,Eigen::placeholders::all);
    Mat2cd mult = line0.transpose() * line0 + line1.transpose() * line1;
    Mat3cd result;
    //
    Arr22cd mat11 {{1.0f/4,1.0f/8},{1.0f/8,1.0f/12}};
    result(0,0) = abs_det_jac * (mult.array() * mat11).sum();
    //
    Arr22cd mat12{{-1.0f/12,1.0f/8},{-1.0f/24,1.0f/12}};
    result(0,1) = abs_det_jac * (mult.array() * mat12).sum();
    result(1,0) = result(0,1);
    //
    Arr22cd mat13{{1.0f/12,5.0f/24},{1.0f/24,1.0f/12}};
    result(0,2) = abs_det_jac * (mult.array() * mat13).sum();
    result(2,0) = result(0,2);
    //
    Arr22cd mat22{{1.0f/12,-1.0f/24},{-1.0f/24,1.0f/12}};
    result(1,1) = abs_det_jac * (mult.array() * mat22).sum();
    //
    Arr22cd mat23{{-1.0f/12,-1.0f/8},{1.0f/24,1.0f/12}};
    result(1,2) = abs_det_jac * (mult.array() * mat23).sum();
    result(2,1) = result(1,2);
    //
    Arr22cd mat33{{1.0f/12,1.0f/8},{1.0f/8,1.0f/4}};
    result(2,2) = abs_det_jac * (mult.array() * mat33).sum();
    return result;
}

// using gaussian quadrature
Arr3cd NedelecP1_2D::int_dot(std::function<Vec2cd(const Pos2D&)> f) const
{
    auto points_and_weights = gaussian_points<7>();
    auto points = points_and_weights.first;
    auto weights = points_and_weights.second;

    Arr3cd result;
    result << 0,0,0;
    double abs_det_jac = abs(jacobian.determinant());
    Mat2d inv_transpose_jac = jacobian.inverse().transpose();

    Eigen::Matrix<Complex,2,7> f_x;
    Eigen::Matrix<Complex,2,7> phi1_x;
    Eigen::Matrix<Complex,2,7> phi2_x;
    Eigen::Matrix<Complex,2,7> phi3_x;
    Eigen::Matrix<Complex,2,7> arr_weight;

    // initialize array
    for(std::size_t i = 0; i < 7; i++){
        const Pos2D& p = points[i];
        Pos2D p_f = Pos2D{domain[0](0) + jacobian(0,0)*p(0) + jacobian(0,1) * p(1),domain[0](1) + jacobian(1,0)*p(0) + jacobian(1,1) * p(1)};
        Vec2cd f_xi = f(p_f);
        f_x(0,i) = f_xi(0);
        f_x(1,i) = f_xi(1);
        phi1_x(0,i) = 1-p(1);
        phi1_x(1,i) = p(0);
        phi2_x(0,i) = -p(1);
        phi2_x(1,i) = p(0);
        phi3_x(0,i) = p(1);
        phi3_x(1,i) = 1-p(0);
        arr_weight(0,i) = weights[i];
        arr_weight(1,i) = weights[i];
    }
    result(0) = inv_transpose_jac.cwiseProduct(f_x.cwiseProduct(arr_weight) * phi1_x.transpose()).sum();
    result(1) = inv_transpose_jac.cwiseProduct(f_x.cwiseProduct(arr_weight) * phi2_x.transpose()).sum();
    result(2) = inv_transpose_jac.cwiseProduct(f_x.cwiseProduct(arr_weight) * phi3_x.transpose()).sum();
    return result * abs_det_jac / 2;
}

std::array<std::size_t,3> NedelecP1_2D::get_mapping() const
{
    return dof_mapping;
}

void NedelecP1_2D::print_element_info()
{
    std::cout << "vertices:" << std::endl;
    for(auto p:domain){
        std::cout << "(" << p[0] << "," << p[1] << ")" << std::endl;
    }
    std::cout << "edge mapping:" << std::endl;
    for(auto m:dof_mapping){
        std::cout << m << " ";
    }
    std::cout << std::endl; 
    std::cout << "jacobian:" << std::endl;
    std::cout << jacobian << std::endl; 
    std::cout << std::endl; 
}
