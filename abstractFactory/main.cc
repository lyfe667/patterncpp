#include<iostream>
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
	virtual CPU * createCPU()=0;
	virtual Memory * createMemory()=0;
};

//factory
class HighConfigComputerAccessoryFactory: public ComputerAccessoryFactory{
public:
	CPU * createCPU(){
		return new FastCPU();
	}
	Memory * createMemory(){
		return new BigMemory();
	}
};

class LowConfigComputerAccessoryFactory: public ComputerAccessoryFactory{
public:
	CPU * createCPU(){
		return new SlowCPU();
	}
	Memory * createMemory(){
		return new SmallMemory();
	}
};

class Computer{
private:
	CPU * cpu_;
	Memory * memory_;

public:
	Computer(CPU *cpu,Memory *memory)
		:cpu_(cpu),memory_(memory)
	{

	}

	~Computer(){
		if(cpu_){
			delete cpu_;
		}
		if(memory_){
			delete memory_;
		}
	}
public:
	void showConfiguration(){
		cpu_->speed();
		memory_->capacity();
	}

};

Computer *assembleComputer(ComputerAccessoryFactory * caf){
	return new Computer(caf->createCPU(),caf->createMemory());
}


int main(){
	HighConfigComputerAccessoryFactory hccaf;
	LowConfigComputerAccessoryFactory lccaf;
	Computer *hcc = assembleComputer(&hccaf);
	Computer *lcc = assembleComputer(&lccaf);
	hcc->showConfiguration();
	lcc->showConfiguration();
	
	if(hcc){
		delete hcc;
	}
	
	if(lcc){
		delete lcc;
	}
	return 0;
}
