#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include "basics/global.h"

/*
    implement gaussian quadrature
*/
template <std::size_t N>
inline constexpr std::pair<std::array<Pos2D,N>,Eigen::Array<double,1,N>> gaussian_points()
{
    static_assert(false,"Not implemented");
}

inline constexpr std::pair<std::array<Pos2D,7>,Eigen::Array<double,1,7>> gaussian_points()
{
    return std::make_pair(
        std::array{
            Pos2D{},
            Pos2D{},
            Pos2D{},
            Pos2D{},
            Pos2D{},
            Pos2D{},
            Pos2D{},
            Pos2D{},
        },
        Eigen::Array{

        }
    );
}

#endif