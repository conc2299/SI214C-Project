#ifndef CUBOID_H
#define CUBOID_H

#include "region.h"
#include "basics/global.h"

/*
    Cuboid 
*/
class Cuboid2D: public Region2D
{
public:
    Cuboid2D(Pos2D corner1, Pos2D corner2, double permeability, double permitivity);
    Cuboid2D(Pos2D corner, double length, double width, double permeability, double permitivity);
    bool is_interior(Pos2D p);
    std::optional<Pos2D> get_boundary_between(Pos2D p1, Pos2D p2);
    double get_minimal_interval();
    std::vector<Pos2D> get_vertices();
private:
    Pos2D corner1;
    Pos2D corner2;
};

#endif