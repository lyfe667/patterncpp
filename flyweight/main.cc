#include<iostream>
#include<memory>
#include<map>
using namespace std;

class Position{
public:
	Position(int x, int y)
		:x_(x), y_(y)
	{
	
	}
	void setx(int x){
		x_=x;
	}
	void sety(int y){
		y_=y;
	}
	int getx(){
		return x_;
	}
	int gety(){
		return y_;
	}

	void showPosition(){
		cout<<"x: "<<x_<<", y: "<<y_<<endl;
	}
private:
	int x_, y_;
};

class IChess{
public:
	virtual void display(Position &pos)=0;
};

class BlackChess: public IChess{
public:
	virtual void display(Position &pos) override{
		cout<<"black chess, ";
		pos.showPosition();
	}
};

class RedChess: public IChess{
public:
	virtual void display(Position &pos) override{
		cout<<"red chess, ";
		pos.showPosition();
	}	
};

enum Color{red, black};

class ChessFactory{
private:
	map<Color, shared_ptr<IChess>> chesses_;

public:
	shared_ptr<IChess> createChess(Color color){
		map<Color, shared_ptr<IChess>>::iterator it = chesses_.find(color);
		if(it==chesses_.end()){
			if(color==red){
				return make_shared<RedChess>();
			}else if(color==black){
				return make_shared<BlackChess>();
			}
		}else{
			return chesses_[color];
		}
	}
};

int main(){
	Position pos(0, 0);
	ChessFactory cf;
	cf.createChess(red)->display(pos);
	pos.setx(1);
	pos.sety(1);
	cf.createChess(black)->display(pos);
	pos.setx(7);
	pos.sety(7);
	cf.createChess(red)->display(pos);

	return 0;
}











