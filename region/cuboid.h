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
    Cuboid2D(Pos2D corner1, Pos2D corner2, Complex permeability, Complex permitivity);
    Cuboid2D(Pos2D corner, double length, double width, Complex permeability, Complex permitivity);
    bool is_interior(const Pos2D& p) const;
    std::optional<Pos2D> get_intersection(const Pos2D& p1, const Pos2D& p2) const;
    std::vector<Pos2D> get_vertices() const;
    EParams get_eparams() const;

    void set_frequency(double omega);  // 设置 ω
    double get_frequency() const;  
private:
    Pos2D corner1;
    Pos2D corner2;
};

#endif