#include<iostream>
#include<memory>
using namespace std;

enum LightState{ ON, OFF};

//reciever
class Light{
private:
	LightState state_;
public:
	Light(LightState state)
		:state_(state)
	{
	}
	void setState(LightState state){
			state_ = state;	
	}
	LightState getState(){
		return state_;
	}
	void showState(){
		if(state_==ON){
			cout<<"light is ON"<<endl;
		}else{
			cout<<"light is OFF"<<endl;
		}
	}
};

//abstract command
class Command{
public:
	virtual void execute() = 0;
};

//concrete command
class LightOnCommand: public Command{
private:
	shared_ptr<Light> light_;
public:
	LightOnCommand(const shared_ptr<Light> &light)
		:light_(light)
	{
		
	}
	virtual void execute() override{
		light_->setState(ON);
	}
};

class LightOffCommand: public Command{
private:
	shared_ptr<Light> light_;
public:
	LightOffCommand(const shared_ptr<Light> &light)
		:light_(light)
	{
		
	}

	virtual void execute() override{
		light_->setState(OFF);
	}
};

//invoker
class CommandInvoker{
private:
	shared_ptr<Command> command_;
public:
	CommandInvoker( )
	{
	
	}
	
	void takeCommand(const shared_ptr<Command> &command)
	{
		command_=command;
	}
	void executeCommand(){
		if(command_)
		{
			command_->execute();
		}else{
			cout<<"No Command is taken yet... "<<endl;
		}
	}
};

int main(){
	shared_ptr<Light> light = make_shared<Light>(OFF);
	shared_ptr<LightOnCommand> lonc = make_shared<LightOnCommand>(light);
	shared_ptr<LightOffCommand> loffc = make_shared<LightOffCommand>(light);
	shared_ptr<CommandInvoker> xiaoming = make_shared<CommandInvoker>();
	light->showState();
	
	xiaoming->takeCommand(lonc);
	xiaoming->executeCommand();
	light->showState();

	xiaoming->takeCommand(loffc);
	xiaoming->executeCommand();
	light->showState();

	return 0;
}






