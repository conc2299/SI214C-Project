#include "nedelecp1.h"
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

Mat3cd NedelecP1_2D::int_curl_dot_self()
{
    double abs_det_jac = abs(jacobian.determinant());

}

/*
    three shape function
    phi1(x,y) = (1-y,x)
    phi2(x,y) = (-y,x)
    phi3(x,y) = (y,1-x)
*/
Mat3cd NedelecP1_2D::int_dot_self()
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

Arr3cd NedelecP1_2D::int_dot(std::function<Vec2cd(const Pos2D&)> f)
{

}

std::array<std::size_t,3> NedelecP1_2D::get_mapping()
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
