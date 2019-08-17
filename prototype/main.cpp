#include<iostream>
#include<memory>
#include<vector>
using namespace std;

class Cloneable{
public:
	virtual shared_ptr<Cloneable> clone()=0;
};

class Sheep: public Cloneable{
public:
	Sheep(){
		 age=10;
		 legs=shared_ptr<vector<int>>(new vector<int>(4));
		 (*legs)[0]=0;
		 (*legs)[1]=1;
		 (*legs)[2]=2;
		 (*legs)[3]=3;
	}
	
	void setLeg(int i,int l){
		(*legs)[i]=l;
	}
	
	int getLeg(int i){
		return (*legs)[i];
	}

	void setAge(int age_){
		age=age_;
	}
	
	int getAge(){
		return age;
	}

	void show(){
		cout<<"************"<<endl;
		cout<<age<<endl;
		cout<<(*legs)[0]<<endl;
		cout<<(*legs)[1]<<endl;
		cout<<(*legs)[2]<<endl;
		cout<<(*legs)[3]<<endl;
		cout<<"************"<<endl;
	}
//		实现深拷贝
	virtual shared_ptr<Cloneable> clone(){
		shared_ptr<Sheep> clonedSheep(new Sheep());
		clonedSheep->setLeg(0,(*legs)[0]);
		clonedSheep->setLeg(1,(*legs)[1]);
		clonedSheep->setLeg(2,(*legs)[2]);
		clonedSheep->setLeg(3,(*legs)[3]);
		clonedSheep->setAge(age);
		return clonedSheep;
	}
private:
	int age;
	shared_ptr<vector<int>> legs;
};



int main(){
	Sheep s0;
/*	cout<<s0.getAge()<<endl;
	cout<<s0.getLeg(0)<<endl;
	cout<<s0.getLeg(1)<<endl;
	cout<<s0.getLeg(2)<<endl;
	cout<<s0.getLeg(3)<<endl;*/
	
	s0.show();

	Sheep s1;
	s1=s0;

	s1.show();
	
	s0.setLeg(0,5);

	s0.show();
	s1.show();

	shared_ptr<Sheep> ps2 = dynamic_pointer_cast<Sheep>(s0.clone());

	ps2->show();

	s0.setLeg(1,10);

	s0.show();
	s1.show();
	ps2->show();

/*	cout<<s1.getAge()<<endl;
	cout<<s1.getLeg(0)<<endl;
	cout<<s1.getLeg(1)<<endl;
	cout<<s1.getLeg(2)<<endl;
	cout<<s1.getLeg(3)<<endl;*/

	return 0;
}





