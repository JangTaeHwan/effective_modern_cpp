#include <string>
#include <memory>
#include <list>
#include <type_traits>	// 형변환 템플릿들
#include <iostream>

using UserInfo = std::tuple<std::string, std::string, std::size_t>;


enum UserInfoFields_ { uiName, uiEmail, uiRequtation };

enum class UserInfoFields : uint8_t { uiName, uiEmail, uiRequtation };


// std::underlying_type 는 T가 enumeration 일 때만 정의 됨
// 밑에 3개 템플릿 변화는 9장 복습
template<typename E>
constexpr typename std::underlying_type<E>::type
toUType(E enumerator) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

template<typename E>
constexpr std::underlying_type_t<E>
toUType2(E enumerator) noexcept {
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

template<typename E>
constexpr auto
toUType3(E enumerator) noexcept {
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

int main() {

    UserInfo uInfo{"jang", "jang@naver.com", 1};

    // enum의 장점, 범위 없는 형식에 반환 형식도 자유로움
    auto name = std::get<uiName>(uInfo);

    // 반면 enum class 경우 범위와 형식이 엄격해 코드가 좀 더 길어진다
    //auto email = std::get<static_cast<uint8_t>(UserInfoFields::uiEmail)>(uInfo);
    auto email = std::get<toUType3(UserInfoFields::uiEmail)>(uInfo);

    std::cout << name << " " << email << std::endl;

    return 0;
}
