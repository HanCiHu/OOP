#include <iostream>
#include <string>

using namespace std;


class bird{
	protected:
	int altitude;
	int size;

	public:
	virtual int getFeed() = 0;
	virtual bird operator>(bird &b) = 0;

	bird(int altitude, int size){
		this->altitude = altitude;
		this->size = size;
	}

	int getAltitue(){
		return this->altitude;
	}
};

class vulture : public bird{
	string feed;
	public :
	vulture(int altitude, int size, string feed) : bird(altitude, size){
		this->feed = feed;
	}
	int getFeed(){
		cout << "vulture's feed is " << this->feed << endl;
	}
	bird operator>(bird &b){
		return this->altitude > b.getAltitue() ? *this : b;
	}
};

class swallow : public bird{
	string feed;
	public:
	swallow(int altitude, int size, string feed) : bird(altitude, size){
		this->feed = feed;
	}
	int getFeed(){
		cout << "swallow's feed is " << this->feed << endl;
	}

	bird operator>(bird &b){
		return this->altitude > b.getAltitue() ? *this : b;
	}
};

class chicken : public bird{
	string feed;
	public:
	chicken (int altitude, int size, string feed) : bird(altitude, size){
		this->feed = feed;
	}
	int getFeed(){
		cout << "chicken's feed is " << this->feed << endl;
	}

	bird operator>(bird &b){
		return this->altitude > b.getAltitue() ? *this : b;
	}
};

class dog {
protected:
	int size;
	string name;
	int popularity;

public :
	dog(int size, string name) {
		this->size = size;
		this->name = name;
	}
	virtual int getPopularity() = 0;
	virtual dog operator>(dog &d) = 0;
	int getPopularity() {
		return popularity;
	}

};

class Retriever : public dog {
	int popularity;
	public :
	Retriever(int size, string name, int pop) : dog(size,name){
		this->popularity = pop;
	}
	int getPopularity(){
		cout << "Retriever popularity is " << this->popularity << endl;
	}
	dog operator>(dog &d){
		return this->popularity > d.getPopularity() ? *this : d;
	}
};

class Beagle : public dog {
	int popularity;
	public :
	Beagle(int size, string name, int pop) : dog(size,name){
		this->popularity = pop;
	}
	int getPopularity() {
		cout << "Beagle popularity is " << this->popularity << endl;
	}
	dog operator>(dog &d){
		return this->popularity > d.getPopularity() ? *this : d;
	}
};

class Maltese : public dog {
	int popularity;
	public :
	Maltese(int size, string name, int pop) : dog(size,name){
		this->popularity = pop;
	}
	int getPopularity() {
		cout << "Maltese popularity is " << this->popularity << endl;
	}
	dog operator>(dog &d){
		return this->popularity > d.getPopularity() ? *this : d;
	}
};

int main()
{
	bird *bird1 =  new vulture(1200, 2000, "meet");
	dog *dog1 = new Retriever(100,"james",10);
	dog *dog2 = new Beagle(50,"Alt",5);
	dog1.getPopularity();
}
