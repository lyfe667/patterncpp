#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Person{
private:
	int id_;
	int age_;
	string gender_;
	string maritalStatus_;
public:
	Person(int id,int age, const string &gender, const string &maritalStatus)
		:id_(id), age_(age), gender_(gender) ,maritalStatus_(maritalStatus)
	{

	}
	int getId() const{
		return id_;
	}
	int getAge() const{
		return age_;
	}
	string getGender() const{
		return gender_;
	}
	string getMaritalStatus() const{
		return maritalStatus_;
	}
	void show() const{
		cout<<"id: "<<id_<<" , age: "<<age_<<" , gender: "<< gender_
			<<" , marital status: "<<maritalStatus_<<endl;
	}
};

class Cretiria{
public:
	virtual vector<Person> filter(const vector<Person> &persons)=0;
};

class FemaleCretiria: public Cretiria{
public:
	virtual vector<Person> filter(const vector<Person> &persons) override{
		vector<Person> result;
		for(vector<Person>::const_iterator it=persons.begin();it!=persons.end();it++){
			if(it->getGender()=="female"){
				result.push_back(*it);
			}
		}
		return result;
	}
};

class MaleCretiria: public Cretiria{
public:
	virtual vector<Person> filter(const vector<Person> &persons) override{
		vector<Person> result;
		for(vector<Person>::const_iterator it=persons.begin();it!=persons.end();it++){
			if(it->getGender()=="male"){
				result.push_back(*it);
			}
		}
		return result;
	}
};

class SingleCretiria: public Cretiria{
public:
	virtual vector<Person> filter(const vector<Person> &persons) override{
		vector<Person> result;
		for(vector<Person>::const_iterator it=persons.begin();it!=persons.end();it++){
			if(it->getMaritalStatus()=="single"){
				result.push_back(*it);
			}
		}
		return result;
	}
};
//使用独立的And Or标准进行解耦
class OrCretiria: public Cretiria{
private:
	shared_ptr<Cretiria> cretiria0_;
	shared_ptr<Cretiria> cretiria1_;
public:
	OrCretiria(const shared_ptr<Cretiria> &cretirial0, const shared_ptr<Cretiria> &cretiria1)
		:cretiria0_(cretirial0), cretiria1_(cretiria1)
	{
	
	}
	virtual vector<Person> filter(const vector<Person> &persons) override{
		vector<Person> personsByc0 = cretiria0_->filter(persons);
		vector<Person> personsByc1 = cretiria1_->filter(persons);
		vector<Person> in0out1;
		for(vector<Person>::iterator it=personsByc0.begin();it!=personsByc0.end();it++){
			if(0==count_if(personsByc1.begin(), personsByc1.end(),[it](const Person &p1)->bool{return it->getId()==p1.getId();})){
				in0out1.push_back(*it);
			}
		}
		personsByc1.insert(personsByc1.end(),in0out1.begin(),in0out1.end());
		return personsByc1;
	}
	void setCretiria0(const shared_ptr<Cretiria> &cretiria){
		cretiria0_=cretiria;
	}
	void setCretiria1(const shared_ptr<Cretiria> &cretiria){
		cretiria1_=cretiria;
	}
	
};

class AndCretiria: public Cretiria{
private:
	shared_ptr<Cretiria> cretiria0_;
	shared_ptr<Cretiria> cretiria1_;
public:
	AndCretiria(const shared_ptr<Cretiria> &cretirial0, const shared_ptr<Cretiria> &cretiria1)
		:cretiria0_(cretirial0), cretiria1_(cretiria1)
	{
	
	}
	virtual vector<Person> filter(const vector<Person> &persons) override{
		vector<Person> personsByc0 = cretiria0_->filter(persons);
		vector<Person> personsByc1 = cretiria1_->filter(personsByc0);
		return personsByc1;
	}
	void setCretiria0(const shared_ptr<Cretiria> &cretiria){
		cretiria0_=cretiria;
	}
	void setCretiria1(const shared_ptr<Cretiria> &cretiria){
		cretiria1_=cretiria;
	}
};

void showAllPersons(const vector<Person> &persons){
	for(const Person &p: persons){
		p.show();
	}
	cout<<endl;
}

int main(){
	Person p0(0,12,"male","single");
	Person p1(1,25,"female","married");
	Person p2(2,22,"male","married");
	Person p3(3,55,"male","married");
	Person p4(4,4,"female","single");
	Person p5(5,99,"female","single");
	Person p6(6,18,"male","single");

	vector<Person>  persons{p0, p1, p2, p3, p4, p5, p6};
	showAllPersons(persons);

	shared_ptr<FemaleCretiria> fc=make_shared<FemaleCretiria>();
	vector<Person> ps=fc->filter(persons);
	showAllPersons(ps);

	shared_ptr<MaleCretiria> mc=make_shared<MaleCretiria>();
	ps=mc->filter(persons);
	showAllPersons(ps);

	shared_ptr<SingleCretiria> sc=make_shared<SingleCretiria>();
	ps=sc->filter(persons);
	showAllPersons(ps);

	shared_ptr<AndCretiria> ac=make_shared<AndCretiria>(fc,sc);
	ps=ac->filter(persons);
	showAllPersons(ps);

	ac->setCretiria0(mc);
	ps=ac->filter(persons);
	showAllPersons(ps);
	
	ac->setCretiria1(fc);
	ps=ac->filter(persons);
	showAllPersons(ps);
	
	shared_ptr<OrCretiria> oc=make_shared<OrCretiria>(fc,sc);
	ps=oc->filter(persons);
	showAllPersons(ps);

	oc->setCretiria0(mc);
	ps=oc->filter(persons);
	showAllPersons(ps);
	
	return 0;
}














