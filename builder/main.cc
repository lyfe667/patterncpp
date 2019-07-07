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

//abstract builder
class ComputerAccessoryBuilder{
public:
	virtual shared_ptr<CPU> createCPU()=0;
	virtual shared_ptr<Memory> createMemory()=0;
};

//concrete builder
class HighConfigComputerAccessoryBuilder: public ComputerAccessoryBuilder{
public:
	shared_ptr<CPU> createCPU(){
		return shared_ptr<FastCPU>(new FastCPU());
	}
	shared_ptr<Memory> createMemory(){
		return shared_ptr<BigMemory>(new BigMemory());
	}
};

class LowConfigComputerAccessoryBuilder: public ComputerAccessoryBuilder{
public:
	shared_ptr<CPU> createCPU(){
		return shared_ptr<SlowCPU>(new SlowCPU());
	}
	shared_ptr<Memory> createMemory(){
		return shared_ptr<SmallMemory>(new SmallMemory());
	}
};
//要建造的Product
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

/*shared_ptr<Computer> assembleComputer(const shared_ptr<ComputerAccessoryBuilder> &caf){
	return shared_ptr<Computer>(new Computer(caf->createCPU(),caf->createMemory()));
}*/

//比抽象工厂模式多了一个Director，用于控制具体的创建过程。
class Director{
private:
	shared_ptr<ComputerAccessoryBuilder> cab_;
public:
	void setBuilder(const shared_ptr<ComputerAccessoryBuilder> &cab){
		cab_=cab;
	}
	shared_ptr<Computer> build(){
		return shared_ptr<Computer>(new Computer(cab_->createCPU(),cab_->createMemory()));
	}
};



int main(){
	/*shared_ptr<Computer> hcc = assembleComputer(make_shared<HighConfigComputerAccessoryBuilder>());
	shared_ptr<Computer> lcc = assembleComputer(make_shared<LowConfigComputerAccessoryBuilder>());
	hcc->showConfiguration();
	lcc->showConfiguration();*/
	Director bd;
	bd.setBuilder(make_shared<HighConfigComputerAccessoryBuilder>());
	shared_ptr<Computer> hcc=bd.build();
	bd.setBuilder(make_shared<LowConfigComputerAccessoryBuilder>());
	shared_ptr<Computer> lcc=bd.build();
	hcc->showConfiguration();
	lcc->showConfiguration();

	return 0;
}
