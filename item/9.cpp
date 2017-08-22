#include <string>
#include <memory>
#include <list>
#include <type_traits>	// 형변환 템플릿들
#include <iostream>


// typedef 보다 using을 별칭 선언으로 선호하는 이유는
// 아래와 같이 템플릿화를 할 수 있는지 여부에 있다.
template<typename T>
using MyAllocList1 = std::list<T, std::allocator<T>>;	// MyAllocList1<Widget> lw;

template<typename T>
struct MyAllocList2 {
    typedef std::list<T, std::allocator<T>> type;	// MyAllocList2<Widget>::type lw;
};


template<typename T>
class Widget {
private:
    /*
       또한 typedef를 템플릿화 하기 위해 우회 방법으로 위와 같이 struct로 감쌌을 때
      아래와 같이 T = Widget2 일 때 자료형 type을 가지는 MyAllocList2를 만들 수 도 있기 때문에
      의존적 형식 안에서 typedef 앞에는 typename을 붙여야 한다.

      template<>
      struct MyAllocList2<Widget2> {
         std::string type;
      };
    */
    typename MyAllocList2<T>::type list2;

    // 반면, MyAllocList1 경우 컴파일러가 형식이름임을 알고 있으므로 typename을 붙일 필요도 붙여서도 안된다.
    MyAllocList1<T> list1;

    // 아래 형변환 템플릿 들 중 typedef로 구현되어 있는 것들은 c++11 표준, ::type 선언을 표준으로 함.
    // (using 보다 못하지만 역사적인 이유로 typedef로 구현)
    // 뒤늦게 c++14에서 using으로 구현한 xxx_xxx_t 반영
    // c++11 에서도 using remove_const_t = typename std::remove_const<T>::type; 이렇게 사용 가능

    typename std::remove_const<T>::type t1;
    std::remove_const_t<T> t2;

    typename std::remove_reference<T>::type t3;
    std::remove_reference_t<T> t4;

    typename std::add_lvalue_reference<T>::type t5;
    std::add_lvalue_reference<T> t6;

};

int main() {


    return 0;
}
