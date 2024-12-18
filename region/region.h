#ifndef REGION_H
#define REGION_H

#include "basics/pos.h"
#include "basics/vec.h"

#include <optional>

/*
    Abstract region class
*/
class Region
{
public:
    virtual bool is_interior(POS3D p)=0;
    virtual std::optional<POS3D> get_boundary_between(POS3D, POS3D)=0;

protected:
    double permeability;
    double permitivity;
};

#endif