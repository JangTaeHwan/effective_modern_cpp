#include <iostream>
#include <vector>
#include <array>

template<typename T>
class TD;

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
    return N;
}

template<typename T>
void f(T param) {
    std::cout << "normal param: " << param << std::endl;
}

template<typename T>
void f(std::initializer_list<T> listParam) {
    std::cout<< "list param: ";
    for (const auto& i : listParam) {
        std::cout<< i << " ";
    }
    std::cout << std::endl;
}

int main() {
    int keyVals[] = { 1, 2, 3, 4, 5, 6, 7 };
    std::array<int, arraySize(keyVals)> mappedVals;
    std::cout << mappedVals.size() << std::endl;

    const char name[] = "T. H.";
    std::cout << arraySize(name) << std::endl;

    auto& testPtr = name; 					// const char (&) [6]
    std::cout << arraySize(testPtr) << std::endl;

    auto x = { 1, 2, 3 };					// std::initializer_list<int>

    f(x);
    f({ 4, 5, 6 });
}
