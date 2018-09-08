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
        IS_Aggregate &&operator==(IS_Aggregate &&src){      //OK，因为允许用户定义=运算符重载
            return (IS_Aggregate&&)*this;
        }
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
    //trivial copyable是trivial的超集，其中的特性就不在这里补充了，详情见博客。
    struct Base_Trivial1{//Base_Trivial1(){}
    };                                                      //空类是允许的,如果存在构造函数时此时该类不是trivial的但是却是trivial copyable的
    struct IS_Trivial : Base_Trivial1{
    private:
        IS_Trivial() = default;                             //存在非用户定义的构造函数
        int foo1;                                           //可以有非public的非静态数据成员
    public:
        static int sfoo1;                                   //静态成员的规定依然存在
        //IS_Trivial(int arg1,int arg2):Base_Trivial1(),foo1(arg1),foo2(arg2){}    //在存在trivial构造函数的时候可以允许存在其他的构造函数
        int foo2;
        Base_Trivial1 foo3;                                 //类型成员也是一个trivial
        ~IS_Trivial() = default;                            //虚函数为trivial
        void func1();                                       //非虚函数即可
    };
    struct Important_example{
        Important_example();
    };
    Important_example::Important_example() = default;         //这个类是非trivial的，因为在第一次声明时就需要判断构造函数等是否是user-provide的
    struct Base1_trivial{
        int foo1;
        Base1_trivial() = default;
        Base1_trivial(int a):foo1(a){}
    };
    struct Base2_trivial{
        int foo2;
        ~Base2_trivial() = default;
    };
    struct mul_inher:Base1_trivial,Base2_trivial{
        Base1_trivial foo3;
        Base2_trivial foo4;
    };
    bool in_std_11_trivial() {
        std::cout<<"Begain Shows C++11 Trivial:\nTesting : IS_Trivial\nUsing is_pod:"<<(std::is_pod<IS_Trivial>::value?"true\n":"false\n")<<"Using is_trivially_copyable:"<<(std::is_trivially_copyable<IS_Trivial>::value?"true\n":"false\n")<<
        "Using is_trivial:"<<(std::is_trivial<IS_Trivial>::value?"true\n":"false\n")<<std::endl<<
        "Testing : Important_example\t"<<(std::is_trivial<Important_example>::value?"true":"false")<<std::endl<<
        "Testing : mul_inher\t"<<(std::is_trivial<mul_inher>::value?"true":"false")<<std::endl;
        return true;
    }
    //对于standard layout的限制明显少了很多，具体特性见博客。
    struct Base_STD_Layout{};
    struct Base_STD_Layout1:Base_STD_Layout{};
    struct STD_Layout:Base_STD_Layout1{                         //在继承树中只能有一个类有非静态且不为非standard layout的成员
    private:
        int foo1,foo2,foo3 = 4;                                 //只要所有成员的访问限制统一即可
        Base_STD_Layout foo4;                                   //可以拥有之前基类类型的数据成员
        Base_STD_Layout1 foo5;
    public:
        STD_Layout(){}                                          //没有过多的对默认构造函数，移动，拷贝构造，移动，拷贝赋值运算符，析构函数做限制
        STD_Layout(int a,int b,int c):foo1(a),foo2(b),foo3(c){}
        STD_Layout(STD_Layout &src){}
        STD_Layout(STD_Layout &&src){}
        STD_Layout &operator=(STD_Layout &src){return *this;}
        STD_Layout &&operator =(STD_Layout &&src){return (STD_Layout&&)*this;}
        ~STD_Layout(){}
    };
    struct Base_STD_Layout2{};
    struct T_1:Base_STD_Layout,Base_STD_Layout2{
        int foo1;                                               //可以继承，多继承
        STD_Layout foo2;                                        //可以含有基类类型数据成员
    };
    struct T_2:T_1{
        int fod;                                                //继承树中，只允许一个类有非静态数据成员
    };
    struct T_T{
        Base_STD_Layout foo3[2];
    };
    struct T_3:Base_STD_Layout,Base_STD_Layout2{
        T_T _tD;                                                //基类不允许成为第一个非静态数据成员，对于其他std layout型成员也是递执行的，即不可以以基类类型的非静态数组、成员。
        Base_STD_Layout foo1[2];
        Base_STD_Layout2 foo2;
    };
    struct T_4:T_1,Base_STD_Layout {};
    bool in_std_11_STD_Layout() {
        std::cout<<"Begain Shows C++11 Standard Layout:\nTesting : STD_Layout\t"<<(std::is_standard_layout<STD_Layout>::value?"true":"false")<<std::endl<<
        "Testing : T_1:"<<(std::is_standard_layout<T_1>::value?"true":"false")<<std::endl<<"Testing : T_1:"<<(std::is_standard_layout<T_1>::value?"true":"false")<<std::endl<<
        "Testing : T_2:"<<(std::is_standard_layout<T_2>::value?"true":"false")<<std::endl<<"Testing : T_3:"<<(std::is_standard_layout<T_3>::value?"true":"false")<<std::endl<<
        "Testing : T_4:"<<(std::is_standard_layout<T_4>::value?"true":"false")<<std::endl;
        return true;
    }
}
namespace _in_std14 {       //C++14总体变化不大，对于PODs，以及trivial和 standard layout都没有变化
    struct Only_Change{
        int i = 123;
    };
    bool is_std_14_all(){
        std::cout<<"Begain Test All:\nTesting Aggregate : "<<(std::is_aggregate<Only_Change>::value?"true\n":"false\n")<<"Testing PODs:"<<(std::is_pod<Only_Change>::value?"true\n":"false\n")<<
        "Testing trivial cpoyable:"<<(std::is_trivially_copyable<Only_Change>::value?"true\n":"false\n")<<"Testing trivial:"<<(std::is_trivial<Only_Change>::value?"true\n":"false\n")<<"Testing standard layout:"<<(std::is_standard_layout<Only_Change>::value?"true":"false")<<std::endl;
        return true;
    }

}
namespace _in_std17{
    //std17新增以下规定：
    //(std::is_aggregate)是C++17的标准，用于验证C++17标准的aggregate，之前的arregate均没有使用到以下限制内容，所以可以。
    class BadBase1{
        explicit BadBase1():foo1(0){}        //用户定义的构造函数（各种）是不可以有的，可以有各种运算符重载和析构函数；其中explicit的构造函数也是不可以有的
        int foo1;
        virtual void func() const{}
    };
    class BadBase2:BadBase1{                 //不可以使用虚，protected，private继承。
        using BadBase1::BadBase1;            //不可以使用继承构造函数
        int foo2;
        void func()const final override{}
    };
    class Base1{
        std::vector<BadBase1> foo1;
    };
    struct IS_aggregate:public BadBase2,public Base1{           //合理的多继承是允许的
        BadBase2 foo1;                                          //OK采用非aggregate的类，数组，使用列表初始化进行其成员初始化。
        Base1 foo2;
        IS_aggregate &operator=(IS_aggregate &src){
            return *this;
        }

        char str[10];                                             //明文规定，数组是按照数组递增顺序为内存排列的。

        ~IS_aggregate(){
            std::cout<<"Endl\n";
        }
    };
    bool _in_std17()
    {
        std::cout<<"Begain Shows C++11 Aggregates!\nTesting IS_aggregate:"<<(std::is_aggregate<IS_aggregate>::value?"true":"false")<<std::endl;
        return true;
    }
}
bool main_aggregate_and_pods() {
    return _in_std03::in_std03() && _in_std03::in_std03_POD()&&_in_std11::_is_std11()&&_in_std11::in_std_11_trivial()&& _in_std11::in_std_11_STD_Layout()&&_in_std14::is_std_14_all()
    && _in_std17::_in_std17();
}
NS_END