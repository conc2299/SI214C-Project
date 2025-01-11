#ifndef GLOBAL_H
#define GLOBAL_H

#include <complex>

#include "Eigen/Dense"
#include "pos.hpp"

using Pos2D = Eigen::Array2d;
using Vec2D = Eigen::Array2d;
using Mat3cd = Eigen::Matrix3cd; 
using Mat2cd = Eigen::Matrix2cd; 
using Mat2d = Eigen::Matrix2d; 

using Arr3cd = Eigen::Array3cd;
using Arr22cd = Eigen::Array22cd;
using Vec3cd = Eigen::Vector3cd;
using Vec2cd = Eigen::Vector2cd;

using Complex = std::complex<double>;

struct EParams
{
    Complex epsilon;
    Complex mu;
    EParams(): epsilon(Complex{1,0}),mu(Complex{1,0}) {};
    EParams(Complex permitivity, Complex permeability)
    : epsilon(permitivity), mu(permeability){};
};

#endif