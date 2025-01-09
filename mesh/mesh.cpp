#include "mesh/mesh.h"
#include "CDT/include/CDT.h"
#include <iostream>

void Mesh2D::build_mesh_from_regions(const std::vector<Region2D*>& regions, std::pair<double,double> mesh_size)
{
    CDT::Triangulation<double> cdt;
}

void print_triangle(const CDT::Triangle& t)
{
    for(auto a:t.vertices)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

void print_vertices(const CDT::V2d<double> v)
{
    std::cout << "(" << v.x << "," << v.y << ")" << std::endl;
}

void Mesh2D::test()
{
    CDT::Triangulation<double> cdt;
    std::array<Pos2D,12> a{Pos2D{0,0}
                        ,Pos2D{0,1}
                        ,Pos2D{0,2}
                        ,Pos2D{1,0}
                        ,Pos2D{1,1}
                        ,Pos2D{1,2}
                        ,Pos2D{2,0}
                        ,Pos2D{2,1}
                        ,Pos2D{2,2}
                        ,Pos2D{1.5,0.5}
                        ,Pos2D{1.5,1}
                        ,Pos2D{1.5,1.5}};
    cdt.insertVertices(a.begin(),
                        a.end(),
                        [](const Pos2D& p){return p[0];},
                        [](const Pos2D& p){return p[1];});
    cdt.eraseSuperTriangle();
    auto vertices = cdt.vertices;
    auto triangles = cdt.triangles;
    for(auto v:vertices)
    {
        print_vertices(v);
    }
    for(auto t:triangles)
    {
        print_triangle(t);
    }
}