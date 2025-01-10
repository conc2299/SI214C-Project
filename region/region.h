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
    virtual bool is_interior(const Pos2D&) const = 0;
    virtual std::optional<Pos2D> get_intersection(const Pos2D&,const Pos2D&) const = 0;
    /*
        the minimal interval of the shape 
        i.e. min((x_max-x_min),(y_max-y_min))
    */
    virtual std::vector<Pos2D> get_vertices() const = 0;
    virtual EParams get_eparams() const = 0;

protected:
    Complex permeability;
    Complex permitivity;
};

#endif