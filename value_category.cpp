//
// Created by KinoluKaslana on 18-8-30.
//
//
#include <iostream>
struct Test_Class_VC
{
    int foo;
    virtual void fun(){std::cout<<"Base"<<std::endl;}
    static int foo1;
    static void fun1(){}
    enum {em1,em2};
};
int Test_Class_VC::foo1 = 1;
void func(){}
static auto &&fun(){return func;}
bool _lvalue()
{
    std::cout<<"In lvalue"<<std::endl;
    int Test_Class_VC::*foo_p = &Test_Class_VC::foo;
    void (*sfun_p)() = &Test_Class_VC::fun1;
    int *sfoo_p = &Test_Class_VC::foo1;                     //左值性质，可被取址
    int foo1 = 1,foo2 = 0,foo3 = 0,foo4 = 0,foo5,foo6;
    int arr[foo1];
    Test_Class_VC obj,*pobj = new Test_Class_VC();
    foo1 += foo2 -= foo3 *= foo4 /= foo5 = foo6 = 1;        //所有的赋值,复合的赋值运算表达式都是一个左值
    std::cout<<foo1<<foo2<<foo3<<foo4<<foo5<<foo6<<std::endl;
    ++foo1 = --foo2 = 2;                                    //借助左值性质，可作为赋值运算符及其复合运算的左操作数，得到，前置自增为左值
    *sfoo_p = 2;                                            //内建的间接寻址（*）表达式
    arr[0] = 2;                                             //内建的下标表达式
    obj.foo = 2;
    obj.foo1 = 2;                                           //访问非枚举量非静态成员函数的对象成员表达式
    obj.fun1();                                             //对于对象成员表达式来说为左值，但是整个函数调用表达式则是一个纯右值
                                                            //推论，可通过检查列表达式：
    //auto temp_foo = &obj.fun;
    //auto temp_foo = &obj.fun1;
    pobj->foo = 2;                                          //指针成员表达式和成员表达式同理
    pobj->foo1 = 2;
    &Test_Class_VC().fun1;                                  //对象为右值，对象成员为非引用类型的非静态数据成员，表达式为左值
    obj.*foo_p = 1;                                         //对象为左值内建的指针的成员表达式
    pobj->*foo_p = 1;                                       //内建的指针的成员指针表达式
    (1,foo1) = 1;                                           //逗号表达式，并且要求最右运算数为左值
    auto &T1 = ++foo1 = --foo2;
    auto &T2 = std::cout<<std::endl;
    auto &T3 = *sfoo_p;
    auto &T4 = arr[0];
    auto &T5 = obj.fun1;
    auto &T6 = obj.*foo_p;
    auto &T7 = pobj->*foo_p;
    auto &T8 = (1,2,3,4,foo1);
    auto &T9 = fun();                                       //返回为函数的右值引用的函数的表达式
    auto &T10 = static_cast<void (&&)()>(func);             //函数类型转为函数的右值引用的表达式
    auto &EX = "qwert";                                     //字符串字面量也是一个左值

                                                            //性质总结：
                                                            //左值可以被取址
                                                            //左值可以被用作内建赋值，复合赋值运算符的左操作数
                                                            //左值可以绑定为左值引用
    delete pobj;
    return true;
}
//ToDo完成下列事项，发表简书
struct Test_Class_VC_1:Test_Class_VC
{
    virtual void fun() final {std::cout<<"Special"<<std::endl;}
};
Test_Class_VC &&func1()
{
    return Test_Class_VC_1();
}
bool _prvalue()
{
    std::cout<<"In prvalue"<<std::endl;
    void (Test_Class_VC::*fun_p)() = &Test_Class_VC::fun;
    void (*sfun_p)() = &Test_Class_VC::fun1;
    int *sfoo_p = &Test_Class_VC::foo1;
    int foo1 = 1,foo2 = 0,foo3 = 0,foo4 = 0,foo5,foo6;
    int arr[foo1];
    Test_Class_VC obj,*pobj = new Test_Class_VC();
    auto && T1 = foo1--;
    auto && T2 = foo2++;                                                 //内建的后置自增自减
    auto && T3 = foo1 + foo2;
    const auto & T4 = foo3 && foo4;
    auto && T5 = &foo2;
    auto && T6 = foo5 < foo6;                                            //内建的除赋值及复合赋值运算符之外的所有算术，逻辑，比较，取址表达式
    //&obj.fun;
    //&obj.em1;
    //&pobj->fun;
    //&pobj->em1;                                                        //内建的对象成员，指针成员，其访问的成员为枚举项或非静态的函数
    (obj.*fun_p)();
    (pobj->*fun_p)();                                                    //内建的对象成员为非静态函数和枚举项的成员指针，指针成员指针表达式
    auto && T7 = static_cast<int>(foo1);                                 //转换为非引用，或函数调用和重载运算符返回非引用的表达式
    //this，和枚举项
    auto && T8 = [](){};                                                 //lambda表达式
    //这里借助的主要是右值的通用性质：能初始化const的左值引用，和右值引用
    //纯右值的性质：
    Test_Class_VC_1().fun();
    ((Test_Class_VC)Test_Class_VC_1()).fun();                            //纯右值不能多态
                                                                         //非类非数组的纯右值不能有CV限定，如果是一个带CV限定为返回值的函数（类型表达式）那么此时CV符会被立刻剥离

    delete pobj;
    return true;
}
bool _xvalue()
{
    std::cout<<"In xvalue"<<std::endl;

    //func1().fun();                                                    //返回右值引用的函数调用和重载运算符表达式
                                                                        //在Debug下可以尝试运行这个代码，也许栈还没有被回收，由于没有右值引用接受
                                                                        //导致对象生存期随栈回朔被释放

    (int [3]){1,2,3}[2];                                                //右值数组的下标访问表达式
    int Test_Class_VC::*foo_p = &Test_Class_VC::foo;

    //&Test_Class_VC_1().foo;
    //&(Test_Class_VC().*foo_p);                                        //对象的成员指针表达式，对象是右值，成员指针指向数据
                                                                        //转换为右值引用的类型转换表达式
                                                                        //性质：
                                                                        //亡值可以绑定到右值引用
    static_cast<Test_Class_VC &&>(Test_Class_VC_1()).fun();             //亡值可以多态
                                                                        //亡值可以有cv限定（即返回右值带有CV限定的函数表达式等）
    return true;
}
bool main_value_category()
{
    return _lvalue() && _prvalue() && _xvalue();
    //泛左值，右值，特性看简书总结。
}