#include <memory>
#include <unordered_map>
#include <iostream>


// std::weak_ptr
// std::shared_ptr과 같은 기능을 하지만, 소유권 공유에 참여하지 않는다.
// std::shared_ptr와 크기는 동일하며 약한 참조 횟수를 관리한다.

class Widget{};

std::shared_ptr<const Widget> loadWidget(int) {
    std::shared_ptr<const Widget> spw;
    return spw;
} 


// weak_ptr 예시
std::shared_ptr<const Widget> fastLoadWidget(int id) {
    static std::unordered_map<int, std::weak_ptr<const Widget>> cache;

    auto objPtr = cache[id].lock();

    if (not objPtr) {
        objPtr = loadWidget(id);
        cache[id] = objPtr;
    }

    return objPtr;
}

// 이외에도 서로 다른 객체가 서로를 소유할 때도 쓰인다.
// (std::shared_ptr로 서로를 가리키면 Swift에서 강한결합과 같은 현상이 나타나고,
//  생포인터나 std::unique_ptr로 가리키면 nullptr을 호출하거나 객체의 상태를 확인하지 못하는 문제가 있다.)

int main() {


}
