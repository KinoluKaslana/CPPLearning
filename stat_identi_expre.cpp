//
// Created by KinoluKaslana  on 18-8-31.
//
//文字总结:https://www.jianshu.com/p/e1f071f2507c
#include <iostream>
static bool test_bool() {
    return true;
}
bool main_statement() {
    //一个语句可以是:
    [[]] int foo1,foo2;                         //声明语句
    [[]] foo1 = foo2 = 2;                       //表达式语句
                                                // 此处为了介绍，语句的基本格式实际上是attr(可选)所需求语句
                                                //即，在语句前可以指定一个属性序列，对这条语句进行修饰
    [[]]flag:int foo3 = 1;
                                                //或是在switch中的
                                                //case constexpr： ...
                                                //default: ...
                                                //以上是标号，任何语句都可以有一个标号
                                                ////注意标号和属性，如果属性出现在标号前，则这个属性应用到的是这个标号
                                                //出现在标号后表明这个属性应用到语句
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
    if(int a = 2;a == foo1 == foo2);
    else
        std::cout<<"Print!"<<std::endl;
    if (int foo32 = 1;test_bool());
    if constexpr (1);
                                                //选择语句
                                                //在C++17之后出现了可选带初始化语句的if语句和constexpr if
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
                                                //以下包含了：
    int a[10][10];
    for(int i = 0;i<1;++i) {                    //迭代语句&&复合语句块
        break;                                  //跳转语句
        for (int j = 0; j < 1; ++j)
            a[i][j];
    }
    for(int (&it)[10]:a)                        //C++11的范围for迭代语句
        for(int &it1:it) {                      //复合语句块
            it1;
            continue;                           //跳转语句
        }
    try {                                       //try块
        while (1) {
            static int jd = 1;
            if (jd == 2)
                throw jd;
            ++jd;
        }
    }
    catch (int ct) {
        std::cout<<"Catch!"<<ct<<std::endl;
        goto ret;                               //跳转语句
    }
    ret:return true;                            //标签+跳转语句
}


//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//标识符在声明中
enum E1{EM1,EM2};
struct C1{int member;};
namespace N1{}
template<class ... _Tys>
struct TC1{TC1(_Tys ... _args) = default;};
static void func1(){}
int a,_a,_87,中文;                               //以_，英文字母，通用转移序列\uxxxx开头的都可以
                                                //对于一个声明的规则如下:
                                                //以下划线+大写字母，+下划线，或在全局范围内的标识符，都是被保留的
                                                //标识符可以命名，名称空间，枚举，枚举项，类，类成员，变量，模板，模板特化，参数包
bool main_identifier() {
    sg:                                         //goto标签等其他实体
                                                //对关键字进行#define or #undef 行为未定义
    int esp = 4;
//标识符在表达式中
    a;_a;_87;中文;
    EM1;EM2;
    func1;                                       //标识符命名了枚举项，变量，函数，则这个标识符就是表达式
                                                //并且，当当前表达式（表达式可以嵌套）单独为当前标识符时，这个表达式代表的是标识符命名的实体
    [=](){esp;};                                //esp在其生存期外被lambda闭包对象捕获，此时，这个esp单独这个表达式的类型实际上时一个
                                                //出现在其出现的最内存的lambda闭包对象的成员访问表达式的类型
    //无限定标识符，有限定标识符，名字，请看本人简书，绪论。
    return true;
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

template<class ...T>
auto fun(T ... args)->int {return (...+args);};     //初等表达式之一，折叠表达式
bool main_expression() {
    C1 Ca,*Cb = new C1();
    int C1::*p_member = &C1::member;
    //表达式的概念，在本人简书内有叙述，此处不再做陈述。
    //初等表达式：                                    //初等表达式存在在表达式嵌套中，作为表达式求值的基本单位
    int j;
    1;                                              //字面量
    j;                                              //对一个实体命名的名字
    [](){};                                         //lanbda表达式
    fun(1,2,3,4,5,6);                               //使用了折叠表达式返回，这里的折叠表达式是初定表达式
    (1+2+3);                                        //括号内的表达式，整个括号当作一个初等表达式
                                                    //解释：为什么括号优先计算
                                                    //因为一个表达式通常都是由运算数和运算符组成
                                                    //表达式可以是一堆初等表达式嵌套，之后顺序执行，所以，我们需要知道每个初等表达式的值即可
                                                    //因此，括号内的值回在所结合的运算符进行表达式求值之前被求值
    //不求值表达式：
    sizeof(std::cout<<1);
    decltype(std::cout<<2);
    typeid(j += 4);
    //以及noexpect和求包大小的sizeof
                                                    //不求值表达式的意义就在于，在编译期获得一个数据，并不在运行时对运算数求值，以上的表达式都是运算符
                                                    //特例，typeid在存对存在多态的对行求类型时，回求动态类型，此时会对表达式求值
    //弃值表达式
    //概念，弃值表达式实际上就是表明，当前表达式的值不被运算符所需要而被丢弃
    j;                                              //一个大的表达式，单独由一个标识符的
    Ca.member;
    Cb->member;
    Ca.*p_member;
    Cb->*p_member;                                  //对于这一类的成员访问表达式
    j == 2?1:2;                                     //条件表达式
    1,2,3,4;                                        //逗号表达式
    //表达式语句                                      //表达式语句，即所有以;结尾的表达式，是C++顺序执行的程序片段
    //常量表达式，在简书中描述这里不再赘述。
    return true;
}
bool main_statement_identifier_expression() {
    return main_statement() && main_identifier() && main_expression();
}