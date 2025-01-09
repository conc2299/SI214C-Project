#include "cuboid.h"

Cuboid2D::Cuboid2D(Pos2D corner1, Pos2D corner2, double permeability, double permitivity)
{
    this->corner1 = corner1;
    this->corner2 = corner2;
    this->permeability = permeability;
    this->permitivity = permitivity;
}

Cuboid2D::Cuboid2D(Pos2D corner, double length, double width, double permeability, double permitivity)
{
    this->permeability = permeability;
    this->permitivity = permitivity;
    this->corner1 = corner;
    double corner2_x = corner1.x + length;
    double corner2_y = corner1.y + width;
    double corner2_z = corner1.z + height;
}

bool Cuboid2D::is_interior(Pos2D p)
{
    return ((p.x-corner1.x) * (p.x - corner2.x) < 0) 
        && ((p.y-corner1.y) * (p.y - corner2.y) < 0)
        && ((p.z-corner1.z) * (p.z - corner2.z) < 0);
}

std::optional<Pos2D> Cuboid::get_boundary_between(Pos2D p1, Pos2D p2)
{
    //
    return std::nullopt;
}