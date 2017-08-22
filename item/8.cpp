#include <iostream>
#include <vector>
#include <mutex>
#include <memory>

class Widget;

bool f1(std::shared_ptr<Widget>) {
    std::cout << "f1 func called" << std::endl;
    return true;
}

bool f2(std::unique_ptr<Widget>) {
    std::cout << "f2 func called" << std::endl;
    return true;
}

bool f3(Widget*) {
    std::cout << "f3 func called" << std::endl;
    return true;
}

template<typename FuncType,
         typename MuxType,
         typename PtrType>
decltype(auto) lockAndCall(FuncType func,
                           MuxType& mutex,
                           PtrType ptr) {

    using MuxGuard = std::lock_guard<MuxType>;

    MuxGuard g(mutex);
    return func(ptr);
}


int main() {
    std::mutex f1m, f2m, f3m;

    auto result1 = lockAndCall(f1, f1m, 0);
//    auto result2 = lockAndCall(f2, f2m, NULL);
    auto result3 = lockAndCall(f3, f3m, nullptr);

}
