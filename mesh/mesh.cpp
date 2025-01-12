#include "mesh/mesh.h"

#include <cmath>
#include <iostream>

#define EPS_MESH 1e-3
#define DISTANCE_TO_NEAREST_INT(x) abs((x)-std::round(x))

void print_triangle(const CDT::Triangle& t)
{
    for(auto a:t.vertices)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}

void print_vertice(const CDT::V2d<double>& v)
{
    std::cout << "(" << v.x << "," << v.y << ")" << std::endl;
}

void print_edge(const CDT::Edge& e)
{
    std::cout << "(" << e.v1() << "," << e.v2() << ")" << std::endl;
}

void print_dt_result(const std::vector<Pos2D>& vs)
{
    CDT::Triangulation<double> cdt;
    cdt.insertVertices(vs.begin(),
                        vs.end(),
                        [](const Pos2D& p){return p[0];},
                        [](const Pos2D& p){return p[1];});
    cdt.eraseSuperTriangle();
    auto vertices = cdt.vertices;
    auto triangles = cdt.triangles;
    auto edges = CDT::extractEdgesFromTriangles(triangles);
    
    for(auto v:vertices)
    {
        print_vertice(v);
    }
    for(auto t:triangles)
    {
        print_triangle(t);
    }
    std::cout << "edges:" << std::endl;
    for(auto e:edges)
    {
        print_edge(e);
    }
}

bool close_to_mesh_grid(Pos2D p, Pos2D mesh_ll, double x_interval, double y_interval)
{
    Pos2D v = p - mesh_ll;
    return (DISTANCE_TO_NEAREST_INT(v[0]/x_interval) <= EPS_MESH
    && DISTANCE_TO_NEAREST_INT(v[1]/y_interval) <= EPS_MESH);
}

std::vector<Pos2D> Mesh2D::gen_vertices(const std::vector<Region2D*>& regions,const std::pair<std::size_t,std::size_t>& mesh_size) const
{
    std::size_t total_vertices_num = (mesh_size.first + 1) * (mesh_size.second + 1);
    //first pass, add uniform grid
    std::vector<Pos2D> grid_vertices;
    grid_vertices.reserve(total_vertices_num);
    double x_interval = (ur[0] - ll[0]) / mesh_size.first;
    double y_interval = (ur[1] - ll[1]) / mesh_size.second;
    // std::cout << x_interval << " " << y_interval << std::endl;
    for(std::size_t i = 0; i < mesh_size.first + 1; i++)
    {
        for(std::size_t j = 0; j < mesh_size.second + 1; j++)
        {
            grid_vertices.emplace_back(Pos2D{ll[0] + i*x_interval, ll[1] + j*y_interval});
        }
    }
    // second pass, add region boundary and vertices,
    std::vector<Pos2D> extra_vertices; 
    auto up_grid_idx = [&](std::size_t idx){return idx + mesh_size.first + 1;}; 
    auto down_grid_idx = [&](std::size_t idx){return idx - mesh_size.first - 1;}; 
    auto left_grid_idx = [&](std::size_t idx){return idx - 1;}; 
    auto right_grid_idx = [&](std::size_t idx){return idx + 1;}; 
    for(auto r:regions)
    {
        // vertices
        auto region_vertices = r->get_vertices();
        for(Pos2D v:region_vertices)
        {
            if(!close_to_mesh_grid(v,ll,x_interval,y_interval))
            {
                extra_vertices.emplace_back(v);
            }
        }
        //boundaries
        for(std::size_t i = 1; i < mesh_size.first; i++)
        {
            for(std::size_t j = 1; j < mesh_size.second; j++)
            {
                std::size_t idx = i * (mesh_size.second + 1) + j;
                if(r->is_interior(grid_vertices[idx])){
                    // check 4 directions
                    std::size_t up_idx = up_grid_idx(idx);
                    std::optional<Pos2D> up_intersect = r->get_intersection(grid_vertices[idx],grid_vertices[up_idx]);
                    if(up_intersect.has_value() && !close_to_mesh_grid(up_intersect.value(),ll,x_interval,y_interval)){
                        extra_vertices.push_back(up_intersect.value());
                    }
                    std::size_t down_idx = down_grid_idx(idx);
                    std::optional<Pos2D> down_intersect = r->get_intersection(grid_vertices[idx],grid_vertices[down_idx]);
                    if(down_intersect.has_value() && !close_to_mesh_grid(down_intersect.value(),ll,x_interval,y_interval)){
                        extra_vertices.push_back(down_intersect.value());
                    }
                    std::size_t left_idx = left_grid_idx(idx);
                    std::optional<Pos2D> left_intersect = r->get_intersection(grid_vertices[idx],grid_vertices[left_idx]);
                    if(left_intersect.has_value() && !close_to_mesh_grid(left_intersect.value(),ll,x_interval,y_interval)){
                        extra_vertices.push_back(left_intersect.value());
                    }
                    std::size_t right_idx = right_grid_idx(idx);
                    std::optional<Pos2D> right_intersect = r->get_intersection(grid_vertices[idx],grid_vertices[right_idx]);
                    if(right_intersect.has_value() && !close_to_mesh_grid(right_intersect.value(),ll,x_interval,y_interval)){
                        extra_vertices.push_back(right_intersect.value());
                    }
                }
            }
        }
    }
    grid_vertices.insert(grid_vertices.end(),extra_vertices.cbegin(),extra_vertices.cend());
    return grid_vertices;
}

void Mesh2D::build_mesh_from_regions(const std::vector<Region2D*>& regions, const std::pair<std::size_t,std::size_t>& mesh_size)
{
    std::vector<Pos2D>&& grid_vertices = gen_vertices(regions,mesh_size);
    // print_dt_result(grid_vertices);

    // build triangular mesh
    CDT::Triangulation<double> cdt;
    cdt.insertVertices(grid_vertices.begin(),
                        grid_vertices.end(),
                        [](const Pos2D& p){return p[0];},
                        [](const Pos2D& p){return p[1];});
    cdt.eraseSuperTriangle();
    auto vertices = cdt.vertices;
    auto triangles = cdt.triangles;
    auto edges = CDT::extractEdgesFromTriangles(triangles);
    
    mesh_vertices.resize(vertices.size());
    std::transform(vertices.cbegin(),vertices.cend(),mesh_vertices.begin(),
        [](const CDT::V2d<double>& p){
            return Pos2D{p.x,p.y};
        } 
    );
    /*
        TODO: optimize the dof order
        this will influence the sparsity of the stifness matrix
    */
    std::size_t idx = 0;
    for(auto e : edges){
        edge_to_dof_idx[e] = idx;
        idx ++ ;
    }

    for(auto t : triangles){
        auto vertidxs = t.vertices;
        std::sort(vertidxs.begin(),vertidxs.end());
        Pos2D p1 = Pos2D{vertices[vertidxs[0]].x,vertices[vertidxs[0]].y};
        Pos2D p2 = Pos2D{vertices[vertidxs[1]].x,vertices[vertidxs[1]].y};
        Pos2D p3 = Pos2D{vertices[vertidxs[2]].x,vertices[vertidxs[2]].y};
        NedelecP1_2D element = NedelecP1_2D(p1,p2,p3,{
                                            edge_to_dof_idx[CDT::Edge(CDT::VertInd(vertidxs[0]),CDT::VertInd(vertidxs[1]))],
                                            edge_to_dof_idx[CDT::Edge(CDT::VertInd(vertidxs[1]),CDT::VertInd(vertidxs[2]))],
                                            edge_to_dof_idx[CDT::Edge(CDT::VertInd(vertidxs[2]),CDT::VertInd(vertidxs[0]))],
                                            });
        elements.emplace_back(std::move(element));
        // add eparams
        Pos2D t_center = (p1 + p2 + p3) / 3;
        EParams ep;
        for(auto r:regions){
            if(r->is_interior(t_center)){
                ep = r->get_eparams();
                break;
            }
        }
        eparam.emplace_back(ep);
    }
    global_dof_num = edges.size();
}

// void Mesh2D::calc_stiffness_mat()
// {
//     for(auto e:elements)
//     {
//         e.int_dot_self();
//         e.print_element_info();
//     }
// }

Eigen::SparseMatrix<std::complex<double>> Mesh2D::calc_stiffness_mat() {
    // initial
    Eigen::SparseMatrix<std::complex<double>> global_matrix(global_dof_num, global_dof_num);

    for (std::size_t i = 0; i < elements.size(); i ++) {
        const auto& element = elements[i];

        std::array<std::size_t, 3> dof_mapping = element.get_mapping();

        Mat3cd local_A = element.int_dot_self();       //  A
        Mat3cd local_B = element.int_curl_dot_self();  //  B

        EParams params = eparam[i];

        Complex mu = params.mu;  // 获取 μ
        Complex epsilon = params.epsilon;  // 获取 ε

        Mat3cd weighted_A = (1.0 / mu) * local_A;       // ~A
        Mat3cd weighted_B = (-omega * omega * epsilon) * local_B;  // ~B
        Mat3cd local_K = weighted_A + weighted_B;  // (~A) + (~B)

        // map
        for (std::size_t i = 0; i < 3; ++i) {
            for (std::size_t j = 0; j < 3; ++j) {
                global_matrix.coeffRef(dof_mapping[i], dof_mapping[j]) += local_K(i, j);
            }
        }
    }
    return global_matrix;
}

Eigen::VectorXcd Mesh2D::calc_rhs(std::function<Vec2cd(const Pos2D&)> f) {
    Eigen::VectorXcd rhs(global_dof_num);
    rhs.setZero();  

    for (const auto& element : elements) {
        
        std::array<std::size_t, 3> dof_mapping = element.get_mapping();

        Arr3cd local_rhs = element.int_dot(f);

        for (std::size_t i = 0; i < 3; ++i) {
            rhs[dof_mapping[i]] += local_rhs[i]*(omega * Complex{0,-1});
        }
    }
    return rhs;
}

void Mesh2D::print_field(const Eigen::VectorXcd& f){
    std::cout << "(" << ll.transpose() << "),(" << ur.transpose() << ")" << std::endl;
    std::cout << edge_to_dof_idx.size() << std::endl;
    for(auto e: edge_to_dof_idx){
        CDT::Edge e_idx = e.first;
        std::size_t f_idx = e.second;
        std::cout << "(" << mesh_vertices[e_idx.v1()].transpose() << "),(" << mesh_vertices[e_idx.v2()].transpose() << "):" << f(f_idx) << std::endl;
    }
}


void Mesh2D::clear()
{
    global_dof_num = 0;
    edge_to_dof_idx.clear();
    elements.clear();
    eparam.clear();
}