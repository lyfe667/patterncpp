#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
using namespace std;

class INode{
public:
	INode(int id)
		:id_(id)
	{
	}

	void setId(int id){
		id_=id;
	}
	
	int getId() const {
		return id_;
	}

	void addChild(shared_ptr<INode> &node){
		childs_.push_back(node);
	}

	// Lambda表达式(匿名函数)的写法：[捕获列表](参数列表)-> 返回类型{函数体}
	void removeChild(int id){
		remove_if(childs_.begin(), childs_.end(), 
				[id](const shared_ptr<INode> &node)->bool{ return node->getId()==id; });
	}

	virtual void operate()=0;
protected:
	int id_;
	vector<shared_ptr<INode>> childs_;
};

class Node:public INode{
public:
	Node(int id)
		:INode(id)
	{
	
	}
	//只有operate需要我们重写
	virtual void operate() override {
		cout<<id_<<" ";
		for(shared_ptr<INode> &node: childs_){
			node->operate();
		}
	}
private:
};

int main(){
	vector<shared_ptr<INode>> nodes(10);

	for(int i=0;i<10;i++){
		nodes[i]=make_shared<Node>(i);
	}

	/*for(int i=0;i<10;i++){
		nodes[i]->operate();
	}*/

	nodes[0]->addChild(nodes[1]);
	nodes[0]->addChild(nodes[2]);
	nodes[1]->addChild(nodes[3]);
	nodes[1]->addChild(nodes[4]);
	nodes[2]->addChild(nodes[5]);
	nodes[2]->addChild(nodes[6]);
	nodes[3]->addChild(nodes[7]);
	nodes[3]->addChild(nodes[8]);
	nodes[4]->addChild(nodes[9]);

	nodes[0]->operate();
	cout<<endl;
	nodes[1]->operate();
	cout<<endl;
	nodes[2]->operate();
	cout<<endl;

	return 0;
}
















