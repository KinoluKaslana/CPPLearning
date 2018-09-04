//
// Created by KinoluKaslana on 18-9-3.
//

#include <iostream>
#include "AllCore.h"
//Aggergates:
NS_AGGREATE_POD
namespace _in_std03 {
    class Aggergates_class {
    private:
        void func3() {}                      //OK各种位置的成员函数
        static int foo1;                    //OKprivate的静态成员
    protected:
        static int foo2;                    //OKprotected的静态成员
        void func1() {}

    public:
        Aggergates_class &operator=(Aggergates_class &src) //OK用户定义的copy-assignment operator
        {
            foo3 = src.foo3;
            foo4 = src.foo4;
            return *this;
        }

        ~Aggergates_class() {}                               //OK用户定义的析构函数

        void func2() {}

        int foo3 = 2;                                       //非静态的类成员为public
        int foo4;
    };

    int Aggergates_class::foo1 = 5;
    int Aggergates_class::foo2 = 5;

    class Bad_base {
        virtual void fun1() {}
    };

    class Non_Aggergates_class : Bad_base                     //继承
    {
    private:
        int foo1;                                           //非public的非静态数据成员
    public:
        int foo2;

        Non_Aggergates_class(int) {
            std::cout << "Call Constructor" << std::endl;
        }                         //用户定义的构造函数
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

    //ToDo:PODs 的性质：生命周期不随构造函数，对于memcpy等强拷贝感冒，如果一个PODs的成员第一个是另一个PODs那么可以直接通过编译器类型指定的类型转换把它转为其成员类类型的指针，直接调用
    //goto跳过PODs时不会有error，但是non-PODs就会抛error
    struct PODs {
        int foo1;

    };
}
NS_END

