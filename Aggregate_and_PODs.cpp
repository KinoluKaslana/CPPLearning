//
// Created by KinoluKaslana on 18-9-3.
//

#include <iostream>
#include <cstdlib>
#include <memory.h>
#include <vector>
#include <type_traits>
#include "AllCore.h"
//Aggergates:
NS_AGGREATE_POD
namespace _in_std03 {
    //一个Aggergates的完全标准描述：
    struct IS_Aggergates{
    private:
        void fun1(){}                                        //任何位置的成员函数
        static int foo1;                                     //static的数据成员可以有private访问限制
        //virtual void vfun1(){};                            //任何位置都不能有虚函数
    protected:
        void fun2(){}
        static int foo2;                                     //static数据成员可以有protected访问限制
        //virtual int vfun2(){}
    public:
        IS_Aggergates &operator=(IS_Aggergates &src)
                {return *this;}                              //有用户定义的重载=运算符
        ~IS_Aggergates(){}                                   //有用户定义的析构函数
        //virtual int vfun3(){}
        //IS_PODs(){}
        const static int foo3 = 2;                           //static数据成员
        int foo4;                                            //非static数据成员必须为public
        //int &foo5;                                         //不包含引用
        std::istream foo6;                                   //可以有任意类型的数据成员，但是如此做会引发错误，具体请见简书内容
    };
    //以下为性质展示定义的类和展示：
    class Aggergates_class {
    private:
        void func3() {}
        static int foo1;
    protected:
        static int foo2;
        void func1() {}

    public:
        Aggergates_class &operator=(Aggergates_class &src){

            foo3 = src.foo3;
            foo4 = src.foo4;
            return *this;
        }

        ~Aggergates_class() {std::cout<<"Destroctor Called!"<<std::endl;}

        void func2() {}

        int foo3;
        int foo4;
    };
    class Bad_base {
        virtual void fun1() {}
    };
    class Non_Aggergates_class : Bad_base{                   //继承
    private:
        int foo1;                                            //非public的非静态数据成员
    public:
        int foo2;

        Non_Aggergates_class(int) {
            std::cout << "Call Constructor" << std::endl;    //用户定义的构造函数
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
    bool in_std03() {
        std::cout<<"Begain Shows C++03 Aggregates!"<<std::endl;
        std::cout<<"Testing Class : IS_Aggregates\t"<<((std::is_aggregate<IS_Aggergates>::value)?"true":"false")<<std::endl<<
        "Testing Class : Aggregates_Class\t"<<((std::is_aggregate<Aggergates_class>::value)?"true":"false")<<std::endl<<
        "Testing Class : Bad_Base\t"<<((std::is_aggregate<Bad_base>::value)?"true":"faluse")<<std::endl<<
        "Testing Class : Non_Aggregates_class\t"<<((std::is_aggregate<Non_Aggergates_class>::value)?"true":"false")<<std::endl;
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
        std::cout << gArray1[0].foo4 << std::endl << gArray1[1].foo4 << std::endl << gArray1[2].foo3 << std::endl;
        /*
         * 不同于Aggergates_class gArray1[3] = {1,2,3};
         * 的初始化结果
         */
        Aggergates_class gArray2[3] = {};
        std::cout << "Bad Aggergates Call List:" << std::endl;
        Non_Aggergates_class bArray1[3] = {{1},
                                           {2},
                                           {3}};            //调用构造函数完成，步骤见运行输出
        std::cout<<"End"<<std::endl;
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

        return true;
    }
    //以下是PODs，在C++03中正确的标准说明：
    struct PODs {
        int foo1;
        int foo2;
    };
    struct IS_PODs{
    private:
        void fun1(){}                                       //任何位置的成员函数
        static int foo1;                                    //static的成员数据
        //virtual void vfun1(){};                           //任何位置都不能有虚函数
    protected:
        void fun2(){}
        static int foo2;
        //virtual int vfun2(){}
    public:
        //IS_PODs &operator=(IS_PODs &src){}                //不能有用户定义的重载=运算符
        //~IS_PODs(){}                                      //不能有用户定义的析构函数
        //virtual int vfun3(){}
        //IS_PODs(){}
        const static int foo3 = 2;                          //static成员数据
        int foo4;                                           //标量类型成员
        //int &foo5;                                        //不包含引用
        PODs foo6;                                          //不包含非PODs成员（包含结构，union，数组）
    };
    //以下是特性展示类声明和展示：
    struct PODs1 {
        PODs OT;
        int foo;
    };
    bool in_std03_POD(){
        std::cout<<"Begain Shows C++03 PODs!"<<std::endl;
        std::cout<<"Testing Class : IS_PODs\t"<<(std::is_pod<IS_PODs>::value?"true":"false")<<std::endl;
        std::cout<<"Testing Class : PODs\t"<<(std::is_pod<PODs>::value?"true":"false")<<std::endl;
        std::cout<<"Testing Class : PODs1\t"<<(std::is_pod<PODs1>::value?"true":"false")<<std::endl;
        goto flags;
        PODs1 T1;                                                                           //auto生存期的POD生命期随堆栈，而不随构造与析构，注意，Aggregate没有这个性质
        flags: PODs *P_T1 = reinterpret_cast<PODs*>(std::malloc(sizeof(PODs)));
        char TEMP[sizeof(PODs1)]{};
        memcpy(&T1,TEMP, sizeof(PODs1));                                                    //PODs不对memcpy感冒，可以直接按照内存分布拷贝，不会有问题
        memcpy(P_T1,&T1,sizeof(PODs));                                                      //同上
        std::cout<< reinterpret_cast<PODs*>(&T1)->foo1 + P_T1->foo2<<std::endl;             //当PODs的第一个成员也是一个POD的时候，可以直接对其在编译器的类型进行转换，可以当作一个成员的类来使用
                                                                                            //因为这里被保证不会向POD类前插任何数据胡
        /*
        goto flags1;
        Aggergates_class T2{};                                                              //不可以跳过非POD的构造调用
        flags1:T2.foo3 = 2;
        */
        std::free(P_T1);
        return true;
    };
}
namespace _in_std11 {
    struct IS_Aggregate{
    private:
        //int foo;
        void fun1(){}                                       //同C++03
        static int foo1;                                    //同C++03
        IS_Aggregate() = default;                           //由于是C++11新特性，特此在标准中修改描述，改为不允许出现用户定义行为的构造函数
                                                            //当前的构造函数是编译器定义行为的，即默认行为的构造函数
    protected:
        void fun2(){}
        static int foo2;                                    //同C++03
    public:
        constexpr static int foo3 = 2;                      //同C++03
        void fun3(){}
        //virtual void fun4(){}                             //同C++03
        //int foo4 = 3;                                     //增加C++11新特性，允许对非静态成员使用定义初始化赋值
        //std::vector<int> foo5{1,2,3};                     //同上
        IS_Aggregate &operator=(IS_Aggregate &src)
                {return *this;}                             //同C++03
        ~IS_Aggregate(){std::cout<<"Destroctor Called!"<<std::endl;} //同C++03
        int foo6;
        std::vector<int> foo7;                              //同C++03
    };
    struct Bad_Try{
        int foo1 = 3;
        std::vector<int> foo2{1,2,3};
        Bad_Try() = default;
    };
    bool _is_std11() {
        std::cout<<"Begain Shows C++11 Aggregates!"<<std::endl<<
        "Testing Class : IS_Aggregate\t"<<((std::is_aggregate<IS_Aggregate>::value)?"true":"false")<<std::endl;
        IS_Aggregate A{1};                                  //推论，由此可知，判断聚类之前，如果得到用户定义的构造函数，那么表明当前类需要进行特殊处理而不能按照聚合的方式初始化。
                                                            //哪怕构造函数函数体，参数等，均为空，这也是用户定义了行为的构造函数
                                                            //由当前示例可知，实际上并不调用构造函数，因为构造函数被定义为private
                                                            //但是会调用析构函数，因为允许存在非PODs类型的数据成员，那么就不敢保证其析构函数是否被用户定义行为
        //IS_Aggrtgate *P = new IS_Aggrtgate();
        return true;
    }
    //因为C++11起，对PODs进行了更加实用的，细致的划分(其主要定义上同03的相差无几)，但是却是两者
    //trivial和standard-layout的并集，即两者的特性在PODs上都要有
    struct Base_Trival1{};                                  //空类是允许的
    struct IS_Trivial : Base_Trival1{
    private:
        IS_Trivial() = default;                             //存在非用户定义的构造函数
        int foo1;                                           //可以有非public的非静态数据成员
    public:
        static int sfoo1;                                   //静态成员的规定依然存在
        IS_Trivial(int arg1,int arg2):Base_Trival1(),foo1(arg1),foo2(arg2){}    //在存在trivial构造函数的时候可以允许存在其他的构造函数
        int foo2;
        Base_Trival1 foo3;                                  //类型成员也是一个trivial
        ~IS_Trivial() = default;                            //虚函数为trivial
        void func1();                                       //非虚函数即可
    };
    struct Important_example{
        Important_example();
    };
    Important_example::Important_example() = default;         //这个类是非trivial的，因为在第一次声明时就需要判断构造函数等是否是user-provide的
    bool in_std_11_trivial() {
        std::cout<<"Testing : IS_Trivial\t"<<std::endl<<(std::is_pod<IS_Trivial>::value?"true":"false")<<std::endl;
    }
    struct Base_STD_Layout{};
    struct Base_STD_Layout1:Base_STD_Layout{};
    struct STD_Layout:Base_STD_Layout1{

    };

}
bool main_aggregate_and_pods() {
    return _in_std03::in_std03() && _in_std03::in_std03_POD()&&_in_std11::_is_std11();
}
NS_END

