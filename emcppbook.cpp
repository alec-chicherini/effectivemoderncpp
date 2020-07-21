// ScotMayersBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <typeinfo>
 
using namespace std;

/////////////////////////////////////////////////////////////////////////////
//  source code from here https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
//output the type of object/vars with different compilers
//type_name() return string with name of type
/////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <ostream>
#include <functional>

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
inline std::ostream& operator<<(std::ostream& os, static_string const& s)
{
    return os.write(s.data(), s.size());
}
template <class T> CONSTEXPR14_TN static_string type_name()
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
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////
//PART1_1 template type
//PART1_2 auto
#define PART1_2
//////////////////////////////////////////////
#ifdef PART1_1

// changing the type of template param between T - T& - T&& to see different type convertion after template oppenning
//T      or T&          or T&&
//TYPE_T or TYPE_T_LREF or TYPE_T_RREF
#define TYPE_T_RREF


template<typename T>

#ifdef TYPE_T
       void f(T param) 
#endif

#ifdef TYPE_T_LREF
       void f(T& param) 
#endif

#ifdef TYPE_T_RREF
        void f(T&& param) 
#endif

{
    cout << " | T =  " << type_name<T>();
    cout << " | param = " << type_name<decltype(param)>() << endl;
};



//function
void someFunc(int, double) {};

#endif

#ifdef PART1_2

///////////////////
///////////////////

#endif


int main()
{

#ifdef PART1_1
    
    //general
    int x = 12;
    int& sx = x;
    const int cx = x;
    const int& rx = x;

    //pointers
    int* ptr = &x;
    int* const ptrc1 = &x;
    const int* ptrc2 = &x;
    const int* const ptrcc = &x;
    
    //arrays
    int arr[] = { 1,2,3 };
    int* ptrToArr = arr;

    const int carr[] = { 1,2 };
    const int* ptrToCArr = arr;

    std::cout << "template<typename T>"<<endl
#ifdef TYPE_T
     << "void f(T param)"
#endif
#ifdef TYPE_T_LREF
     << "void f(T& param)"
#endif
#ifdef TYPE_T_RREF
     << "void f(T&& param)"
#endif
     << endl;
    
    std::cout << "type passed to f | T type| param type"<<endl;
    std::cout << type_name<decltype(x)>(); f(x);
    std::cout << type_name<decltype(sx)>(); f(sx);
    std::cout << type_name<decltype(cx)>(); f(cx);
    std::cout << type_name<decltype(rx)>(); f(rx);

    std::cout << type_name<decltype(ptr)>(); f(ptr);
    std::cout << type_name<decltype(ptrc1)>(); f(ptrc1);
    std::cout << type_name<decltype(ptrc2)>(); f(ptrc2);
    std::cout << type_name<decltype(ptrcc)>(); f(ptrcc);
    
    std::cout << type_name<decltype(arr)>(); f(arr);
    std::cout << type_name<decltype(ptrToArr)>(); f(ptrToArr);
    std::cout << type_name<decltype(carr)>(); f(carr);
    std::cout << type_name<decltype(ptrToCArr)>(); f(ptrToCArr);

    std::cout << type_name<decltype(someFunc)>(); f(someFunc);


#ifdef TYPE_T_RREF
    std::cout << " number 12 "; f(12);
#endif // TYPE_RREF
 
 

#endif


#ifdef PART1_2

    auto x (20); cout << type_name<decltype(x)>() << endl;
    auto& y = x; cout << type_name<decltype(y)>() << endl;
    auto&& z = 30 ; cout << type_name<decltype(z)>() << endl;
    
    auto a { 20 }; cout << type_name<decltype(a)>() << endl;
    auto b = { 20 }; cout << type_name<decltype(b)>() << endl;

#endif

}
