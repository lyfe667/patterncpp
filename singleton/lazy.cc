#include<iostream>
#include<memory>
using namespace std;

class LazySingleton{
public:
	static shared_ptr<LazySingleton> getInstance()
	{
		if(0==pls_.use_count()){
			pls_=shared_ptr<LazySingleton>(new LazySingleton());
		}
		return pls_;
	}
private:
	//只是进行了声明
	static shared_ptr<LazySingleton> pls_;
	LazySingleton(){
	
	}
};
//对static变量进行了定义
shared_ptr<LazySingleton> LazySingleton::pls_;

int main(){
	shared_ptr<LazySingleton> l0=LazySingleton::getInstance();
	shared_ptr<LazySingleton> l1=LazySingleton::getInstance();
	shared_ptr<LazySingleton> l2=LazySingleton::getInstance();
	cout<<l0.get()<<endl;
	cout<<l1.get()<<endl;
	cout<<l2.get()<<endl;
	return 0;
}
