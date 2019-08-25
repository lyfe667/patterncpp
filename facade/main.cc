#include<iostream>
#include<memory>
using namespace std;

class Accessory{
public:
	virtual void start()=0;
	virtual void shutdown()=0;
};

class CPU: public Accessory{
public:
	virtual void start() override{
		cout<<"CPU is starting..."<<endl;
	}
	virtual void shutdown() override{
		cout<<"CPU is shutdown..."<<endl;
	}
};

class Memory: public Accessory{
public:
	virtual void start() override{
		cout<<"Memory is starting..."<<endl;
	}
	virtual void shutdown() override{
		cout<<"Memory is shutdown..."<<endl;
	}
};

class HardDisk: public Accessory{
public:
	virtual void start() override{
		cout<<"HardDisk is starting..."<<endl;
	}
	virtual void shutdown() override{
		cout<<"HardDisk is shutdown..."<<endl;
	}
};
//向用户提供可以隐藏系统复杂性的接口
class Computer{
private:
	shared_ptr<Accessory> cpu_;
	shared_ptr<Accessory> memory_;
	shared_ptr<Accessory> hard_disk_;
public:
	Computer(const shared_ptr<Accessory> &cpu, const shared_ptr<Accessory> &memory,
			const shared_ptr<Accessory> &hard_disk)
		:cpu_(cpu),memory_(memory),hard_disk_(hard_disk)
	{
	}
	void start(){
		cpu_->start();
		memory_->start();
		hard_disk_->start();
		cout<<"computer started."<<endl;
	}
	void shutdown(){
		cpu_->shutdown();
		memory_->shutdown();
		hard_disk_->shutdown();
		cout<<"computer shutdown"<<endl;
	}
};


int main(){
	Computer pc(make_shared<CPU>(), make_shared<Memory>(), make_shared<HardDisk>());
	pc.start();
	pc.shutdown();
	return 0;
}












