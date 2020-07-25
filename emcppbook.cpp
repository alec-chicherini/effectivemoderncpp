// ScotMayersBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>
 
using namespace std;

///returning type of variables and some objects using boost library.
template<typename T>
std::string boost_type_name()
{
    return boost::typeindex::type_id_with_cvr<T>().pretty_name();
}


//////////////////////////////////////////////
//PART1_1 template type
//PART1_2 auto
//PART1_3 decltype
//PART1_4 displaing types
//PART2_1 auto more prefereable
//PART2_2 auto is bad
#define PART2_2
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
    cout << " | T =  " << boost_type_name<T>();
    cout << " | param = " << boost_type_name<decltype(param)>() << endl;
};



//function
void someFunc(int, double) {};

#endif

#ifdef PART1_3

#include <vector>
template<typename Container, typename Index>
decltype(auto) containerReturn(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}


struct Point {
    int x, y;
};
#endif

#ifdef PART1_4

struct Widjet { char* name; };
#endif

#ifdef PART2_1
#include <functional>
#endif

#ifdef PART2_2
#include <vector>
#include <type_traits>
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

    std::cout << "template<typename T>" << endl
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

    std::cout << "type passed to f | T type| param type" << endl;
    std::cout << boost_type_name<decltype(x)>(); f(x);
    std::cout << boost_type_name<decltype(sx)>(); f(sx);
    std::cout << boost_type_name<decltype(cx)>(); f(cx);
    std::cout << boost_type_name<decltype(rx)>(); f(rx);

    std::cout << boost_type_name<decltype(ptr)>(); f(ptr);
    std::cout << boost_type_name<decltype(ptrc1)>(); f(ptrc1);
    std::cout << boost_type_name<decltype(ptrc2)>(); f(ptrc2);
    std::cout << boost_type_name<decltype(ptrcc)>(); f(ptrcc);

    std::cout << boost_type_name<decltype(arr)>(); f(arr);
    std::cout << boost_type_name<decltype(ptrToArr)>(); f(ptrToArr);
    std::cout << boost_type_name<decltype(carr)>(); f(carr);
    std::cout << boost_type_name<decltype(ptrToCArr)>(); f(ptrToCArr);

    std::cout << boost_type_name<decltype(someFunc)>(); f(someFunc);


#ifdef TYPE_T_RREF
    std::cout << " number 12 "; f(12);
#endif // TYPE_RREF



#endif


#ifdef PART1_2

    auto x(20); cout << boost_type_name<decltype(x)>() << endl;
    auto& y = x; cout << boost_type_name<decltype(y)>() << endl;
    auto&& z = 30; cout << boost_type_name<decltype(z)>() << endl;

    auto a{ 20 }; cout << boost_type_name<decltype(a)>() << endl;
    auto b = { 20 }; cout << boost_type_name<decltype(b)>() << endl;

#endif


#ifdef PART1_3

    Point A;
    std::cout << boost_type_name<decltype(A)>() << endl;

    vector<int> ivec = { 1,2,3 };
    std::cout << boost_type_name<decltype(ivec)>() << endl;

    auto var1 = containerReturn(ivec, 0);
    std::cout << boost_type_name<decltype(var1)>() << endl;

    decltype(var1) var2;
    std::cout << boost_type_name<decltype(var2)>() << endl;


    const int& cx = 1;
    std::cout << boost_type_name<decltype(cx)>() << endl;

    auto x2 = cx;
    std::cout << boost_type_name<decltype(x2)>() << endl;

    decltype(auto) x3 = cx;
    std::cout << boost_type_name<decltype(x3)>() << endl;

    auto lambda = []() {return 3; };
    std::cout << boost_type_name<decltype(lambda)>() << endl;




#endif


#ifdef PART1_4
    int x = 5;
    cout << typeid(x).name() << endl;
    cout << boost_type_name<decltype(x)>() << endl;
    cout << endl;

    const int& y = x;
    cout << typeid(y).name() << endl;
    cout << boost_type_name<decltype(y)>() << endl;
    cout << endl;

    Widjet w;
    const Widjet& z = w;
    cout << typeid(z).name() << endl;
    cout << boost_type_name<decltype(z)>() << endl;



#endif

#ifdef PART2_1

    //using auto in all parts of lambda
    auto lambda = [](auto&& x, auto&& y) { cout << x + y << " " << boost_type_name<decltype(x + y)>() << endl; };
   lambda(2,3);
   lambda(1.4f, 5);
   lambda(1, 5.1f);

   //declaring lambda without auto
   std::function<bool(const int&, const int&)> lambdaF = [](const int& a, const int& b) {return a >= b; };
   cout << std::boolalpha;
   cout << lambdaF(1, 2)<<endl;
   cout << lambdaF(4, 3) << endl;


#endif // 

#ifdef PART2_2
   vector<char> vecChar = { 'a','b','c' };
   vector<int> vecInt = { 1,2,3 };
   vector<bool> vecBool = { 1,1,0 };

   auto c = vecChar[1];
   auto i = vecInt[1];
   auto b = vecBool[1];

   cout << boolalpha;
   cout << std::is_same<decltype(c),char>::value << endl;
   cout << std::is_same<decltype(i),int>::value << endl;
   cout << std::is_same<decltype(b),bool>::value << endl;
 
#endif

    return 0;
}
