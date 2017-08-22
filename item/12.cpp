#include <iostream>
#include <memory>

template<typename T>
class TD;

class Data {
public:
    Data(){}

    Data(const Data&) {
        std::cout << "Data copy init" << std::endl;
    }

    Data& operator=(const Data&) {
        std::cout << "Data copy assignment init" << std::endl;
    }

    Data(Data&&) {
        std::cout << "Data move init" << std::endl;
    }
};


class Widget {
public:
    void doWork() & {
        std::cout << "lvalue function called" << std::endl;
    }

    void doWork() && {
        std::cout << "rvalue function called" << std::endl;
    }

    void doSome() const {
        std::cout << "const function called" << std::endl;
    }

    void doSome() {
        std::cout << "non const function called" << std::endl;
    }

    Data& getData() & {
        return data_;
    }

    Data&& getData() && {
        return std::move(data_);
    }

private:
    Data data_;
};

Widget makeWidget() {
    return Widget{};
}

int main() {
    std::unique_ptr<Widget> ptr = std::make_unique<Widget>();
    const Widget cw;
    Widget w;

    // const와 참조한정사에 따라 호출 예
    cw.doSome();
    w.doSome();

    w.doWork();
    makeWidget().doWork();
    ptr->doWork();

    // 멤버변수 참조 형식에 따라 생성자 호출 예

    // auto로 data1을 선언하면 2장의 규칙에 따라 getData의 참조형식을 잃고,
    // data1은 Data 타입이 된다. Data& 형식을 유지하려면 3장에 따라 decltype으로 선언
    // 그렇게 하면 Data의 복사생성 없이 w의 data를 참조한다. auto&로 선언도 마찬가지
    // 아래 data2도 decltype으로 참조하거나 이동생성을 호출하거나 둘 중 선택
    auto data1 = w.getData();
    // 참조한정사에 따라 중복적재 하지 않으면 lvalue 호출로 Data 복사생성자 호출 됨
    auto data2 = makeWidget().getData();
/*
    TD<decltype(data1)> d1Type;
    TD<decltype(data2)> d2Type;
*/
}
