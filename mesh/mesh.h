#ifndef MESH_H
#define MESH_H

#include <vector>

#include "basics/global.h"
#include "elements/nedelecp1.h"
#include "region/region.h"

class Mesh2D
{
public:
    Mesh2D(Pos2D ll, Pos2D ur): ll(ll), ur(ur){};
    void build_mesh_from_regions(const std::vector<Region2D*>& regions, const std::pair<std::size_t,std::size_t>& mesh_size);
    void calc_stifness_mat();
    void clear();
private:
    std::vector<Pos2D> gen_vertices(const std::vector<Region2D*>& regions,const std::pair<std::size_t,std::size_t>& mesh_size) const;
    
    Pos2D ll, ur;
    std::vector<Complex> dof_coeff;
    std::vector<NedelecP1_2D> elements;
    /*
        electrical parameters for elements
    */
    std::vector<EParams> eparam;
};

#endif
