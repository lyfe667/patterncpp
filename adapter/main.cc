#include<iostream>
#include<memory>
using namespace std;
class Power5v{
public:
	virtual int output5v(){
		return 5;
	}
};

class CellPhone{
public:
	void charge(Power5v &p5){
		cout<<"charging with "<<p5.output5v()<<"v..."<<endl;
	}	
};

class Power220v{
public:
	virtual int output220v(){
		return 220;
	}
};

class PowerAdapter: public Power5v,private Power220v{
public:
	virtual int output5v() override{
		cout<<"converting "<<output220v()<<" v to 5v..."<<endl;
		return 5;
	}

};


int main(){
	Power5v p5;
	CellPhone cp;
	cp.charge(p5);
	
	PowerAdapter pa;
	cp.charge(pa);

	return 0;
}
