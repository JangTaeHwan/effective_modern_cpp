#include <iostream>
#include <utility>
#include <vector>
#include <type_traits>

class Data {
public:
    Data() : value(0) {}

    Data(int i) {
        value = i;
    }

    Data(const Data& data) {
        value = data.value;
        std::cout << "Data copy constructor" << std::endl;
    }

    Data(Data&& data) noexcept {
        value = std::move(data.value);
        std::cout << "Data move constructor" << std::endl;
    }

    Data& operator=(const Data& data) {
        value = data.value;
        std::cout << "Data copy assignment" << std::endl;
        return *this;
    }

    Data& operator=(Data&& data) noexcept {
        value = std::move(data.value);
        std::cout << "Data move assignment" << std::endl;
//      noexcept 내부에서 예외 호출시 std::terminate()가 내부적으로 호출되어 프로그램 종료
//      throw 1;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream&, const Data&);

private:
    int value;
};

std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << data.value;
    return os;
}

template<typename T>
void user_swap(T& a, T& b)
noexcept(std::is_nothrow_move_constructible<T>::value
    && std::is_nothrow_move_assignable<T>::value)
{
    std::cout << std::endl;
    std::cout << "user swap called" << std::endl;

/*
     이와 같이 이동생성자의 noexcept를 체크하여 move 연산 할 수 도 있지만
    std::swap은 noexcept 여부를 떠나서 이동 생성, 대입연산자를 복사보다 우선 호출한다.
     추측하건데 그 이유로는 swap 과정은 이동 혹은 복사 연산을 떠나서 본래 a, b가 가진 값이
    중간에 소실 되므로 기존 값으로 되돌리기 어렵다.
     그리고 vector나 다른 자료형 처럼 기존 값들을 저장하고 가지고 있을 이유가 없으므로,
    swap과정은 모두 이동연산을 우선 호출 하는 듯 하다. (vector 자체를 swap하는 경우는 추후 확인 필요)

    auto temp = std::move_if_noexcept(b);
    b = std::move_if_noexcept(a);
    a = std::move_if_noexcept(temp);
*/
    std::swap(a, b);
}

void doSwap(std::vector<Data>& v) {
    try {
        user_swap(v[0], v[1]);
        user_swap(v[1], v[2]);
        user_swap(v[2], v[3]);
// 위에 Data class에서 noexcept에서 throw int가 발생했다면 여기서 catch 할 수 없다.
    } catch(int e) {
    }
}

int main() {
    std::vector<Data> v;


//  v에 push_back 했을 때 size초과 시 내부적으로 resize가 일어나는데
// 이 때 Data의 이동 생성자에 noexcept가 설정돼있지 않다면 내부적으로 복사 생성이 발생한다.
//  vector는 강한 예외 안정성을 보장하기 때문에 resize실패 시 기존 데이터를 유지하기 위해
// 복사 연산하는 것이고 성능 최적화를 하기 위해서는 이동 생성자에 noexcept 키워드를 추가하여
// resize 시 Data의 이동 생성에 예외가 없음을 표시하여 최적화한다.
    v.push_back(Data{1});

    std::cout << std::endl;
    Data a{2};
    v.push_back(std::move(a));

    std::cout << std::endl;
    Data b{3};
    v.push_back(std::move(b));

    std::cout << std::endl;
    Data c{4};
    v.push_back(std::move(c));

//  실제 std::swap을 보면 아래와 같이 T의 nothrow를 체크하여 std::swap의 noexcept를 결정한다.
//  하지만 swap의 경우 stl에서 vector, deque등과 같이 강한 예외 안정성을 보장하여
// noexcept가 아닐 시 copy연산이 일어나지는 않는다.
    std::cout << std::is_nothrow_move_constructible<Data>::value << std::endl
              << std::is_nothrow_move_assignable<Data>::value << std::endl;

//    c++17 feature, g++ 컴파일 안됨, 추후 확인
//    std::cout << std::is_nothrow_swappable_v<Data> << std::endl;

// 아래와 같이 실제 호출 식에 noexcept 호출하여 확인가능
    std::cout << noexcept(user_swap(v[0], v[1])) << std::endl;
// 하지만 이런 식으로 단순한 bool constexpr로는 확인 불가능
    std::cout << noexcept(false) << std::endl;    // 무조건 true 출력

    doSwap(v);

    std::cout<<"program end"<<std::endl;
}
