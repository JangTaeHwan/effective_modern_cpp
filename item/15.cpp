#include <array>
#include <iostream>


//  컴파일 시점에 계산 할 수 있을 때만 const return
//  c++11 에서는 return statement로 작성해야 한다. (변수 선언이나 연산 시 에러)
constexpr
int pow(int base, int exp) noexcept {
    auto result = 1;
    
    for (int i = 0; i < exp; i++) result *= base;

    return result;
}

class Point {
public:
    constexpr Point() : x(0.0), y(0.0) {}

    // c++11 에서 void를 제외한 모든 내장 형식은 literal
    // constexpr로 선언된 사용자 정의 형식도 literal
    constexpr Point(double xVal, double yVal) noexcept
    : x(xVal), y(yVal) {}

    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }


    // c++11 에서는 constexpr 안에서 멤버함수는는 암묵적으로 const 이고
    // void는 literal로 선언 될 수 없다.
    constexpr void setX(double newX) noexcept { x = newX; }   // c++14
    constexpr void setY(double newY) noexcept { y = newY; }   // c++14

private:
    double x, y;
};


// constexpr 함수들로 또 다른 constexpr 함수 생성 가능
constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept {
    return { (p1.xValue() + p2.xValue()) / 2,
             (p1.yValue() + p2.yValue()) / 2 };
}

constexpr
Point reflection(const Point& p) noexcept {
    Point result;

    result.setX(-p.xValue());
    result.setY(-p.yValue());

    return result;
}

int main() {

    const int a = 10;
    constexpr int arraySize = a;

    std::array<int, arraySize> data;

    int n = 3;
    pow(3, n);

    std::array<int, pow(10, 2)> result;

    constexpr Point p1(9.4, 1.2);
    constexpr Point p2(9.7, 9.2);

    constexpr auto mid = midpoint(p1, p2);

    constexpr auto reflectedMid = reflection(mid);
}
