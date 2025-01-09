#ifndef GLOBAL_H
#define GLOBAL_H

#include <complex>

#include "Eigen/Dense"
#include "pos.hpp"

using Pos2D = Eigen::Array2d;
using Mat3cd = Eigen::Matrix3cd; 

using Arr3cd = Eigen::Array3cd;
using Vec3cd = Eigen::Array3cd;
using Vec2cd = Eigen::Array2cd;

using Complex = std::complex<double>;

#endif