#include "nedelecp1.h"

NedelecP1_2D::NedelecP1_2D(Pos2D p1, Pos2D p2, Pos2D p3,std::array<std::size_t,3> mapping)
{
    domain[0] = p1;
    domain[1] = p2;
    domain[2] = p3;
    dof_mapping = mapping;
}

Mat3cd NedelecP1_2D::int_curl_dot_self()
{

}

Mat3cd NedelecP1_2D::int_dot_self()
{
    
}

Arr3cd NedelecP1_2D::int_dot(std::function<Vec2cd(const Pos2D&)> f)
{

}

std::array<std::size_t,3> NedelecP1_2D::get_mapping()
{
    return dof_mapping;
}
