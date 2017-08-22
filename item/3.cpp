#include <iostream>
#include <vector>
#include <array>

template<typename T>
class TD;

template<typename Container, typename Index>
decltype(auto)
authAndAccess(Container&& c, Index i) { 			// 왼값 참조보다는 보편참조
    // authenticateUser();

    return std::forward<Container>(c)[i];
}

int main() {

    auto x = 27;
    const auto cs = x;
    const auto& rx = x;

/*
    // type 확인
    TD<decltype(x)> xType;
    TD<decltype(cs)> csType;
    TD<decltype(rx)> rxType;
*/

    // Container에 오른값 전달 예
    //auto value = authAndAccess(std::vector<int>(5, 3), 1);

    auto v = std::vector<int>(5, 3);

    /*
	 auto의형식 연역은 template과 같고 authAndAccess를 auto로 반환 했을 때
	참조성이 사라진 T 형식의 오른값을 반환하여 아래 식에서 에러
	 아래와 같이 온전한 T& 형식을 반환하려면 decltype(auto) 또는 auto&로 선언
	 그리고 보편참조로 c를 선언하여 오른값을 받도록 확장
    */
    authAndAccess(v, 1) = 5;

    // 보편참조로 선언 후 Container에 오른값 입력 시 아래와 같은 미정의 동작 유의
    authAndAccess(std::vector<int>(5, 3), 1) = 5;

    for (const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
