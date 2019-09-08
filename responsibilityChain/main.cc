#include<iostream>
#include<string>
#include<memory>

using namespace std;

class Approver{
protected:
	string name_;
	shared_ptr<Approver> next_;
public:
	Approver(const string & name)
		:name_(name)
	{

	}
	void setNext(const shared_ptr<Approver> & next){
		next_=next;
	}
	virtual bool approve() =0;
};

class PL: public Approver{
public:
	PL(const string &name)
		:Approver(name)
	{

	}
	virtual bool approve() override{
		cout<<"PL: "<<name_<<" agree?";
		string s;
		cin>>s;
		if("y"==s || "Y"==s){
			cout<<"PL: "<<name_<<" agree"<<endl;
			if(next_){
				return next_->approve();
			}else{
				return true;
			}
		}else{
			cout<<"PL: "<<name_<<" not agree"<<endl;
			return false;
		}
	}
};

class GL: public Approver{
public:
	GL(const string &name)
		:Approver(name)
	{
	
	}

	virtual bool approve() override{
		cout<<"GL: "<<name_<<" agree?";
		string s;
		cin>>s;
		if("y"==s || "Y"==s){
			cout<<"GL: "<<name_<<" agree"<<endl;
			if(next_){
				return next_->approve();
			}else{
				return true;
			}
		}else{
			cout<<"GL: "<<name_<<" not agree"<<endl;
			return false;
		}
	}
};

int main(){
	shared_ptr<GL> gl0=make_shared<GL>("gl0");
	shared_ptr<GL> gl1=make_shared<GL>("gl1");
	shared_ptr<PL> pl0=make_shared<PL>("pl0");
	shared_ptr<PL> pl1=make_shared<PL>("pl1");

	gl0->setNext(gl1);
	gl1->setNext(pl0);
	pl0->setNext(pl1);

	if(gl0->approve()){
		cout<<"Application is agreed."<<endl;
	}else{
		cout<<"Application is not agreed."<<endl;
	}


	return 0;
}
