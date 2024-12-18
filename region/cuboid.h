#ifndef CUBOID_H
#define CUBOID_H

#include "region.h"

/*
    Cuboid 
*/
class Cuboid: public Region
{
public:
    Cuboid(POS3D corner1, POS3D corner2, double permeability, double permitivity);
    Cuboid(POS3D corner, double length, double width, double height, double permeability, double permitivity);
    bool is_interior(POS3D p);
    std::optional<POS3D> get_boundary_between(POS3D p1, POS3D p2);
private:
    POS3D corner1;
    POS3D corner2;
};

#endif