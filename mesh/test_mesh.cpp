#include <iostream>
#include "mesh.h"
#include "region/cuboid.h"

int main()
{
    Mesh2D m{Pos2D{0,0},Pos2D{1,1}};
    Cuboid2D cuboid1(Pos2D{0.6,0.2},Pos2D{0.8,0.5},1,Complex{1,-50});
    Cuboid2D cuboid2(Pos2D{0.1,0.6},Pos2D{0.4,0.8},1,5);
    m.build_mesh_from_regions(std::vector<Region2D*>{(Cuboid2D*)&cuboid1,(Cuboid2D*)&cuboid2},std::make_pair(3,3));
    m.calc_stifness_mat();
    std::cout << " " << std::endl;
}