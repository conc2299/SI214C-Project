#include "basics/pos.h"
#include "cuboid.h"

Cuboid::Cuboid(POS3D corner1, POS3D corner2, double permeability, double permitivity)
{
    this->corner1 = corner1;
    this->corner2 = corner2;
    this->permeability = permeability;
    this->permitivity = permitivity;
}

Cuboid::Cuboid(POS3D corner, double length, double width, double height, double permeability, double permitivity)
{
    this->permeability = permeability;
    this->permitivity = permitivity;
    this->corner1 = corner;
    double corner2_x = corner1.x + length;
    double corner2_y = corner1.y + width;
    double corner2_z = corner1.z + height;
}

bool Cuboid::is_interior(POS3D p)
{
    return ((p.x-corner1.x) * (p.x - corner2.x) < 0) 
        && ((p.y-corner1.y) * (p.y - corner2.y) < 0)
        && ((p.z-corner1.z) * (p.z - corner2.z) < 0);
}

std::optional<POS3D> Cuboid::get_boundary_between(POS3D p1, POS3D p2)
{
    //
    return std::nullopt;
}