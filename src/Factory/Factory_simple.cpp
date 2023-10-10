#include <iostream>
#include <memory>
using namespace std;

// 1、抽象产品类
class Shape {
public:
    virtual ~Shape(){cout<<"Destruct Class Shape"<<endl;}
    virtual void draw()=0;
};

// 2、实体产品类
class Circle : public Shape {
public:
    void draw() override{
        cout<<"draw a Circle"<<endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override{
        cout<<"draw a Rectangle"<<endl;
    }
};

// 3、工厂类，提供接口：生成不同实体类对象
class ShapeFactory {
public:
    std::shared_ptr<Shape> getShape(const std::string& shapeType);
};

std::shared_ptr<Shape> ShapeFactory::getShape(const std::string& shapeType)
{
    if(shapeType=="Circle")
    {
        return std::make_shared<Circle>();
    }
    else if(shapeType=="Rectangle")
    {
        return std::make_shared<Rectangle>();
    }
    return nullptr;
}

// 使用该工厂，通过传递类型信息来获取实体类的对象
int main()
{
    ShapeFactory factory;
    auto shape1 = factory.getShape("Circle");
    shape1->draw();
    auto shape2 = factory.getShape("Rectangle");
    shape2->draw();
    return 0;
}
