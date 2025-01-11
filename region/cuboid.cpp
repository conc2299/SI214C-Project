#include "cuboid.h"

Cuboid2D::Cuboid2D(Pos2D corner1, Pos2D corner2, Complex permeability, Complex permitivity)
: corner1(corner1), corner2(corner2)
{
    this->permeability = permeability;
    this->permitivity = permitivity;
}

Cuboid2D::Cuboid2D(Pos2D corner, double length, double width, Complex permeability, Complex permitivity)
{
    this->permeability = permeability;
    this->permitivity = permitivity;
    this->corner1 = corner;
    corner2[0] = corner1[0] + length;
    corner2[1] = corner1[1] + width;
}

bool Cuboid2D::is_interior(const Pos2D& p) const
{
    return ((p[0]-corner1[0]) * (p[0] - corner2[0]) < 0) 
        && ((p[1]-corner1[1]) * (p[1] - corner2[1]) < 0);
}

// bool Cuboid2D::on_edge(const Pos2D& p) const
// {
//     const double eps = 1e-9;
//     if( abs(p[0] - corner1[0]) < eps || abs(p[0] - corner2[0]) < eps){
//         return ((p[1]-corner1[1]) * (p[1] - corner2[1]) < 0);
//     }
//     if( abs(p[1] - corner1[1]) < eps || abs(p[1] - corner2[1]) < eps){
//         return ((p[0]-corner1[0]) * (p[0] - corner2[0]) < 0);
//     }
// }

double crossProduct(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

std::optional<Pos2D> line_intersection(const Pos2D& p1, const Pos2D& p2, const Pos2D& q1, const Pos2D& q2)
{
    const double eps = 1e-6;
    double dx1 = p2[0] - p1[0];
    double dy1 = p2[1] - p1[1];
    double dx2 = q2[0] - q1[0];
    double dy2 = q2[1] - q1[1];
    double denominator = crossProduct(dx1, dy1, dx2, dy2);
    if (abs(denominator) < eps) {
        return std::nullopt;
    }
    double dx = q1[0] - p1[0];
    double dy = q1[1] - p1[1];
    double t1 = crossProduct(dx, dy, dx2, dy2) / denominator;
    double t2 = crossProduct(dx, dy, dx1, dy1) / denominator;
    if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1) {
        Pos2D intersection = {p1[0] + t1 * dx1, p1[1] + t1 * dy1};
        return intersection;
    }
    return std::nullopt;
}

std::optional<Pos2D> Cuboid2D::get_intersection(const Pos2D& p1,const Pos2D& p2) const
{
    const double eps = 1e-9;
    Pos2D corner3 = Pos2D{corner1[0],corner2[1]};
    Pos2D corner4 = Pos2D{corner2[0],corner1[1]};
    auto intersect1 = line_intersection(p1,p2,corner1,corner3);
    if(intersect1.has_value()){
        return intersect1;
    }
    auto intersect2 = line_intersection(p1,p2,corner3,corner2);
    if(intersect2.has_value()){
        return intersect2;
    }
    auto intersect3 = line_intersection(p1,p2,corner2,corner4);
    if(intersect3.has_value()){
        return intersect3;
    }
    auto intersect4 = line_intersection(p1,p2,corner4,corner1);
    if(intersect4.has_value()){
        return intersect4;
    }
    return std::nullopt;
}

std::vector<Pos2D> Cuboid2D::get_vertices() const
{
    Pos2D corner3 = Pos2D{corner1[0],corner2[1]};
    Pos2D corner4 = Pos2D{corner2[0],corner1[1]};
    return std::vector<Pos2D>{corner1,corner4,corner2,corner3};
}

EParams Cuboid2D::get_eparams() const
{
    return EParams{permitivity,permeability};
}

// add w set and read
void Cuboid2D::set_frequency(double omega) {
    this->omega = omega;  
}

double Cuboid2D::get_frequency() const {
    return this->omega;   
}
