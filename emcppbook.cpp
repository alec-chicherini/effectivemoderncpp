// ScotMayersBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <typeinfo>
 

using namespace std;



#define PART1

#ifdef PART1
// untill f func source code from here https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <ostream>




#ifndef _MSC_VER
#  if __cplusplus < 201103
#    define CONSTEXPR11_TN
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN
#  elif __cplusplus < 201402
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN noexcept
#  else
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN constexpr
#    define NOEXCEPT_TN noexcept
#  endif
#else  // _MSC_VER
#  if _MSC_VER < 1900
#    define CONSTEXPR11_TN
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN
#  elif _MSC_VER < 2000
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN noexcept
#  else
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN constexpr
#    define NOEXCEPT_TN noexcept
#  endif
#endif  // _MSC_VER

class static_string
{
    const char* const p_;
    const std::size_t sz_;

public:
    typedef const char* const_iterator;

    template <std::size_t N>
    CONSTEXPR11_TN static_string(const char(&a)[N]) NOEXCEPT_TN
        : p_(a)
        , sz_(N - 1)
    {}

    CONSTEXPR11_TN static_string(const char* p, std::size_t N) NOEXCEPT_TN
        : p_(p)
        , sz_(N)
    {}

    CONSTEXPR11_TN const char* data() const NOEXCEPT_TN { return p_; }
    CONSTEXPR11_TN std::size_t size() const NOEXCEPT_TN { return sz_; }

    CONSTEXPR11_TN const_iterator begin() const NOEXCEPT_TN { return p_; }
    CONSTEXPR11_TN const_iterator end()   const NOEXCEPT_TN { return p_ + sz_; }

    CONSTEXPR11_TN char operator[](std::size_t n) const
    {
        return n < sz_ ? p_[n] : throw std::out_of_range("static_string");
    }
};

inline
std::ostream&
operator<<(std::ostream& os, static_string const& s)
{
    return os.write(s.data(), s.size());
}

template <class T>
CONSTEXPR14_TN
static_string
type_name()
{
#ifdef __clang__
    static_string p = __PRETTY_FUNCTION__;
    return static_string(p.data() + 31, p.size() - 31 - 1);
#elif defined(__GNUC__)
    static_string p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return static_string(p.data() + 36, p.size() - 36 - 1);
#  else
    return static_string(p.data() + 46, p.size() - 46 - 1);
#  endif
#elif defined(_MSC_VER)
    static_string p = __FUNCSIG__;
    return static_string(p.data() + 38, p.size() - 38 - 7);
#endif
}




template<typename T>
// changing the type of template param between T - T& - T&&
void f(T& param) {
    T tvar(param);
    cout << " | T =  " << type_name<decltype(tvar)>();
    cout << " | param = " << type_name<decltype(param)>() << endl;
};

#endif

int main()
{

#ifdef PART1

    int x = 12;
    int& sx = x;
    const int cx = x;
    const int& rx = x;

    int* ptr = &x;
    int* const ptrc1 = &x;
    const int* ptrc2 = &x;
    const int* const ptrcc = &x;

    std::cout << type_name<decltype(x)>(); f(x);
    std::cout << type_name<decltype(sx)>(); f(sx);
    std::cout << type_name<decltype(cx)>(); f(cx);
    std::cout << type_name<decltype(rx)>(); f(rx);
    std::cout << type_name<decltype(ptr)>(); f(ptr);
    std::cout << type_name<decltype(ptrc1)>(); f(ptrc1);
    std::cout << type_name<decltype(ptrc2)>(); f(ptrc2);
    std::cout << type_name<decltype(ptrcc)>(); f(ptrcc);

    //std::cout << " number 1 " << " -> "; f(1);


#endif



}
