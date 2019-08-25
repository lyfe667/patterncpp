#include<iostream>
#include<memory>
using namespace std;

int main(){
	int *p=new int(10);
	shared_ptr<int> ps0(p);
	{
		shared_ptr<int> ps1(p);
		cout<<ps1.use_count()<<endl;
		cout<<*ps1<<endl;
	}
//	shared_ptr<int> ps2(p);
	cout<<ps0.use_count()<<endl;
//	cout<<ps2.use_count()<<endl;
	cout<<*ps0<<endl;
//	cout<<*ps2<<endl;
	return 0;
}
