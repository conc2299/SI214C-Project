#ifndef POS_HPP
#define POS_HPP

#include <array>

/*
    Dim vector with Tp elements
*/
template <typename Tp, std::size_t Dim>
class Pos
{
public:
    constexpr Pos() = default;

    template <typename... Args>
    constexpr Pos(Args... args){
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

    constexpr Pos<Tp,Dim> operator+(const Pos<Tp,Dim>& other) const{
        Pos<Tp,Dim> result;
        for(std::size_t i = 0; i < Dim; i++){
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    constexpr Pos<Tp,Dim> operator-(const Pos<Tp,Dim>& other) const{
        Pos<Tp,Dim> result;
        for(std::size_t i = 0; i < Dim; i++){
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    constexpr Pos<Tp,Dim> operator*(const Pos<Tp,Dim>& other) const{
        Pos<Tp,Dim> result;
        for(std::size_t i = 0; i < Dim; i++){
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    constexpr Pos<Tp,Dim> operator*(const Tp& other) const {
        Pos<Tp,Dim> result;
        for(std::size_t i = 0; i < Dim; i++){
            result.data[i] = data[i] * other;
        }
        return result;
    }

    constexpr Pos<Tp,Dim> operator/(const Pos<Tp,Dim>& other) const {
        Pos<Tp,Dim> result;
        for(std::size_t i = 0; i < Dim; i++){
            result.data[i] = data[i] / other.data[i];
        }
        return result;
    }

    constexpr Pos<Tp,Dim> operator/(const Tp& other) const {
        Pos<Tp,Dim> result;
        for(std::size_t i = 0; i < Dim; i++){
            result.data[i] = data[i] / other;
        }
        return result;
    }

    constexpr Pos& operator+=(const Pos<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] += other.data[i];
        }
        return *this;
    }

    constexpr Pos& operator-=(const Pos<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] -= other.data[i];
        }
        return *this;
    }

    constexpr Pos& operator*=(const Pos<Tp,Dim>& other){
        for(std::size_t i = 0; i < Dim; i++){
            data[i] *= other.data[i];
        }
        return *this;
    }

    constexpr Pos& operator/=(const Pos<Tp,Dim>& other){
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

#endif 