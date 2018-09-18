//
// Created by KinoluKaslana on 18-9-18.
//
//本例程和相关说明在：https://www.jianshu.com/p/8933f0893821
#include "AllCore.h"
NS_COPY_ELISION
class T1{
public:
    int foo;
    T1(){std::cout<<this<<" Call ! "<<std::endl;}
    T1(T1 &src){std::cout<<&src<<" Call &! "<<this<<std::endl;}
    T1(T1 &&src){std::cout<<&src<<" Call &&! "<<this<<std::endl;}
    friend T1 operator+(T1 &,int);
    friend T1 operator+(T1 &&,int);
};
T1 operator+(T1 &src,int i){
    src.foo += i;
    return src;
}
T1 operator+(T1 &&src,int i){
    src.foo += i;
    return src;
}
T1 func1(){
    T1 foo1;                                                        //调用构造函数，直接在调用方所在的栈区
    foo1 + 1;                                                       //返回时使用复制构造，临时变量实质化
    return foo1;                                                    //但是这种情况下，不一定使用复制消除
}
T1 func2(){
    return T1() + 1;                                                //同F1，但是此时是存在一个匿名的此时必定使用复制消除
    //注意，此时复制消除的是从operator+返回时构造的那一个
    //（即发生临时变量实质化后返回时在调用方上构造）
    //注意，这里并不与C++17规定冲突。
}
bool Test1(){
    std::cout<<"Test1 ON!"<<std::endl;
    T1 T = func1();
    std::cout<<"Result:"<<&T<<std::endl;
    std::cout<<"End!\n";
    return true;
}
bool Test2(){
    std::cout<<"Test2 ON!"<<std::endl;
    T1 T1 = func2();
    std::cout<<"Result:"<<&T1<<std::endl;
    std::cout<<"End!\n";
    return true;
}
bool Test3(){
    std::cout<<"Test3 ON!"<<std::endl;
    T1 T2 = T1((T1 &&)T1(T1()));                                    //这里问题同F2一样。
    std::cout<<"Result:"<<&T2<<std::endl;
    std::cout<<"End!\n";
    return true;
}
T1 func3(){
    return T1();
}
bool Test4(){
    std::cout<<"Test3 ON!"<<std::endl;
    T1 T3 = T1(T1(T1()));                                           //多层的相同的构造嵌套，不发生多次构造，直接进行复制消除。
    T1 T4 = func3();
    std::cout<<"Result:"<<&T3<<","<<&T4<<std::endl;                 //原理同上，返回并使用右值不发生临时变量实质化。
    std::cout<<"End!\n";
    return true;
}
void exception()try{
    std::cout<<"Exception ON!"<<std::endl;
    try{
        T1 T;
        std::cout<<&T<<std::endl;                                   //情况一，throw了一个不超过最内层try的对象，可能发生复制消除
        throw  T;
    }catch(T1 T) {                                                  //catch了一个与throw相同类型的对象，此时可以省略复制，和以引用捕捉一样
        std::cout << &T << std::endl;
    }
    try{
        T1 T;
        std::cout<<&T<<std::endl;
        throw  T;                                                   //同情况一
    }catch(T1 T){
        std::cout<<&T<<std::endl;
        throw;                                                      //违反规定，catch中存在改变了catch子句参数的可观察的表现，所以这个catch必定不会发生复制消除
    }
}catch(T1 T){
    std::cout<<&T<<std::endl;
    std::cout<<"End!\n";
}
bool _main_copy_elision(){
    exception();
    return Test1()&&Test2()&&Test3()&&Test4();
}
NS_END