#include <memory>
#include <iostream>


class Investment {
public:
    virtual ~Investment() {
        std::cout << "Investment destroctor called" << std::endl;
    }
};

class Stock: public Investment {
public:
    ~Stock() {
        std::cout << "Stock destroctor called" << std::endl;
    }
};

class Bond:
    public Investment{};

class RealEstate:
    public Investment{};

auto delInv = [] (Investment* pInv)
{
    // do something
    std::cout << "delInv called" << std::endl;
    delete pInv;
};

std::string invType = "stock";

template<typename... Ts>
auto makeInvestment(Ts&&... params)
{
    std::unique_ptr<Investment, decltype(delInv)>
        pInv(nullptr, delInv);

    if (invType == "stock")
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if (invType == "Bond")
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if (invType == "RealEstate")
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }

    return pInv;
}


// unique_ptr deleter 사용자 정의시 크기
// 상태 없는 함수 객체(갈무리 없는 람다식) -> 크기 변화 없음
// 상태 있는 함수 객체 -> 상태를 저장하는 변수 크기 만큼 증가
// 함수 포인터 -> 2워드로 증가(기존 1워드)

// unique_ptr 은 다음 두 가지 형식이 있다
// 개별 객체: unique_ptr<T>   (operator [] 제공 안함)
// 배열 형식: unique_ptr<T[]> (operator *, -> 제공 안함)
// 주로 배열 형식 unique_ptr 생성 보다는 내장된 stl 사용 선호
// unique_ptr -> shared_ptr 변환 가능

int main() {
    auto myInv = makeInvestment();
}
