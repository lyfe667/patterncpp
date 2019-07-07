#include<iostream>
#include<memory>
using namespace std;

class CPU{
public:
	virtual void speed()=0;
};

class Memory{
public:
	virtual	void capacity()=0;	
};

class FastCPU: public CPU{
public:
	void speed(){
		cout<<"6 kernel, 4.4HZ..."<<endl;
	}
};

class SlowCPU: public CPU{
public:
	void speed(){
		cout<<"2 kernel, 2.2HZ..."<<endl;
	}
};

class BigMemory: public Memory{
public:
	void capacity(){
		cout<<"32G..."<<endl;
	}
};

class SmallMemory: public Memory{
public:
	void capacity(){
		cout<<"4G..."<<endl;
	}
};

//abstract factory
class ComputerAccessoryFactory{
public:
	virtual shared_ptr<CPU> createCPU()=0;
	virtual shared_ptr<Memory> createMemory()=0;
};

//factory
class HighConfigComputerAccessoryFactory: public ComputerAccessoryFactory{
public:
	shared_ptr<CPU> createCPU(){
		return shared_ptr<FastCPU>(new FastCPU());
	}
	shared_ptr<Memory> createMemory(){
		return shared_ptr<BigMemory>(new BigMemory());
	}
};

class LowConfigComputerAccessoryFactory: public ComputerAccessoryFactory{
public:
	shared_ptr<CPU> createCPU(){
		return shared_ptr<SlowCPU>(new SlowCPU());
	}
	shared_ptr<Memory> createMemory(){
		return shared_ptr<SmallMemory>(new SmallMemory());
	}
};

class Computer{
private:
	shared_ptr<CPU> cpu_;
	shared_ptr<Memory> memory_;

public:
	Computer(shared_ptr<CPU> cpu,shared_ptr<Memory> memory)
		:cpu_(cpu),memory_(memory)
	{

	}

	~Computer(){
	}
public:
	void showConfiguration(){
		cpu_->speed();
		memory_->capacity();
	}

};

shared_ptr<Computer> assembleComputer(const shared_ptr<ComputerAccessoryFactory> &caf){
	return shared_ptr<Computer>(new Computer(caf->createCPU(),caf->createMemory()));
}


int main(){
	LowConfigComputerAccessoryFactory lccaf;
	shared_ptr<Computer> hcc = assembleComputer(make_shared<HighConfigComputerAccessoryFactory>());
	shared_ptr<Computer> lcc = assembleComputer(make_shared<LowConfigComputerAccessoryFactory>());
	hcc->showConfiguration();
	lcc->showConfiguration();
	
	return 0;
}
