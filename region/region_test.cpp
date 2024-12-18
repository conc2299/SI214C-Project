#include "cuboid.h"

#include <iostream>

using namespace std;

int main()
{
    Cuboid c(POS3D{1.0f,1.0f,1.0f},POS3D{2.0f,2.0f,2.0f},1,1);
    cout << c.is_interior(POS3D{1.5f,1.5f,1.5f}) << endl;
    cout << c.is_interior(POS3D{0.5f,0.5f,0.5f}) << endl;
    return 0;
}