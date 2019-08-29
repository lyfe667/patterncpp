#include<iostream>
#include<memory>
#include<map>
using namespace std;

class Server{
public:
	Server(const string &ip)
		:IP_(ip)
	{
	
	}

	virtual string response(const string &url)=0;

protected:
	string IP_;
};

class RealServer: public Server{
public:
	RealServer(const string &ip)
		:Server(ip)
	{
	
	}

	virtual string response(const string &url) override {
		string respStr(url);
		respStr = "response from " +IP_+":"+respStr;
		return respStr;
	}
};

class ProxyServer: public Server{
public:
	ProxyServer(const string &ip)
		:Server(ip)
	{
		
	}

	virtual string response(const string &url) override{
		map<string, shared_ptr<Server>>::iterator it=servers_.find(url);
		if(it!=servers_.end()){
			return it->second->response(url);
		}else{
			string respStr(url);
			respStr="can't response "+respStr;
			return respStr;
		}
	}

	void addURL(const string &url, const shared_ptr<Server> &server){
		servers_.insert(pair<string,shared_ptr<Server>>(url,server));
	}
	
	void removeURL(const string &url){
	 	servers_.erase(url);
	 }
private:
	map<string, shared_ptr<Server>> servers_;
};

int main(){
	const string ip0("12.36.149.99");
	const string ip1("10.56.129.70");
	shared_ptr<Server> server0=make_shared<RealServer>(ip0);
	shared_ptr<Server> server1=make_shared<RealServer>(ip1);
	const string google_url("www.google.com");
	const string baidu_url("www.baidu.com");
	cout<<server0->response(google_url)<<endl;
	cout<<server1->response(baidu_url)<<endl;
	const string ip2("10.56.122.88");
	shared_ptr<Server> server2=make_shared<ProxyServer>(ip2);
	dynamic_pointer_cast<ProxyServer>(server2)->addURL(google_url,server0);
	dynamic_pointer_cast<ProxyServer>(server2)->addURL(baidu_url,server1);

	const string tudou_url("www.tudou.com");
	cout<<server2->response(google_url)<<endl;
	cout<<server2->response(baidu_url)<<endl;
	cout<<server2->response(tudou_url)<<endl;

	dynamic_pointer_cast<ProxyServer>(server2)->removeURL(google_url);
	cout<<server2->response(google_url)<<endl;

	return  0;
}







