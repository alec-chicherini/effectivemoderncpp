// ScotMayersBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <typeinfo>
#include <vector>
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
#define PART1_4
//////////////////////////////////////////////


#ifdef PART1_1

// changing the type of template param between T - T& - T&& to see different type convertion after template oppenning
//T      or T&          or T&&
//TYPE_T or TYPE_T_LREF or TYPE_T_RREF
#define TYPE_T_LREF


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

    auto x (20); cout << boost_type_name<decltype(x)>() << endl;
    auto& y = x; cout << boost_type_name<decltype(y)>() << endl;
    auto&& z = 30 ; cout << boost_type_name<decltype(z)>() << endl;
    
    auto a { 20 }; cout << boost_type_name<decltype(a)>() << endl;
    auto b = { 20 }; cout << boost_type_name<decltype(b)>() << endl;

#endif


#ifdef PART1_3

    Point A;
    std::cout << boost_type_name<decltype(A)>()<<endl;

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
    cout<<boost_type_name<decltype(x)>()<<endl;
    cout << endl;

    const int& y = x;
    cout << typeid(y).name() << endl;
    cout<<boost_type_name<decltype(y)>()<<endl;
    cout << endl;

    Widjet w;
    const Widjet& z = w;
    cout << typeid(z).name() << endl;
    cout<<boost_type_name<decltype(z)>()<<endl;
   
   
    

#endif
}
