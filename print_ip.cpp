#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <tuple>

using namespace std;

template<typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
void print_ip(const T& in) {
    cout << in << endl;
}

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void print_ip(const T& in) {
    for (auto i = sizeof(in); i > 0; i--) {
        cout << ((in >> 8 * (i-1)) & 0xFF);
        if (i - 1 > 0) {
            cout << ".";
        }
    }

    cout << endl;
}

template <
        template <typename, typename > typename Container,
        typename Type,
        typename Allocator = std::allocator<Type>,
        typename = enable_if_t<
                is_same_v<Container<Type, Allocator>, vector<Type, Allocator>> ||
                is_same_v<Container<Type, Allocator>, list<Type, Allocator>>
        >>
void print_ip(const Container<Type, Allocator> &container) {
    for (auto i = container.begin(); i != container.end(); i++) {
        if (i != container.begin()) {
            cout << ".";
        }
        cout << *i;
    }

    cout << endl;
}

template<typename... Ts>
struct AllSame;

template<>
struct AllSame<> : std::true_type {};

template<typename T>
struct AllSame<T> : std::true_type {};

template<typename First, typename Second, typename... Rest>
struct AllSame<First, Second, Rest...>
        : std::conditional_t<
                std::is_same_v<First, Second>,
                AllSame<Second, Rest...>,
                std::false_type
        > {};

template <size_t I = 0, typename... Ts>
constexpr void printTuple(tuple<Ts...> tup)
{
    if
    constexpr(I == sizeof...(Ts))
    {
        return;
    }
    else {
        cout << get<I>(tup);
        if (I + 1 < sizeof...(Ts)) {
            cout << ".";
        }
        printTuple<I + 1>(tup);
    }
}

template <typename... Ts, typename = std::enable_if_t<AllSame<Ts...>::value>>
void print_ip(tuple<Ts...> in) {
    printTuple(in);
}

int main() {
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100

    print_ip( std::make_tuple(123, 456, 789, 23) ); // 123.456.789.0

//    print_ip( std::forward_list<int>{1000, 2000, 3000, 4000} ); // 100.200.300.400 // 400.300.200.100
}