#include <iostream>
#include <string>


// 특수 멤버 함수 정리 (컴파일러가 자동으로 생성하는 멤버 함수들)

class Data {
public:
    // 사용자 선언 생성자가 없는 경우 자동 생성
    Data() {}

    // 기본 적으로 noexcept, 부모가 virtual 일 때 virtual
    ~Data() {}

    // 복사 배정 연산자 선언과 상관없이 생성됨. 단 이동연산을 하나라도 선언하면 삭제
    // 이동 생성자가 선언 안됐을 때는 복사 생성자 호출
    Data(const Data& data) {
        std::cout << "Data copy constructor" << std::endl;
    }

    // 복사 생성자와 상관없이 생성됨. 단 이동연산을 하나라도 선언하면 삭제
    // 이동 배정 연산자가 선언 안됐을 때는 복사 배정 연산자 호출
    Data& operator=(const Data& data) {
        std::cout << "Data copy assignment" << std::endl;
        return *this;
    }

    // 사용자 선언 복사 연산들과 소멸자가 없을 때 이동연산들 생성(c++11 부터)
    Data(Data&& data) noexcept {
        std::cout << "Data move constructor" << std::endl;
    }

    Data& operator=(Data&& data) noexcept {
        std::cout << "Data move assignment" << std::endl;
        return *this;
    }
};

class Widget {
public:
    Widget() = default;

    // 다음과 같이 아래 두 형식의 템플릿 복사 연산들을 선언 하더라도
    // 기본 복사 연산 생성에 영향을 주지 않는다. (main 예시와 26장 참조)
    template<typename T>
    Widget(const T& rhs);

    template<typename T>
    Widget& operator=(const T& rhs);

private:
    Data data;
};

int main() {
    Widget w1;
    Widget w2(w1);
    Widget w3 = w1;

    // template 으로 선언된 복사 연산들은 기본 이동생성자 선언에도 영향을 주지 않는다.
    Widget w4(std::move(w2));
    Widget w5 = std::move(w3);
}
