#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
class TD;

template<typename T>
void f(const T& param) {
    std::cout << "T 	= 	" << typeid(T).name() << std::endl;
    std::cout << "param   = 	" << typeid(param).name() << std::endl;	// const와 참조를 무시한 T와 동일한 결과 출력
}

// 정확한 타입 출력을 위해선 boost/type_index.hpp 이용

int main() {
    //const char name[] = "test";
    std::string name = "test";
    const int val = 42;
    auto x = val;
    auto y = &val;
    auto z1 = name;
    auto& z2 = name;

// 컴파일 에러를 통해 auto의 연역 타입 확인
/*
    TD<decltype(x)> xType;
    TD<decltype(y)> yType;
    TD<decltype(z1)> z1Type;
    TD<decltype(z2)> z2Type;
*/

    f(x);
    f(y);
    f(z1);
    f(z2);

    std::cout<< typeid(x).name() << std::endl;
    std::cout<< typeid(y).name() << std::endl;
    std::cout<< typeid(z1).name() << std::endl;
    std::cout<< typeid(z2).name() << std::endl;

}
