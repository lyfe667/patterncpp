#include<iostream>
using namespace std;

enum EShape{circle, rectangle};

class Shape{
public:
	virtual void draw()=0;
};

class Circle: public Shape{
public:
	void draw(){
		cout<<"drawing a circle..."<<endl;
	}
};

class Rectangle: public Shape{
public:
	void draw(){
		cout<<"drawing a rectangle..."<<endl;
	}
};

class ShapeFactory{
public:
	static Shape * createShape(EShape s){
		if(circle==s){
			return new Circle();
		}else if(rectangle==s){
			return new Rectangle();
		}else{
			return nullptr;
		}
	}
};


int main(){
	Shape *s0=ShapeFactory::createShape(circle);
	Shape *s1=ShapeFactory::createShape(rectangle);
	
	s0->draw();
	s1->draw();

	if(s0){
		delete s0;
	}
	if(s1){
		delete s1;
	}
	return 0;
}
