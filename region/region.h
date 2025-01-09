#ifndef REGION_H
#define REGION_H

#include "basics/global.h"

#include <optional>
#include <vector>

/*
    Abstract region class
*/
class Region2D
{
public:
    virtual bool is_interior(Pos2D)=0;
    virtual std::optional<Pos2D> get_boundary_between(Pos2D, Pos2D)=0;
    /*
        the minimal interval of the shape 
        i.e. min((x_max-x_min),(y_max-y_min))
    */
    virtual double get_minimal_interval()=0;
    virtual std::vector<Pos2D> get_vertices()=0;

protected:
    double permeability;
    double permitivity;
};

#endif