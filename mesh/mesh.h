#ifndef MESH_H
#define MESH_H

#include <vector>
#include <map>

#include "basics/global.h"
#include "elements/nedelecp1.h"
#include "region/region.h"
#include "Eigen/Sparse"
#include "CDT/include/CDT.h"

class Mesh2D
{
public:
    Mesh2D(Pos2D ll, Pos2D ur, double omega): ll(ll), ur(ur), omega(omega){};
    void build_mesh_from_regions(const std::vector<Region2D*>& regions, const std::pair<std::size_t,std::size_t>& mesh_size);

    Eigen::SparseMatrix<std::complex<double>> calc_stiffness_mat();
    Eigen::VectorXcd calc_rhs(std::function<Vec2cd(const Pos2D&)> f);

    void print_field(const Eigen::VectorXcd& f);
    void clear();
    
private:
    std::vector<Pos2D> gen_vertices(const std::vector<Region2D*>& regions,const std::pair<std::size_t,std::size_t>& mesh_size) const;
    
    Pos2D ll, ur;
    std::size_t global_dof_num;
    std::vector<NedelecP1_2D> elements;
    /*
        electrical parameters for elements
    */
    std::vector<EParams> eparam;
    std::unordered_map<CDT::Edge,std::size_t> edge_to_dof_idx;
    std::vector<Pos2D> mesh_vertices;
    double omega;
};

#endif
