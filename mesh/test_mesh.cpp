#include <iostream>
#include "mesh.h"
#include "region/cuboid.h"

#define EPS0 8.854E-12
#define MU0 1.257E-6

int main()
{
    Mesh2D m(Pos2D{0,0},Pos2D{1,1},1000.0f);
    Cuboid2D cuboid1(Pos2D{0.6,0.2},Pos2D{0.8,0.5},(1*MU0),(2*EPS0));
    Cuboid2D cuboid2(Pos2D{0.1,0.6},Pos2D{0.4,0.8},(1*MU0),(5*EPS0));
    m.build_mesh_from_regions(std::vector<Region2D*>{(Cuboid2D*)&cuboid1,(Cuboid2D*)&cuboid2},std::make_pair(16,16));
    auto j_field = [](const Pos2D& p){
        if(p[0] >= 0.6 && p[0] <= 0.7 && p[1] >= 0.6 && p[1] <= 0.7){
            return Vec2cd{0,1};
        }
        return Vec2cd{0,0};
    };
    auto stifness_mat = m.calc_stiffness_mat();
    auto rhs = m.calc_rhs(j_field);
    Eigen::SparseLU<Eigen::SparseMatrix<Complex>> solver;
    solver.compute(stifness_mat);
    Eigen::VectorXcd x = solver.solve(rhs);
    m.print_field(x);
}