#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class commandKey
{
	private:
	char key;

	public:
	void setKey(char key){
		this->key = key;
	}

	bool IsEqual(char key){
		return (this->key == key);
	}

	virtual void Execute() = 0; 
};

class insert : public commandKey
{
	public:
	void Execute()
	{
		cout << "insert" << endl;;
		return ;
	}
};

class del : public commandKey
{
	public:
	void Execute()
	{
		cout << "delete" << endl;;
		return ;
	}
};

class search : public commandKey
{
	public:
	void Execute()
	{
		cout << "search" << endl;
		return ;
	}
};

class change : public commandKey
{
	public:
	void Execute()
	{
		cout << "change" << endl;
		return ;
	}
};

class ex : public commandKey
{
	public:
	void Execute()
	{
		cout << "exit" << endl;
		return ;
	}
};

class ne : public commandKey
{
	public:
	void Execute()
	{
		cout << "next" << endl;
		return ;
	}
};

class post : public commandKey
{
	public:
	void Execute()
	{
		cout << "post" << endl;
		return ;
	}
};

class commandHandler
{
	private:
	vector<commandKey*> commands;

	public:
	void addCommand(commandKey *command){
		commands.push_back(command);
	}

	bool Execute(char key){
		vector<commandKey*>::iterator start = commands.begin();
		vector<commandKey*>::iterator end = commands.end();

		while (start != end){
			if ((*start)->IsEqual(key)){
				(*start)->Execute();
				return true;
			}
			start++;
		}
		return false;
	}
};

void printTxt(string txt)
{
	
}

string* setTxt()
{
	string line;
	ifstream txt("test.txt");

	getline(txt,line);

}

int main(){
	commandHandler *commands = new commandHandler;

	commandKey *commandInsert = new insert;
	commandInsert->setKey('i');
	commands->addCommand(commandInsert);

	commandKey *commandDelete = new del;
	commandDelete->setKey('d');
	commands->addCommand(commandDelete);

	commandKey *commandSearch = new search;
	commandSearch->setKey('s');
	commands->addCommand(commandSearch);

	commandKey *commandNext = new ne;
	commandNext->setKey('n');
	commands->addCommand(commandNext);

	commandKey *commandPost = new post;
	commandPost->setKey('p');
	commands->addCommand(commandPost);

	commandKey *commandExit = new ex;
	commandExit->setKey('t');
	commands->addCommand(commandExit);

	commandKey *commandChange = new change;
	commandChange->setKey('c');
	commands->addCommand(commandChange);

	char command;
	string *txt = setTxt();

	do
	{
		cout << "input : ";
		cin >> command;
		if (commands->Execute(command) == false){
			cout << "invalid command" << endl;
		}

	} while (command != 't');
	

}