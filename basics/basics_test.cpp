#include "basics/vec.hpp"

#include <complex>
#include <iostream>

int main()
{
    constexpr Vec<std::complex<double>,2> 
        v1(std::complex<double>{1.0,2.0},
            std::complex<double>{2.0,1.0});
    constexpr Vec<std::complex<double>,2> 
        v2(std::complex<double>{1.0,3.0},
            std::complex<double>{2.0,1.0});
    constexpr auto v3 = inner_product(v1,v2);
    constexpr auto v4 = inner_product(v2,v1);

    std::cout << v1[0] << v1[1] << std::endl;
    std::cout << v2[0] << v2[1] << std::endl;
    std::cout << v3 << std::endl;
    std::cout << v4 << std::endl;
}
