#include <string>
#include <iostream>

class Widget {
public:
    Widget(int i) {
        value = i;
        std::cout << "default init" << std::endl;
    }

    // 자세한 특수 멤버 함수들은 17장에서
    Widget(const Widget&) = default;		// 기본 복사 생성
    Widget& operator=(const Widget&) = delete;	// 복사 배정 삭제

    bool isLucky(int number);
    bool isLucky(char) = delete;			// char 삭제
    bool isLucky(bool) = delete;			// bool 삭제
    bool isLucky(double) = delete;			// double, float 삭제

    // 템플릿 포인터 삭제
    template<typename T>
    void processPointer(T* ptr){}

    int getValue() {
        return value;
    }

private:
    int value = 5;
};

// 템플릿 특수화 삭제
// 같은 클래스내 불가능, 같은 이름공간 내 선언
template<>
void Widget::processPointer<void>(void*) = delete;

template<>
void Widget::processPointer<char>(char*) = delete;

int main() {
    // explicit 지정 없을 시 Widget(const Widget&) 호출
    Widget w[3] = { 1, 2, 3 };

    Widget* ptr = &(w[0]);

    // *temp, temp->, temp++, temp-- / 역참조, 증가, 감소 불가능
    void* temp = w;

    std::cout << (*ptr).getValue() << std::endl;
    ptr++;
    std::cout << ptr->getValue() << std::endl;

    // error: ‘void*’ is not a pointer-to-object type
    //std::cout << (*temp).getValue() << std::endl;
    //std::cout << temp->getValue() << std::endl;

    // ISO C++ forbids incrementing a pointer of type ‘void*’
    //temp++;
    // ISO C++ forbids decrementing a pointer of type ‘void*’
    //temp--;

    return 0;
}
