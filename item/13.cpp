#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <set>

// c++11 에서 멤버함수 cbegin, cend은 제공하지만 비멤버는 빠져있다.
// c++14 에서 구현되있지만 c++11을 사용할 경우 아래 템플릿 선언.
namespace user {

template<class C>
auto cbegin(const C& container) -> decltype(std::begin(container)) {
    return std::begin(container);
}

template<class C>
auto cend(const C& container) -> decltype(std::end(container)) {
    return std::end(container);
}

// 다음과 같이 정의할 수 도 있지만, 이렇게 선언할 경우
// container에 멤버함수로 begin()이나 end()가 없는 배열은 사용할 수 없다.
/*
template<class C>
auto cend(const C& container) -> decltype(container.end()) {
    return container.end();
}
*/
}

template<typename C, typename V>
void findAndInsert(C& container,
                   const V& targetVal,
                   const V& insertVal)
{
    auto it = std::find(user::cbegin(container),
                        user::cend(container),
                        targetVal);
    container.insert(it, insertVal);
}

// 템플릿 배열 특수화
template<typename C, std::size_t N,  typename V>
void findAndInsert(C (&container)[N],
                   const V& targetVal,
                   const V& insertVal)
{
    auto it = std::find(std::cbegin(container),
                        std::cend(container),
                        targetVal);

    // insert 구현
}

int main() {
    //std::vector<int> v{ 1, 2, 3, 4, 5 };
    int v[] = { 1, 2, 3, 4, 5 };

    findAndInsert(v, 1, 2);

    for(const auto& value : v) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

}
