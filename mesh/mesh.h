#ifndef MESH_H
#define MESH_H

#include <vector>

#include "basics/global.h"
#include "elements/nedelecp1.h"
#include "region/region.h"

struct EParams
{
    Complex epsilon;
    Complex mu;
    EParams(Complex permitivity, Complex permeability)
    : epsilon(permitivity), mu(permeability){};
};

class Mesh2D
{
public:
    Mesh2D(Pos2D ll, Pos2D ur): ll(ll), ur(ur){};
    void build_mesh_from_regions(const std::vector<Region2D*>& regions, std::pair<double,double> mesh_size);
    void test();
private:
    Pos2D ll, ur;
    std::vector<Complex> dof_coeff;
    std::vector<NedelecP1_2D> elements;
    /*
        electrical parameters for elements
    */
    std::vector<EParams> eparam;
};

#endif
