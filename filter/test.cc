#include<iostream>
#include<vector>
using namespace std;

int main(){
	int a[3]{1,2,3};
	cout<<a[0]<<","<<a[1]<<","<<a[2]<<endl;
	vector<int> v{1,2,3,4};
	v.insert(v.end(),5);
	for(int d:v){
		cout<<d<<" ";
	}
	cout<<endl;
	return 0;
}
