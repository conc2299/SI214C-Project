#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include "basics/global.h"

/*
    implement gaussian quadrature
*/
template <std::size_t N>
inline std::pair<std::array<Pos2D,N>,std::array<double,N>> gaussian_points()
{
    static_assert(false,"Not implemented");
}

template <>
inline std::pair<std::array<Pos2D,7>,std::array<double,7>> gaussian_points()
{
    return std::make_pair(
        std::array{
            Pos2D{1.0f/3,1.0f/3},
            Pos2D{0.797426985353087,0.101286507323456},
            Pos2D{0.101286507323456,0.797426985353087},
            Pos2D{0.101286507323456,0.101286507323456},
            Pos2D{0.470142064105115,0.059715871789770},
            Pos2D{0.059715871789770,0.470142064105115},
            Pos2D{0.470142064105115,0.470142064105115}
        },
        std::array{
            0.225000000000000 / 2,
            0.125939180544827 / 2,
            0.125939180544827 / 2,
            0.125939180544827 / 2,
            0.132394152788506 / 2,
            0.132394152788506 / 2,
            0.132394152788506 / 2
        }
    );
}

#endif