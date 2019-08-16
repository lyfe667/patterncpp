#include<iostream>
#include<memory>
using namespace std;

class A{
public:
	virtual void fun(){
		cout<<"A"<<endl;
	}
};

class B:public A{
public:
 	virtual void fun(){
		cout<<"func"<<endl;
	}
};


int main(){
//	shared_ptr<A> pa=make_shared<B>();
//	pa->fun();
	A *pa=new B();
	pa->fun();
	
	return 0;
}
