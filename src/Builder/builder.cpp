#include "builder_computer.h"

int main()
{
	// 1. 创建电脑建造者
	AbstractBuilder* Computer_Builder = new ComputerBuilder;
	
	// 2. 创建管理者 管理电脑建造者制造电脑产品
	Director* pDirector = new Director{ Computer_Builder };
	AbstractProduct* computerProduct = pDirector->createComputer("联想显示器", "外星人主机", "雷蛇键盘", "罗技鼠标");

	// 3. 电脑产品制造完成
	computerProduct->show();

	delete Computer_Builder;
	delete pDirector;
	delete computerProduct;

	return 0;
}