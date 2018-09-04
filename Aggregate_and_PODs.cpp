//
// Created by KinoluKaslana on 18-9-3.
//

#include <iostream>
#include <cstdlib>
#include <memory.h>
#include "AllCore.h"
//Aggergates:
NS_AGGREATE_POD
namespace _in_std03 {
    class Aggergates_class {
    private:
        void func3() {}                                     //OK各种位置的成员函数
        static int foo1;                                    //OKprivate的静态成员
    protected:
        static int foo2;                                    //OKprotected的静态成员
        void func1() {}

    public:
        Aggergates_class &operator=(Aggergates_class &src){ //OK用户定义的copy-assignment operator

            foo3 = src.foo3;
            foo4 = src.foo4;
            return *this;
        }

        ~Aggergates_class() {}                              //OK用户定义的析构函数

        void func2() {}

        int foo3 = 2;                                       //非静态的类成员为public
        int foo4;
    };

    int Aggergates_class::foo1 = 5;
    int Aggergates_class::foo2 = 5;

    class Bad_base {
        virtual void fun1() {}
    };

    class Non_Aggergates_class : Bad_base{                  //继承
    private:
        int foo1;                                           //非public的非静态数据成员
    public:
        int foo2;

        Non_Aggergates_class(int) {
            std::cout << "Call Constructor" << std::endl;   //用户定义的构造函数
        }
        Non_Aggergates_class(Non_Aggergates_class &src) {
            foo1 = src.foo1;
            foo2 = src.foo2;
            std::cout << "Call copy constructor" << std::endl;
        }

        Non_Aggergates_class &operator=(Non_Aggergates_class &src) {
            std::cout << "Call copy-assignment operator" << std::endl;
            Non_Aggergates_class(std::forward<Non_Aggergates_class &>(src));
            return *this;
        }

        void fun1() override final {}                        //虚函数
    };

    struct Bad_Kind {
        Bad_Kind(int) {}
    };

    struct Nature1 {
        Aggergates_class T1;
        int foo;
    };
    struct Nature2 {
        Bad_Kind T1;
        int foo;
    };

    class Bad_Test {
    private:
        Bad_Test() = default;

    public:
        int foo;
        int &fdo;
    };

    bool in_std03() {
        int i = 4;
        Aggergates_class gd1 = {1, 2};          //并不调用构造函数
        Aggergates_class gd2 = {1};             //第二个数据成员被默认初始化成功
        Aggergates_class gd3 = {};              //区别，一个使用的是标量默认初始化
        Aggergates_class gd4;                   //一个使用默认构造函数
        //Non_Aggergates_class bd = {1,3};
        int Array1[3] = {1, 2, 3};              //OK话括号内元素和数组大小等价
        int Array2[3] = {1};                    //OK小于数组大小，自动对为指定初始化值的成员自动初始化
        int Array3[3] = {};                     //OK同上
        int Array4[] = {1, 2, 3};               //OK推断为同大小的
        int Array5[3];                          //没有初始化，值通常为未知（特定状况，如所处位置，编译器等）
        Aggergates_class gArray1[3] = {{1},
                                       {2, 3},
                                       {}};
        std::cout << gArray1[0].foo3 << std::endl << gArray1[1].foo4 << std::endl << gArray1[2].foo3 << std::endl;
        /*
         * 不同于Aggergates_class gArray1[3] = {1,2,3};
         * 的初始化结果
         */
        Aggergates_class gArray2[3] = {};
        std::cout << "Bad Aggergates Call List:" << std::endl;
        Non_Aggergates_class bArray1[3] = {{1},
                                           {2},
                                           {3}};            //调用构造函数完成，步骤见运行输出
        //Non_Aggergates_class bArray2[3] = {{1,2},{},{3}}; //没有正确使用构造函数
        //Non_Aggergates_class bArray3[3] = {};             //同上
        Nature1 T1{1, 2, 3};                                //为聚合体，可以直接初始化，并且不经过构造
        Nature1 T2{1, 2};                                   //同上
        Nature1 T3{};                                       //同上
        Nature1 AT1[3]{1, 2, 3};
        Nature2 NT1{1, 2};                                  //当前类为聚合体，但是成员有不是聚合体的，需要满足相应构造要求
        //Nature2 NT2 {};                                   //存在成员无法显式的默认初始化
        Nature2 AT2[1]{Bad_Kind(1)};                        //使用构造，调用拷贝构造进行初始化
        int j = 1;
        Bad_Test A{1, j};                                   //没有提到，但是这里没有使用构造函数进行初始化
        //推论，由此可知，判断聚类之前，如果得到用户定义的构造函数，那么表明当前类需要进行特殊处理而不能按照聚合的方式初始化。
        //哪怕构造函数函数体，参数等，均为空
        return true;
    }
    struct PODs {
        int foo1;
        int foo2;
    };
    struct PODs1 {
        PODs OT;
        int foo;
    };
    bool in_std03_POD(){
        goto flags;
        PODs1 T1;                                                                           //auto生存期的POD生命期随堆栈，而不随构造与析构，注意，Aggregate没有这个性质
        flags: PODs *P_T1 = reinterpret_cast<PODs*>(std::malloc(sizeof(PODs)));
        char TEMP[sizeof(PODs1)]{};
        memcpy(&T1,TEMP, sizeof(PODs1));                                                    //PODs不对memcpy感冒，可以直接按照内存分布拷贝，不会有问题
        memcpy(P_T1,&T1,sizeof(PODs));                                                      //同上
        std::cout<< reinterpret_cast<PODs*>(&T1)->foo1 + P_T1->foo2<<std::endl;             //当PODs的第一个成员也是一个POD的时候，可以直接对其在编译器的类型进行转换，可以当作一个成员的类来使用
        /*
        goto flags1;
        Aggergates_class T2{};                                                              //不可以跳过非POD的构造调用
        flags1:T2.foo3 = 2;
        */
        return true;
    };
}
bool main_aggregate_and_pods() {
    return _in_std03::in_std03() && _in_std03::in_std03_POD();
}
NS_END

