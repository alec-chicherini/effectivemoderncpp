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
//PART3_1 {} () = 
//PART3_2 nullptr instead NULL and 0
//PART3_3 using insted typedef
//PART3_4 enums
//PART3_5 =deleted
//PART3_6 override
//PART3_7 ::iterator -> ::const_iterator
//PART3_8 noexcept
//PART3_9 constexpr
//PART3_10 const functions - thread free
//PART3_11 special funcs
//PART4_1 unique_ptr 
//PART4_2 shared_ptr 
//PART4_3 weak_ptr
//PART4_4 make instead of new
//PART4_5 Pimpl - in this file -> no example
//PART5_1 move & forward
//PART5_2 rvalue references
//PART5_3 rvalue with and without forward
//PART5_4 no universal reference overloading
//PART5_5 descriptor dispatch
//PART5_6 reference collapsing
//PART5_7 moving not always faster
//PART5_8 perfect forwarding
//PART6_1 lambda captures
//PART6_2 lambda move capture
//PART6_3 decltype for lambda
//PART6_4 std::bind vs lambda
//PART7_1 thread and async
//PART7_2 std::launch::async
//PART7_3 std::thread joinable and not
//PART7_4 std::future dtor
//PART7_5 conditinal varaible and future<void>
//PART7_6 std::atomic vc volatile
//PART8_1 copy params in function

#define PART8_1
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

#ifdef PART3_1
#include <string>
class bracer
{public:
    bracer() { cout << "default constructor"<<endl; }
    bracer(string str) {cout<<"one arg constructor : " << str << endl;}
    bracer(string str1, string str2) {cout << "two arg constructor :" << str1 << str2 << endl;}
    bracer(const bracer& br) { cout << "copy constructor" << endl; }
    bracer& operator=(const bracer& other) { cout << "operator= overloading" << endl; return *this; }
    bracer(initializer_list<string> il) { cout << "initializer list constructor" << endl; }
};

#endif

#ifdef PART3_3
#include <string>

void f(int x, const std::string& st) { cout << x << st << endl; };
typedef void (*FPTD)(int, const std::string&);
using FPU = void(*) (int, const std::string&);

#include< map>
#include <vector>

template<typename T>
using mapVec = map<vector<T>, T>;

#endif

#ifdef PART3_5
#include<iostream>
template<class T>
class deleters
{
public: 
    deleters<T>& operator=(const deleters<T>&) = delete;
    deleters<T>(const deleters<T>&) = delete;
    deleters<T>(T _t) : var(_t) {};

private:
    T var;
};


#endif

#ifdef PART3_6

class Base
{

public:
    //virtual int doWork() { std::cout << "Base::doWork\n"; };
    virtual int& doWork()&   { std::cout << "Base::doWork&::data "  << data << endl; return data; };
    virtual int&& doWork()&& { std::cout << "Base::doWork&&::data " << data << endl; return std::move(data); };
    Base&& takeObject() { return std::move(*this); }
private:
private:
    int data = 1;
};

class Derived :public Base
{

public:
   // virtual int doWork()  { std::cout << "Derived::doWork\n"; };
    virtual int& doWork()&   { std::cout << "Derived::doWork::data "   << data << endl;  return data; };
    //virtual int&& doWork()&& { std::cout << "Derived::doWork&&::data " << data << endl;  return std::move(data); };

    Derived&& takeObject() { return std::move(*this); }
private:
    int data = 2;
};

#endif

#ifdef PART3_7
#include <vector>
#endif

#ifdef PART3_8
 void func()noexcept {};
#endif

#ifdef PART3_9
 class X
 {
      int value;
    public:
        constexpr X(const int value_)  noexcept:value(value_){};
        constexpr const int mul(const X& x) const  noexcept{ return value * x.value; }
 };

#endif

#ifdef PART3_10
#include <mutex>
#include <chrono>
 class X
 {
     static int x;
 public:
     void const inc() 
     {
        // std::lock_guard<std::mutex> lg(mx);

         std::cout << x++ <<std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
        // mutable std::mutex mx;
 };

 int X::x = { 0 };

#endif

#ifdef PART3_11
 class test
 {
 public:
     test() { std::cout << "ctor->"; };//ctor
     ~test() { std::cout << "dtor|"; };//dtor
     test(const test& rhs) {};//copy 
     test& operator=( test& rhs) { std::cout << "copy assignment->"; return rhs;};//copy assignment 

     test(test&& rhs) {};//move 
     test& operator=(test&& rhs) { std::cout << "move assignment->"; return rhs; };// move assignment 
 };
#endif
 
#ifdef PART4_1
 auto deleter = [](int* data)
 {
     std::cout << "auto deleter call" << endl;
     delete data;
 };
 
 void deleter2(int* data)
 {
     std::cout << "func deleter call" << endl;
     delete data;
 
 };


#endif

#ifdef PART4_2
#include <vector>
#include <memory>
 class X:public std::enable_shared_from_this<X>
 {
     int _x;
     
 public:
     X(int&& x) :_x(x) {};
     auto from_this() {return shared_from_this(); };
 };

#endif

#ifdef PART4_3

#endif

#ifdef PART4_4
#include <string>
#include "S:\Code\ikvasir\timedelay\timedelay.h"
#include "S:\Code\ikvasir\timedelay\timedelay.cpp"

 class bigData
 {
     int intData[1000];
     string strData[1000];
 };

#endif

#ifdef PART5_1
 void f(int&& x)
 {
    std::cout<<boost_type_name<decltype(x)>()<<std::endl;
 };
#endif

#ifdef PART5_2

#endif

#ifdef PART5_3
#include "S:\Code\ikvasir\timedelay\timedelay.h"
#include "S:\Code\ikvasir\timedelay\timedelay.cpp"
#endif

#ifdef PART5_4
#include <vector>
#include "S:\Code\ikvasir\timedelay\timedelay.h"
#include "S:\Code\ikvasir\timedelay\timedelay.cpp"

 std::vector<std::string> vec;
 std::vector<std::string> vec2;


 template<typename T>
 void add_forward(T&& x)
 {
     vec.push_back(std::forward<T>(x));
 }

 void add_copy(std::string x)
 {
     vec2.push_back(x);
 }
#endif

#ifdef PART5_5
 template<typename T>
 void funcImpl(T&& x, std::false_type)
 {
     std::cout << "funcImpl - non integer" << std::endl;
 };

 template<typename T>
 void funcImpl(T&& x, std::true_type)
 {
     std::cout << "funcImpl - integer" << std::endl;
 };

 template<typename T>
 void func(T&& x)
 {
     using T_deref = std::remove_reference_t<T>;
     funcImpl(std::forward<T>(x), std::is_integral<T_deref>());
 };

 class A
 {
 public:

     template<typename T>
         void funcImpl(T&& x, std::true_type, std::false_type)
     {
         std::cout << "Iternal type object passed to func" << std::endl;
     };

     template<typename T>
         void funcImpl(T&& x, std::false_type, std::true_type)
     {
         std::cout << "A object passed to func" << std::endl;
     };

     template<typename T>
         void funcImpl(T&& x, std::false_type, std::false_type)
     {
         std::cout << "Undefined object pass to func" << std::endl;
     };

     template<typename T>
     void func(T&& x)
     {
         funcImpl(std::forward<T>(x),
             std::is_fundamental<std::decay_t<T>>(),
             std::is_same<std::decay_t<T>, A>());
     };

 };

 class B {};

#endif

#ifdef PART5_6


#endif

#ifdef PART5_7
#include "S:\Code\ikvasir\timedelay\timedelay.h"
#include "S:\Code\ikvasir\timedelay\timedelay.cpp"
#include <vector>
#include <array>
#endif

#ifdef PART5_8

 auto lambda = []<typename T>(T x) { std::cout << boost_type_name<T>()<<" "; };

 template<typename... Ts>
 void f(Ts... params)
 {
     (lambda(params), ...); std::cout << std::endl;
     (std::cout<<...<<params) << std::endl;
     
 }

 template<typename ...Ts>
 void fwd(Ts&& ... params)
 {
     f(std::forward<Ts>(params)...);
 }

 struct A
 {
     int x, y;
 };

 
#endif

#ifdef PART6_1
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

 template <typename T>
 struct is_vector { static const bool value = false; };

 template <typename T, typename A>
 struct is_vector <std::vector<T, A>>{static const bool value = true; };

 template <typename T>
 struct is_map { static const bool value = false; };

 template <typename T, typename A, typename K, typename C>
 struct is_map <std::map<T,A,K,C>> { static const bool value = true; };

 template<typename C>
 void ContainerFill(C& container, const int size)
 {
      if constexpr (is_vector<C>::value)
     for (int i = 0; i < size; i++)container.push_back(rand());

      if constexpr (is_map<C>::value)
     for (int i = 0; i < size; i++)container.insert(std::make_pair(i,rand()));
 }

 template<typename C>
 void ContainerSize(const C& container)
 {
     std::cout << "container type = " << boost_type_name<C>() << std::endl;
     std::cout << "container.size() = "<< container.size() << std::endl;
 }

 template<typename C>
 void ContainerErase( C& container)
 {
     for (auto it = container.begin(); it != container.end();)
     {
        it=container.erase(it);
     }

     std::cout << "Container Ereased "<<std::endl;
 }

 template<typename C>
 void ContainerPrint(C& container)
 {
     if constexpr (is_vector<C>::value)
         for (auto& i : container)std::cout << i << " ";

     if constexpr (is_map<C>::value)
         for (auto& i : container)std::cout << i.first <<"-"<<i.second<< " ";

  
     std::cout << std::endl;
 }

 template<typename C>
 void ContainerRemoveOdd(C& container)
 {
     if constexpr (is_vector<C>::value)
         for(auto it=container.begin(); it!=container.end();)
         {
             if (*it % 2 == 1)it = container.erase(it);
             else ++it;
         }
     if constexpr (is_map<C>::value)
         for (auto it = container.begin(); it != container.end();)
         {
             if (it->second % 2 == 1)it = container.erase(it);
             else ++it;
         }
     
 };

 template<typename C>
 void ContainerCheck(C& container)
 {
     int divider = 2;
     if constexpr (is_vector<C>::value){
     if (std::all_of(begin(container), end(container), [&](const auto& value) {return value % divider == 0; }))
         std::cout<<"All in this container devide by "<< divider<<std::endl;
     else
         std::cout << "NOT All in this container devide by " << divider << std::endl;
     }

     if constexpr (is_map<C>::value) {
         if (std::all_of(begin(container), end(container), [&](const auto& value) {return value.second % divider == 0; }))
             std::cout << "All in this container devide by " << divider << std::endl;
         else
             std::cout << "NOT All in this container devide by " << divider << std::endl;
     }
     
 }
#endif

#ifdef PART6_2
#include <array>
#endif

#ifdef PART6_3

#endif

#ifdef PART6_4
#include <functional>
 using namespace std::placeholders;
 void print(std::string a, std::string b, std::string c) { std::cout << a << b << c<<std::endl; }
#endif

#ifdef PART7_1

//#define TEST_MAX_THREAD
#define TEST_MAX_THREAD_ASYNC
#include <chrono>
#include <thread>
#include <future>
#include <vector>

 void func(){ std::this_thread::sleep_for(std::chrono::seconds(1000)); }

#endif

#ifdef PART7_2

#include <thread>
#include <future>


 void func() { std::this_thread::sleep_for(std::chrono::seconds(1)); }

 auto func2 = []< typename...Ts >(Ts&&...params) { (std::cout << ... << params)  << std::endl; };

 template<typename ... Ts, typename F>
 auto
 reallyAsync(F&& f, Ts&&... params)
 {
     
     return std::async(std::launch::async,
            f,
            std::forward<Ts>(params)...);
 }

#endif

#ifdef PART7_3
#include <thread>

 class ThreadRAII
 {
 public:
     enum class DtorAction { join, detach };

     ThreadRAII(std::thread&& t, DtorAction a) :action(a), t(std::move(t)) {}
     ThreadRAII() = delete;
     ThreadRAII(ThreadRAII&&) = default;
     ThreadRAII& operator=(ThreadRAII&&) = default;
     ~ThreadRAII() {
         if (t.joinable()) {
             if (action == DtorAction::join)t.join();
                 else t.detach();
         };
     };
     std::thread& get() { return t; }

 private:
     DtorAction action;
     std::thread t;
 
 };


#endif

#ifdef PART7_4
#include <iostream>
#include <future>
#include <thread>
#endif

#ifdef PART7_5
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

 std::mutex m;
 std::condition_variable cv_first,cv_second;
 bool ready_first = true;
 bool ready_second = false;

 void first() {
     while (1) {
       
         std::unique_lock<std::mutex> lk(m);
         cv_first.wait(lk, [] {return ready_second; }); ready_second = false;

         auto now = std::chrono::high_resolution_clock::now();
         std::this_thread::sleep_for(500ms);

         auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);
         std::cout << "..f(" << delay.count() << "ms).." << std::flush;

         ready_first = true; lk.unlock(); cv_second.notify_one();
     };
 }

 void second() {
     while (1) {

         std::unique_lock<std::mutex> lk(m);
         cv_second.wait(lk, [] {return ready_first; }); ready_first = false;

         auto now = std::chrono::high_resolution_clock::now();
         std::this_thread::sleep_for(250ms);

         auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now);
         std::cout << "..s(" << delay.count() << "ms).." << std::flush;

         ready_second = true; lk.unlock(); cv_first.notify_one();
     };
 }

#endif

#ifdef PART7_6
#include <atomic>
#include <thread>
#endif

#ifdef PART8_1

 void f(int i) { std::cout << " copy value->" << std::move(i) << std::endl; }
 //void f(int& i) { std::cout <<" lvalue->"<< i<<std::endl; }
 //void f(int&& i) { std::cout << " rvalue->" << std::move(i) << std::endl; }
 //template<typename T>  void f(T&& i){ std::cout << " frwded_value->" << std::forward<T>(i) << std::endl; }
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
     lambda(2, 3);
     lambda(1.4f, 5);
     lambda(1, 5.1f);

     //declaring lambda without auto
     std::function<bool(const int&, const int&)> lambdaF = [](const int& a, const int& b) {return a >= b; };
     cout << std::boolalpha;
     cout << lambdaF(1, 2) << endl;
     cout << lambdaF(4, 3) << endl;


#endif 

#ifdef PART2_2
     vector<char> vecChar = { 'a','b','c' };
     vector<int> vecInt = { 1,2,3 };
     vector<bool> vecBool = { 1,1,0 };

     auto c = vecChar[1];
     auto i = vecInt[1];
     auto b = vecBool[1];

     cout << boolalpha;
     cout << std::is_same<decltype(c), char>::value << endl;
     cout << std::is_same<decltype(i), int>::value << endl;
     cout << std::is_same<decltype(b), bool>::value << endl;

#endif

#ifdef PART3_1

     bracer a;
     bracer b{};
     a = b;
     bracer c(" 123 ");
     bracer d = c;

     bracer e();//function

     bracer f("1", "2");
     bracer g{ "3","4" };
     bracer h{ {} };
     bracer i({});

#endif

#ifdef PART3_2

     auto x = { nullptr };
     auto y = { 0 };
     auto z = { NULL };
     auto c = { false };
     cout << boost_type_name<decltype(x)> << endl;
     cout << boost_type_name<decltype(y)> << endl;
     cout << boost_type_name<decltype(z)> << endl;
     cout << boost_type_name<decltype(c)> << endl;

#endif

#ifdef PART3_3

     f(1, "23");

     FPTD ff = f;
     FPU fu = f;

     ff(4, std::string("56"));
     fu(7, std::string("89"));


     mapVec<int> mv{ {{1, 2, 3, 4},10} };
     cout << mv[{1, 2, 3, 4}] << endl;

#endif

#ifdef PART3_4
     enum class iEnum : int { a = 1, b = 2, c = 3 };
     cout << static_cast<int>(iEnum::b) << endl;

     constexpr auto lambda = []<typename E>(E enumerator) { return static_cast<underlying_type_t<E>>(enumerator); };
     cout << lambda(iEnum::c);


#endif

#ifdef PART3_5

     //deleters<int> dINT;   //error:no default constructor exists for class "deleters<int>"
     deleters<int> dINT2(4);
     deleters<int> dINT3(5);
     //dINT2 = dINT3;	//error: function "deleters<T>::operator=(const deleters<T> &) [with T=int]"  cannot be referenced -- it is a deleted function

#endif

#ifdef PART3_6


     std::unique_ptr<Base>    ptrBD = std::make_unique <Derived>();
     std::unique_ptr<Base>    ptrBB = std::make_unique <Base>();
     std::unique_ptr<Derived> ptrDD = std::make_unique <Derived>();

     //lvalue version call
     ptrBB.get()->doWork();
     ptrBD.get()->doWork();
     ptrDD.get()->doWork();

     //rvalue version call
     ptrBB.get()->takeObject().doWork();
     ptrBD.get()->takeObject().doWork();
     //ptrDD.get()->takeObject().doWork();


#endif

#ifdef PART3_7
     vector<int> vec = { 0,1,2,3,4,5 };
     auto iter = std::find_if(vec.cbegin(), vec.cend(), [](const int i) {return i % 2; });
     //*iter = -1;
     std::cout << *iter;
#endif

#ifdef PART3_8
     auto lambda = []() {};
     cout << noexcept(lambda()) << endl;
     cout << noexcept(func());

#endif

#ifdef PART3_9

     constexpr const  X x(4);
     constexpr auto y = x.mul(2);
     std::cout << y;
#endif // PART3_9

#ifdef PART3_10


     X x;
     x.inc();
     x.inc();
     x.inc();
     x.inc();
     x.inc();

     thread a([&]() {x.inc(); });
     thread b([&]() {x.inc(); });
     thread c([&]() {x.inc(); });
     thread d([&]() {x.inc(); });
     thread e([&]() {x.inc(); });

     a.join();
     b.join();
     c.join();
     d.join();
     e.join();



#endif

#ifdef PART3_11
     std::cout << "t#";
     test t;
     std::cout << std::endl;
     std::cout << "tt#";
     test tt;
     std::cout << std::endl;
     std::cout << "move#";
     t = test();
     std::cout << std::endl;
     std::cout << "copy#";
     t = tt;
     std::cout << std::endl;

#endif

#ifdef PART4_1

    std::unique_ptr<int> int_u_ptr = std::make_unique<int>(4);
    std::cout << "int_u_ptr = " << *int_u_ptr.get() << std::endl;

     
    std::unique_ptr<int, decltype(deleter)> int_u_ptr_custom_deleter;
    int_u_ptr_custom_deleter.reset(new int(5));
    std::cout << "int_u_ptr_deleter = " << *int_u_ptr_custom_deleter.get() << std::endl;

    
    std::unique_ptr<int> int_u_ptr_custom_deleter2;
    int_u_ptr_custom_deleter2.reset(new int(5));
    std::cout << "int_u_ptr_deleter = " << *int_u_ptr_custom_deleter2.get() << std::endl;
    
    deleter2(int_u_ptr_custom_deleter2.release());//delete object here
    if (int_u_ptr_custom_deleter2.release() == nullptr)cout << "managed object deleted" << endl;
    else cout << "managed  object NOT deleted" << endl;

    

#endif

#ifdef PART4_2
    X x(12345);

    
    shared_ptr<X> ptr1 = make_shared<X>(x);
    cout << "ptr1 - " << ptr1.use_count() << endl;
    cout  << endl;

    shared_ptr<X> ptr2 = ptr1;
    cout << "ptr1 - " << ptr1.use_count() << endl;
    cout << "ptr2 - " << ptr2.use_count() << endl;

    cout << endl;

    shared_ptr<X> ptr3 = std::move(ptr2);
    cout << "ptr1 - " << ptr1.use_count() << endl;
    cout << "ptr2 - " << ptr2.use_count() << endl;
    cout << "ptr3 - " << ptr3.use_count() << endl;
    cout << endl;

    shared_ptr<X> ptr4 = make_shared<X>(x);

    cout <<"ptr1 - " << ptr1.use_count() << endl;
    cout <<"ptr2 - " << ptr2.use_count() << endl;
    cout <<"ptr3 - " << ptr3.use_count() << endl;
    cout <<"ptr4 - " << ptr4.use_count() << endl;
    cout << endl;

    vector<shared_ptr<X>> vec;

    vec.emplace_back(ptr1 -> from_this());
    for (auto &s : vec)cout << s.use_count() << endl; cout << endl;

    cout << "ptr1 - " << ptr1.use_count() << endl;
    cout << "ptr2 - " << ptr2.use_count() << endl;
    cout << "ptr3 - " << ptr3.use_count() << endl;
    cout << "ptr4 - " << ptr4.use_count() << endl;
    cout << endl;

    vec.push_back(ptr3->from_this());
    for (auto &s : vec)cout << s.use_count() << endl; cout << endl;

    cout << "ptr1 - " << ptr1.use_count() << endl;
    cout << "ptr2 - " << ptr2.use_count() << endl;
    cout << "ptr3 - " << ptr3.use_count() << endl;
    cout << "ptr4 - " << ptr4.use_count() << endl;
    cout << endl;

    vec.push_back(ptr4->from_this());
    for (auto &s : vec)cout << s.use_count() << endl; cout << endl;

    cout << "ptr1 - " << ptr1.use_count() << endl;
    cout << "ptr2 - " << ptr2.use_count() << endl;
    cout << "ptr3 - " << ptr3.use_count() << endl;
    cout << "ptr4 - " << ptr4.use_count() << endl;
    cout << endl;
    

#endif

#ifdef PART4_3

    int x=4;

    auto sp = std::make_shared<int>(x);
    std::weak_ptr <int> wp(sp);
    std::cout<<wp.use_count()<<" - " << sp.use_count()<<std::endl;
    std::cout << std::endl;

    auto sp2=sp;
   
    std::cout << wp.use_count() << " - " << sp.use_count() << std::endl;
    std::cout << sp2.use_count()<< std::endl;
    std::cout << std::endl;

    std::weak_ptr <int> wp2(sp);
    std::cout << wp.use_count() << " - " << sp.use_count() << std::endl;
    std::cout << wp2.use_count() << " - " << sp2.use_count() << std::endl;
    std::cout << std::endl;

    std::cout << wp2.expired() << std::endl << std::endl;
    auto sp3 = wp2.lock();
    std::cout << wp.use_count() << " - " << sp.use_count() << std::endl;
    std::cout << wp2.use_count() << " - " << sp2.use_count() << std::endl;
    std::cout << sp3.use_count() << std::endl;
    std::cout << std::endl;

    std::cout<<wp2.expired() << std::endl << std::endl;

#endif

#ifdef PART4_4

    timedelay T;

    T.addTimer("usingNew");
    std::vector<std::shared_ptr<bigData>> spPool1;
    for (int i = 0; i < 10000; i++)
        spPool1.push_back(std::shared_ptr<bigData>(new bigData));
    std::cout << "usingNew = " << T.readTimer("usingNew") << "s." << std::endl;

    T.addTimer("usingMake");
    std::vector<std::shared_ptr<bigData>> spPool2;
    for (int i = 0; i < 10000; i++)
        spPool2.push_back(std::make_shared<bigData>());
    std::cout << "usingMake = " << T.readTimer("usingMake") <<"s."<< std::endl;

    //for 10000 at my pcresult is 7.684s at new and 7,396s at Make

#endif

#ifdef PART5_1
    
    f(1);
    int x = 4;
    int* x2 = new int(4);
    int& x3 = x;
    int&& x4 = 5;
    auto&& x5 = x;
    
    std::cout << boost_type_name<decltype(x)>()  << " -------> " << boost_type_name<decltype(std::move(x))>()  << std::endl;
    std::cout << boost_type_name<decltype(x2)>() << " -------> " << boost_type_name<decltype(std::move(x2))>() << std::endl;
    std::cout << boost_type_name<decltype(x3)>() << " -------> " << boost_type_name<decltype(std::move(x3))>() << std::endl;
    std::cout << boost_type_name<decltype(x4)>() << " -------> " << boost_type_name<decltype(std::move(x4))>() << std::endl;
    std::cout << boost_type_name<decltype(x5)>() << " -------> " << boost_type_name<decltype(std::move(x5))>() << std::endl;
    std::cout << std::endl;

    int y = 4;
    int* y2 = new int(4);
    int& y3 = y;
    int&& y4 = 5;
    auto&& y5 = x;

    std::cout << boost_type_name<decltype(y)>() << " -------> " << boost_type_name<decltype(std::forward<decltype(x)>(x))>() << std::endl;
    std::cout << boost_type_name<decltype(y2)>() << " -------> " << boost_type_name<decltype(std::forward<decltype(x2)>(x2))>() << std::endl;
    std::cout << boost_type_name<decltype(y3)>() << " -------> " << boost_type_name<decltype(std::forward<decltype(x3)>(x3))>() << std::endl;
    std::cout << boost_type_name<decltype(y4)>() << " -------> " << boost_type_name<decltype(std::forward<decltype(x4)>(x4))>() << std::endl;
    std::cout << boost_type_name<decltype(y5)>() << " -------> " << boost_type_name<decltype(std::forward<decltype(x5)>(x5))>() << std::endl;
#endif

#ifdef PART5_2
    int x = 1;
    auto&& x2 = x;
    auto&& x3 = 2;
  

    std::cout << boost_type_name<decltype(x)>() << std::endl;
    std::cout << boost_type_name<decltype(x2)>() << std::endl;
    std::cout << boost_type_name<decltype(x3)>() << std::endl;

    auto lambda = []<typename T>(T&& x)->decltype(x) { return x; };

    std::cout << boost_type_name<decltype(lambda(x))>() << std::endl;
    std::cout << boost_type_name<decltype(lambda(3))>() << std::endl;

#endif

#ifdef PART5_3
    timedelay Td;

    auto lambda = [](int&& x) {return x; };
    auto lambda2 = [](int&& x) {return std::move(x); };

    int x = 4;

    auto lambda3 = [=]() {return x; };
    auto lambda4 = [&]() {return std::move(x); };

    Td.addTimer("lambda_direct");
    for (int i = 0; i < 100000; i++)lambda(4);
    std::cout << Td.readTimer("lambda_direct") << std::endl;

    Td.addTimer("lambda_move");
    for (int i = 0; i < 100000; i++)lambda2(4);
    std::cout << Td.readTimer("lambda_move") << std::endl;

    Td.addTimer("lambda_direct2");
    for (int i = 0; i < 100000; i++)lambda3();
    std::cout << Td.readTimer("lambda_direct2") << std::endl;

    Td.addTimer("lambda_move2");
    for (int i = 0; i < 100000; i++)lambda4();
    std::cout << Td.readTimer("lambda_move2") << std::endl;

#endif

#ifdef PART5_4
    timedelay Td;

    std::string  x;
    x.resize(10000, '0');

    Td.addTimer("forward");
    for (int i = 0; i < 100000; i++)add_forward(x);
    std::cout << Td.readTimer("forward") << std::endl;

    Td.addTimer("copy");
    for (int i = 0; i < 100000; i++)add_copy(x);
    std::cout << Td.readTimer("copy") << std::endl;

#endif

#ifdef PART5_5
    func(1);
    func("str");
    func(1.2);
    std::cout << std::endl;

    A a, b;
    a.func(b);
    a.func(2);
    B c;

    a.func(c);

#endif

#ifdef PART5_6

    auto r = []() {return 5; };

    int x(0);
    std::cout << boost_type_name<decltype(x)>() << std::endl;
    auto& xl = x; //(& _)
    std::cout << boost_type_name<decltype(xl)>() << std::endl;
    auto&& xr = x; //(&& _)
    std::cout << boost_type_name<decltype(xr)>() << std::endl;
   // auto& xl2 = r();  //(& &&)
   // std::cout << boost_type_name<decltype(xl2)>() << std::endl;
    auto&& xr2 = xl;//(&& &)
    std::cout << boost_type_name<decltype(xr2)>() << std::endl;
    auto&& xr3 = r();//(&& &&)
    std::cout << boost_type_name<decltype(xr3)>() << std::endl;
    auto& xl3 = xl;//(& &)
    std::cout << boost_type_name<decltype(xl3)>() << std::endl;
    auto x2 = xl;//(_ &)
    std::cout << boost_type_name<decltype(x2)>() << std::endl;
    auto x3 = r();//(_ &&)
    std::cout << boost_type_name<decltype(x3)>() << std::endl;
#endif

#ifdef PART5_7
    timedelay Td;
    
    std::vector<int> vec(100);
    std::array<int, 100> arr; arr.fill(4);
    std::string str; str.resize(1000, 'a');
    std::string str2; str2.resize(10, 'z');
   

    auto lambda1 = [&]() {return vec; };
    auto lambda2 = [&]() {return std::move(vec); };
    auto lambda3 = [&]() {return arr; };
    auto lambda4 = [&]() {return std::move(arr); };
    auto lambda5 = [&]() {return str; };
    auto lambda6 = [&]() {return std::move(str); };
    auto lambda7 = [&]() {return str2; };
    auto lambda8 = [&]() {return std::move(str2); };

   
    auto test = [&](auto fn, std::string timer_name) {
        
        Td.addTimer(timer_name);
        for (int i = 0; i < 100000; i++)fn();
        std::cout << Td.readTimer(timer_name)*100 ;
    };
    std::cout << "copy       move" << std::endl;
    test(lambda1, "1"); std::cout <<" ";
    test(lambda2, "2"); std::cout << std::endl;
    test(lambda3, "3"); std::cout << " ";
    test(lambda4, "4"); std::cout << std::endl;
    test(lambda5, "5"); std::cout << " ";
    test(lambda6, "6"); std::cout << std::endl;
    test(lambda7, "7"); std::cout << " ";
    test(lambda8, "8"); std::cout << std::endl;

#endif

#ifdef PART5_8
 

       std::cout << std::endl;
       int *x = new int(1);
       float y = 2.3;
       std::string z = "4";
       fwd(*x,y,z);

       A a;
       a.x = 1;
       a.y = 2;
    
      // int&& b = a.x; //ERROR
       auto && b = a.x; //cast to lvalue ref
       std::cout << boost_type_name<decltype(b)>() << std::endl;


#endif

#ifdef PART6_1
       std::map<int, int> mp;
       std::vector<int> vec;

       ContainerFill(vec, 10);
       ContainerFill(mp, 10);

       ContainerSize(mp);
       ContainerSize(vec);

       ContainerPrint(vec);
       ContainerPrint(mp);

       ContainerCheck(vec);
       ContainerCheck(mp);

       ContainerRemoveOdd(vec);
       ContainerRemoveOdd(mp);

       ContainerPrint(vec);
       ContainerPrint(mp);

       ContainerCheck(vec);
       ContainerCheck(mp);

       ContainerErase(mp);
       ContainerErase(vec);

       ContainerSize(mp);
       ContainerSize(vec);

#endif

#ifdef PART6_2
       std::array<int, 3> A{1,2,3};
       auto prnt = [&] {for (auto& x : A)std::cout << x << " "; std::cout << std::endl; };
       auto func = [&](int mul) {for (auto& d : A) d *= mul; };
       auto func2 = [data = std::move(A)](){for (auto& d : data) std::cout << d << " "; std::cout << std::endl; };

       prnt();
       func(3);
       prnt();
       func2();
       prnt();

 

#endif

#ifdef PART6_3
       auto lambda = [](auto&& x) {return std::forward<decltype(x)>(x); };
       auto lambda2 = []<typename T>(T && x) { return std::forward<T>(x); };
       auto lambda_type_print = [](auto&& t) { std::cout << boost_type_name<decltype(t)>() << std::endl; };

       int i = 0;

       std::cout << boost_type_name<decltype(i)>() << std::endl;
       std::cout << boost_type_name<decltype(lambda(i))>() << std::endl;
       std::cout << boost_type_name<decltype(lambda2(i))>() << std::endl;
       std::cout << std::endl;
       lambda_type_print(i);  std::cout << std::endl;

       int& ii = i;
       std::cout << boost_type_name<decltype(ii)>() << std::endl;
       std::cout << boost_type_name<decltype(lambda(ii))>() << std::endl;
       std::cout << boost_type_name<decltype(lambda2(ii))>() << std::endl;
       std::cout << std::endl;

       lambda_type_print(ii);  std::cout << std::endl;

       int&&iii = 1;
       std::cout << boost_type_name<decltype(iii)>() << std::endl;
       std::cout << boost_type_name<decltype(lambda(iii))>() << std::endl;
       std::cout << boost_type_name<decltype(lambda2(iii))>() << std::endl;
       std::cout << std::endl;
       lambda_type_print(iii);  std::cout << std::endl;

#endif

#ifdef PART6_4

       print("1", "2", "3");
       auto print2 = std::bind(print, _3, _1, _2);
       print2("1", "2", "3");
#endif

#ifdef PART7_1
       std::vector<std::thread> t_vec;
       std::vector<std::future<void>> f_vec;
       while (1) {

#ifdef TEST_MAX_THREAD//after starting 10K+ thread nothing happen.
           t_vec.push_back(std::thread(func));
           std::cout << t_vec.size() << std::endl;
#endif


#ifdef TEST_MAX_THREAD_ASYNC//the same
           f_vec.push_back(std::async(func));
           std::cout << f_vec.size() << std::endl;
#endif

           
       
       };
#endif//PART7_1

#ifdef PART7_2
       
    auto fut = reallyAsync(func);//simple function call
    auto fut2 = reallyAsync(func2);//template lambda function call

#endif

#ifdef PART7_3

    ThreadRAII tr1(std::thread([] {std::cout << "ThreadRAII cover1 . joined \n"; }), ThreadRAII::DtorAction::join);
    ThreadRAII tr2(std::thread([] {std::cout << "ThreadRAII cover2 . detached \n"; }), ThreadRAII::DtorAction::detach);

#endif

#ifdef PART7_4
    //https://en.cppreference.com/w/cpp/thread/future
    // future from a packaged_task
    std::packaged_task<int()> task([] { return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
    std::thread t(std::move(task)); // launch on a thread

    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, [] { return 8; });


    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();

    std::cout << "Done!\nResults are: "
        << f1.get() << ' ' << f2.get()  << '\n';
    t.join();
#endif

#ifdef PART7_5
    std::thread f(first);
    std::thread s(second);
    f.join();
    s.join();
#endif

#ifdef PART7_6
    std::atomic<int> ai=0;
    volatile int vi = 0;//on count 10 000-100 000 this value not equal atomic
    int i = 0;//on count 10 000-100 000 this value not equal atomic

    int count = 100000;

    while (count--) {

        std::thread t1([&] {i++; vi++; ai++; });
        std::thread t2([&] {i++; vi++; ai++; });
       
        t2.join();
        t1.join();
    };

    std::cout << "ai = " << ai << " vi = " << vi << " i = " << i;

#endif

#ifdef PART8_1
    int i=4;
    f(2);

#endif
    return 0;
}
