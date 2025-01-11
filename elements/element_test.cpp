#include "nedelecp1.h"
#include "basics/global.h"

int main()
{
    NedelecP1_2D e(Pos2D{0,0},Pos2D{1.0f/2,0},Pos2D{0,1},std::array<std::size_t,3>{1,2,3});
    auto result = e.int_dot_self();
}