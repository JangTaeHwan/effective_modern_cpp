#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

template<typename T>
class TD;

template<typename T>
void f(const T& param) {
    std::cout << "T 	= 	" << typeid(T).name() << std::endl;
    std::cout << "param   = 	" << typeid(param).name() << std::endl;	// const와 참조를 무시한 T와 동일한 결과 출력
}

int main() {
    // unorderd_map의 key는 const 형식으로 연역된다.
    std::unordered_map<std::string, int> m;

    m.insert({"abc", 1});

//    따라서 아래와 같이 const 없이 왼값 참조로 p를 선언하면 컴파일 에러 발생.
//    for (std::pair<std::string, int>& p : m)


//  아래와 같이 const를 선언하면 컴파일과 동작은 되지만 실행시 주소값이 다르다.
//  따라서 내부적으로 m의 객체를 얻어와 임시 객체에 복사하고 해당 객체의 주소를 p에 전달한다.
    for (const std::pair<std::string, int>& p : m) {
        // 4장에서 배운 컴파일 에러로 타입 확인 가능
        // TD<decltype(p)> pType;
        // TD<decltype(*(m.cbegin()))> mType;

        std::cout << &p << std::endl;
        std::cout << &(*(m.cbegin())) << std::endl;
    }

//  위 문제를 해결하려면 아래 두 가지 방법이 있으며 auto로 선언하는게 깔끔하다.
    for (const std::pair<const std::string, int>& p : m) {
        std::cout << &p << std::endl;
        std::cout << &(*(m.cbegin())) << std::endl;
    }

    for (const auto& p : m) {
        std::cout << &p << std::endl;
        std::cout << &(*(m.cbegin())) << std::endl;
    }
}
