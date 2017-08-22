#include <string>
#include <memory>
#include <vector>

class Widget {
public:
	Widget();
	~Widget();			// 여기서 ~Widget() 선언시 컴파일 에러(effective c++ 항목 22 참조)
						// 멤버변수로 pImpl을 가지고 있어서 소멸자에 pImpl을 delete하는
						// 코드가 내부적으로 inline되어 들어가고 그 이전에 표준 라이브러리에서
						// static_assert로 Impl이 완전한 형식인지를 판단한다.
						// 따라서 pimpl에서 delete 구현은 Impl 선언 부 이후에 있어야 한다.

	std::string getName();
private:
	struct Impl;
	std::unique_ptr<Impl> pImpl;
};
