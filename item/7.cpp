#include <string>
#include <vector>
#include <iostream>


class Widget {
public:
    Widget() {
        std::cout << "default init" << std::endl;
    }
    Widget(int i, bool d) {
        std::cout << "int bool init" << std::endl;
    }
    Widget(int i, double d) {
        std::cout << "int double init" << std::endl;
    }
    Widget(std::initializer_list<long double> il) {
        std::cout << "initializer init" << std::endl;
    }

    Widget(const Widget& w) {
        std::cout << "copy init" << std::endl;
    }
    operator float() const {
        return 0.1f;
    }
};


int main() {
    Widget wt0{};
    Widget wt1({});

    Widget w1{1, true};
    Widget w2{1, 1.32};
    Widget w3(1, 1.32);
    Widget w4{1.21, 1.32};

    Widget w5(w1);
    Widget w6{w1};

    Widget w7(std::move(w1));
    Widget w8{std::move(w1)};

    return 0;
}
