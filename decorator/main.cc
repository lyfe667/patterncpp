#include<iostream>
#include<memory>
using namespace std;

class IShape{
public:
	virtual void draw()=0;
};
//decorated class
class Circle:public IShape{
public:
	virtual void draw() override{
		cout<<"drawing circle..."<<endl;
	}
};

class Rectangle: public IShape{
public:
	virtual void draw() override{
		cout<<"drawing rectangle..."<<endl;
	}
};

//abstract decorator
class ShapeDecorator: public IShape{
public:
	//ShapeDecorator() = default;
	ShapeDecorator(const shared_ptr<IShape> &shape)
		:shape_(shape)
	{
	
	}
protected:
	shared_ptr<IShape> shape_;
};

//concrete decorator
class RedShapeDecorator: public ShapeDecorator{
public:
	RedShapeDecorator(const shared_ptr<IShape> &shape)
		:ShapeDecorator(shape)
	{
	}
	virtual void draw() override{
		cout<<"set color to red"<<endl;
		shape_->draw();
	}
};

class BlueShapeDecorator: public ShapeDecorator{
public:
	BlueShapeDecorator(const shared_ptr<IShape> &shape)
		:ShapeDecorator(shape)
	{
	}
	virtual void draw() override{
		cout<<"set color to blue"<<endl;
		shape_->draw();
	}
}; 

int main(){
	shared_ptr<IShape> circle=make_shared<Circle>();
	circle->draw();
	shared_ptr<IShape> rect=make_shared<Rectangle>();
	rect->draw();
	
	shared_ptr<IShape> sd=make_shared<RedShapeDecorator>(circle);
	sd->draw();

	sd=make_shared<BlueShapeDecorator>(rect);
	sd->draw();

	return 0;
}






