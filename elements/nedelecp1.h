#ifndef NEDELECP1_H
#define NEDELECP1_H

#include <array>
#include <functional>

#include "basics/global.h"
/*
    Using standard definition by Ciarlet 1976
    1. Domain T
        triangle
    2. Local function space V(T)

    3. Degree of freedom(DOF) L
        |dof| = 3
*/
class NedelecP1_2D
{
public:
    NedelecP1_2D() = default;
    // should be ordered in vertice idx
    NedelecP1_2D(Pos2D p1, Pos2D p2, Pos2D p3, std::array<std::size_t,3> mapping);

    /*
        calculate the int-curl-dot values
    */
    Mat3cd int_curl_dot_self();

    /*
        calculate the int-dot values
    */
    Mat3cd int_dot_self();
    Arr3cd int_dot(std::function<Vec2cd(const Pos2D&)> f);
    std::array<std::size_t,3> get_mapping();
    void print_element_info();
private:
    /*
        Triangle Domain
        p1p2 : phi1
        p2p3 : phi2
        p1p3 : phi3
    */
    std::array<Pos2D,3> domain;
    // maps the local dof to global dof
    std::array<std::size_t,3> dof_mapping;
    Mat2d jacobian;
};

#endif