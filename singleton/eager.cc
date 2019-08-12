#include<iostream>
#include<memory>
using namespace std;

class EagerSingleton{
public:
	static EagerSingleton * getInstance()
	{
		static EagerSingleton as;
		return &as;
	}
private:
	//私有化构造函数
	EagerSingleton(){
	
	}
};

int main(){
	//shared_ptr<LazySingleton> l0=LazySingleton::getInstance();
	//shared_ptr<LazySingleton> l1=LazySingleton::getInstance();
	//shared_ptr<LazySingleton> l2=LazySingleton::getInstance();
	//cout<<l0.get()<<endl;
	//cout<<l1.get()<<endl;
	//cout<<l2.get()<<endl;
	EagerSingleton * pas0 = EagerSingleton::getInstance();
	EagerSingleton * pas1 = EagerSingleton::getInstance();
	EagerSingleton * pas2 = EagerSingleton::getInstance();
	cout<< pas0 <<endl;
	cout<< pas1 <<endl;
	cout<< pas2 <<endl;
	return 0; 
}
