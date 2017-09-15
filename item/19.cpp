#include <memory>
#include <iostream>


// std::shared_ptr
// 가리키는 객체의 수명을 신경 쓸 필요가 없으며, 소멸자처럼 객체의 파괴가 결정론적이다.
// 객체의 참조 횟수 포인터를 가져서 일반 포인터 크기의 2배이다. 참조 횟수 포인터는 원자적연산을 한다.

// unique_ptr과 달리 삭제자가 포인터 형식의 일부가 아니다.
class Widget{};

auto deleter = [](Widget* pw)
{
    // do someting
    delete pw;
};

std::unique_ptr<Widget, decltype(deleter)>
upw(new Widget, deleter);

std::shared_ptr<Widget>
spw(new Widget, deleter);

// 또한 shared_ptr은 unique_ptr과 달리 사용자 삭제자 등록으로 크기가 증가하지 않는다.
// 이는 삭제자 또한 힙에 할당되어 객체와 마찬가지로 하나만 생성되며,
// 참조횟수 포인터(사실상 제어블록)가 관리한다.
// 제어블록이 가리키는 힙 메모리는 참조횟수, 약한참조, 사용자 삭제자 순으로 저장한다.

/*
 다음과 같은 생포인터 생성은 피해야한다.
 auto pw = new Widget;
 std::shared_ptr<Widget> spw1(pw, deleter);
 std::shared_ptr<Widget> spw2(pw, deleter);
 위와 같이 생포인터로 여러 spw를 만들 수 있으며 참조 횟수도 여러개 생겨서
 삭제 호출이 여러번 발생한다.(미정의 동작)

 이와 같이 파라미터에서 생성 선호 또는 21장 make_shared 참고
 std::shared_ptr<Widget> spw(new Widget, deleter);
*/

int main() {


}
