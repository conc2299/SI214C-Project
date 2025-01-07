#ifndef VEC_H
#define VEC_H

#include <array>
#include <stdexcept>
#include <complex>

/*
    Dim vector with Tp elements
*/
template <typename Tp, std::size_t Dim>
class Vec
{
public:
    constexpr Vec() = default;

    template <typename... Args>
    constexpr Vec(Args... args){
        static_assert(sizeof...(args) == Dim, "Number of arguments must match the dimension");
        _initialize<0>(args...);
    }

    constexpr const Tp& operator[](std::size_t index) const{
        if(index >= Dim){
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    constexpr Tp& operator[](std::size_t index){
        if(index >= Dim){
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    constexpr Vec<Tp,Dim> operator+(const Vec<Tp,Dim>& other) const{
        Vec<Tp,Dim> product;
        for(std::size_t i = 0; i < Dim; i++){
            product.data[i] = data[i] + other.data[i];
        }
        return product;
    }

    constexpr Vec<Tp,Dim> operator-(const Vec<Tp,Dim>& other) const{
        Vec<Tp,Dim> product;
        for(std::size_t i = 0; i < Dim; i++){
            product.data[i] = data[i] - other.data[i];
        }
        return product;
    }

    constexpr Vec<Tp,Dim> operator*(const Vec<Tp,Dim>& other) const{
        Vec<Tp,Dim> product;
        for(std::size_t i = 0; i < Dim; i++){
            product.data[i] = data[i] * other.data[i];
        }
        return product;
    }

    constexpr Vec<Tp,Dim> operator/(const Vec<Tp,Dim>& other) const {
        Vec<Tp,Dim> product;
        for(std::size_t i = 0; i < Dim; i++){
            product.data[i] = data[i] / other.data[i];
        }
        return product;
    }

    constexpr Vec& operator+=(const Vec<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] += other.data[i];
        }
        return *this;
    }

    constexpr Vec& operator-=(const Vec<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] -= other.data[i];
        }
        return *this;
    }

    constexpr Vec& operator*=(const Vec<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] *= other.data[i];
        }
        return *this;
    }

    constexpr Vec& operator/=(const Vec<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] /= other.data[i];
        }
        return *this;
    }

private:
    std::array<Tp,Dim> data;

    // used for recursive initializaion
    template <std::size_t Index, typename Last>
    constexpr void _initialize(Last last){
        data[Index] = last;
    }

    template <std::size_t Index, typename First, typename... Rest>
    constexpr void _initialize(First first, Rest... rest){
        data[Index] = first;
        _initialize<Index+1>(rest...);
    }
};

// real value vector
template <std::size_t Dim>
constexpr double inner_product(const Vec<double,Dim>& v1, const Vec<double,Dim>& v2){
    double res;
    for(std::size_t i = 0; i < Dim ; i++){
        res += v1[i] * v2[i];
    }
    return res;
}

// complex value vector inner product
template <std::size_t Dim>
constexpr std::complex<double> inner_product(const Vec<std::complex<double>,Dim>& v1, const Vec<std::complex<double>,Dim>& v2){
    std::complex<double> res;
    for(std::size_t i = 0; i < Dim ; i++){
        res += v1[i] * conj(v2[i]);
    }
    return res;
}

#endif