#include<iostream>
#include<memory>
using namespace std;

//implementor
class IOS{
public:
	virtual void run()=0;
	
	~IOS(){
		cout<<"IOS destructor"<<endl;
	}
};

//concret implementor
class Ubuntu:public IOS{
public:
	virtual void run() override{
		cout<<"Ubuntu is running..."<<endl;
	}
};

class Win10:public IOS{
public:
	virtual void run() override{
		cout<<"Win10 is running..."<<endl;
	}
};

//Bridge abstraction
class Computer{
public:
	Computer(const shared_ptr<IOS> &os)
		:os_(os)
	{
	
	}
	
	virtual void start()=0;
	
	void reinstallOS(const shared_ptr<IOS> &os){
		os_=os;
	}
	
	~Computer(){
		cout<<"Computer destructor"<<endl;
	}

protected:
	shared_ptr<IOS> os_;
};
//Concret bridge
class Laptop: public Computer{
public:
	Laptop(const shared_ptr<IOS> &os)
		:Computer(os)
	{
	
	}
	virtual void start() override{
		cout<<"Laptop is starting..."<<endl;
		os_->run();
	}
};

class Desktop: public Computer{
public:
	Desktop(const shared_ptr<IOS> &os)
		:Computer(os)
	{
	
	}
	virtual void start() override{
		cout<<"Desktop is starting"<<endl;
		os_->run();
	};
};


int main(){
	//构造一个装Ubuntu的Laptop
	shared_ptr<Computer> pc=make_shared<Laptop>(make_shared<Ubuntu>());
	pc->start();
	//安装win10系统
	pc->reinstallOS(make_shared<Win10>());
	pc->start();
	//构造一个装Ubuntu的Desktop
	pc=make_shared<Desktop>(make_shared<Ubuntu>());
	pc->start();
	//安装win10系统
	pc->reinstallOS(make_shared<Win10>());
	pc->start();
	return 0;
}
