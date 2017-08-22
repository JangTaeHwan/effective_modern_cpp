#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>

template<typename T>
class TD;

template<typename T>
void print(const T& val){
    std::cout << val << std::endl;
}

using Type = bool;
std::vector<Type> possible() {
    std::vector<Type> v = { 1, 0, 0, 1, 0 };

    return v;
}

int main() {
    auto a = possible()[3];

    // Type = int 일 때 'TD<int> aType'
    // Type = bool 일 때 'TD<std::_Bit_reference> aType'
    TD<decltype(a)> aType;

    std::cout << a << std::endl;
    print(a);
}
