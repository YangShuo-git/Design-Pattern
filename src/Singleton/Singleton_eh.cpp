#include <iostream>
using namespace std;

/*
 * Singleton
 * 饿汉模式：是指单例程序在运行时，被立即执行初始化
 * 问题：静态成员的初始化顺序是无法保障（假如两个单例，其中一个是另一个的成员，成员单例初始化发生在外部单例初始化工作之后，程序就会崩溃）
 */
class Singleton {
public:
    static Singleton* getInstance()   //饿汉模式，单例运行时已经初始化了m_data 每次返回m_data的引用
    {
        return m_data;
    }

private:
    Singleton(){cout<<"Construct Class Singleton!!!"<<endl;}  //构造函数私有化
    ~Singleton(){}

    static Singleton* m_data;   //静态成员，类内声明
};

Singleton* Singleton::m_data;  //类外定义


int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    std::cout << "p1: " << hex << p1 << std::endl; 
    std::cout << "p2: " << hex << p2 << std::endl; 
}