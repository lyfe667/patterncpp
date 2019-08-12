#include<iostream>
#include<memory>
#include<unistd.h>
#include<pthread.h>
using namespace std;

class LazySingleton{
public:
	static shared_ptr<LazySingleton> getInstance()
	{
		if(0==pls_.use_count()){
			pthread_mutex_lock(&mutex_);
			if(0==pls_.use_count()){
				sleep(4);
				pls_=shared_ptr<LazySingleton>(new LazySingleton());
//		cout<<pls_.get()<<"\t"<<endl;
			}
			pthread_mutex_unlock(&mutex_);
		}
		return pls_;
	}
private:
	//只是进行了声明
	static pthread_mutex_t mutex_;
	static shared_ptr<LazySingleton> pls_;
	//私有化构造函数
	LazySingleton(){
	
	}
};
//对static变量进行了定义
shared_ptr<LazySingleton> LazySingleton::pls_;
pthread_mutex_t LazySingleton::mutex_=PTHREAD_MUTEX_INITIALIZER;

void *thread0(void *){
	shared_ptr<LazySingleton> ls=LazySingleton::getInstance();
	cout<<ls.get()<<"\t"<<endl;
}

int main(){
	//shared_ptr<LazySingleton> l0=LazySingleton::getInstance();
	//shared_ptr<LazySingleton> l1=LazySingleton::getInstance();
	//shared_ptr<LazySingleton> l2=LazySingleton::getInstance();
	//cout<<l0.get()<<endl;
	//cout<<l1.get()<<endl;
	//cout<<l2.get()<<endl;
	//pthread_mutex_init(&mutex,NULL);
	pthread_t tid0,tid1;
	pthread_create(&tid0,NULL,thread0,NULL);
	sleep(2);
	pthread_create(&tid1,NULL,thread0,NULL);
	pthread_join(tid0,NULL);
	pthread_join(tid1,NULL);
	//pthread_mutex_destroy(&mutex);
	return 0;
}
