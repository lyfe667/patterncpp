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

/*class PowerAdapter: public Power5v,private Power220v{
public:
	virtual int output5v() override{
		cout<<"converting "<<output220v()<<" v to 5v..."<<endl;
		return 5;
	}

};*/

class PowerAdapter: public Power5v{
public:
	virtual int output5v() override{
		if(p220_.use_count()>0){
			cout<<"converting "<<p220_->output220v()<<" v to 5v..."<<endl;
			return 5;
		}else{
			return 0;
		}
	}
	void plugPower220v(const shared_ptr<Power220v> &p220){
		p220_=p220;
	}

private:
	shared_ptr<Power220v> p220_;
};



int main(){
	//直接使用5v电源充电
	Power5v p5;
	CellPhone cp;
	cp.charge(p5);
	
	//使用电源适配器充电，但是为插入电源
	PowerAdapter pa;
	cp.charge(pa);
	//插入220v电源，并充电
	pa.plugPower220v(make_shared<Power220v>());
	cp.charge(pa);

	return 0;
}
