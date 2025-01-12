#include "nedelecp1.h"
#include "basics/global.h"

int main()
{
    NedelecP1_2D e(Pos2D{0,0},Pos2D{1,0},Pos2D{0,1},std::array<std::size_t,3>{1,2,3});
    auto j_field = [](const Pos2D& p){
        if(p[0] >= 0 && p[0] <= 1 && p[1] >= 0 && p[1] <= 1){
            return Vec2cd{0,1};
        }
        return Vec2cd{0,0};
    };
    auto result = e.int_dot(j_field);
}