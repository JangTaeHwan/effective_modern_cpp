#include <iostream>
#include <string>
#include <atomic>
#include <mutex>

class Widget {
public:
    uint64_t value() const {
        if (cacheValid) {
            return cachedValue;
        } else {
            auto val1 = std::string("expensive Computation");
            auto val2 = std::string("expensive Computation");
            // 멀티스레드 환경에서 멤버 변수 cachedValue에 대해 원자성을 보장하기 위해
            // atomic으로 선언하고 캐시 확인 또한 atomic으로 선언할 경우
            // 겉보기에는 효율적이고 잘 동작할 것처럼 보이지만 위의 비싼 연산을 여러번 하거나
            // cachedValue가 유효하지 않는 경우가 생긴다.
            cachedValue = val1.size() + val2.size();
            cacheValid = true;
            return cachedValue;
        }

        // 따라서 위 경우 처럼 둘 이상 변수나 메모리 조작을 하나의 단위에서 조작해야 할 때는
        // atomic 보다는 mutex로 전체를 lock거는 방식이 좋다.
        std::lock_guard<std::mutex> guard(m);
    }

private:
    // const 내에서 변수의 값을 조정할 때 mutable 선언
    mutable std::mutex m;
    mutable std::atomic<bool> cacheValid { false };
    mutable std::atomic<uint64_t> cachedValue;
};

int main() {


}
