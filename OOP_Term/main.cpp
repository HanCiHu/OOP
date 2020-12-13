#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <cstdlib>
using namespace std;

string txt, console_message, command;
vector<string> words;
vector<vector<string> > pages;
int pages_index = 0;

int stringToInt(string str);
void printPage();
void set_pages();
void make_pages();
void saveTxt();
string getTxt();

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
		regex re("i\\((\\d+),(\\d+),(\\w+)\\)");
		smatch match;
		if (regex_match(command, re)){
			regex_search(((const string)command).begin(),((const string)command).end(), match, re);

			int line = stringToInt(match[1]);
			int index = stringToInt(match[2]);

			if (line > 20 || line <= 0 || pages.size() - pages_index < line){
				console_message = "해당 line이 존재하지 않습니다.";
				return ;
			}
			if (index > pages[line - 1].size() || index < 0){
				console_message = "유효한 index를 입력해주세요.";
				return ;
			}
			if (match[3].length() > 75){
				console_message = "최대 75바이트 까지만 입력할수 있습니다.";
				return ;
			}
			pages[pages_index + line - 1].insert(pages[pages_index + line - 1].begin() + index, 1, match[3]);
			set_pages();
			console_message = command;
			return;
		}
		console_message = "i(line(int), index(int), word(string))형으로 입력해주세요.";
		return ;
	}
};

class del : public commandKey
{
	public:
	void Execute()
	{
		regex re("d\\((\\d+),(\\d+)\\)");
		smatch match;

		if (regex_match(command, re)){
			regex_search(((const string)command).begin(),((const string)command).end(), match, re);

			int line =stringToInt(match[1]);
			int index = stringToInt(match[2]) - 1;
			if (line > 20 || line <= 0 || pages.size() - pages_index < line){
				console_message = "해당 line이 존재하지 않습니다.";
				return ;
			}
			if (index > pages[line - 1].size() - 1 || index < 0){
				console_message = "해당 index가 존재하지 않습니다";
				return ;
			}
			pages[pages_index + line - 1].erase(pages[pages_index + line - 1].begin() + index);
			set_pages();
			console_message = command;
			return;
		}
		console_message = "d(line(int), index(int))형으로 입력해주세요.";
		return ;
	}
};

class se : public commandKey
{
	public:
	void Execute()
	{
		regex re("s\\((\\w+)\\)");
		smatch match;
		if (regex_match(command, re)){
			regex_search(((const string)command).begin(),((const string)command).end(), match, re);
			if (match[1].length() > 75){
				console_message = "최대 75바이트 까지만 입력할수 있습니다.";
				return;
			}
			else{
				for (int i = 0; i < pages.size(); i++){
					for (int j = 0; j < pages[i].size(); j++){
						if (pages[i][j] == match[1]){
							pages_index = i;
							console_message = command;
							return ;
						}
					}
				}
			}
			console_message = "단어를 찾을수 없습니다.";
			return;
		}
		console_message = "s(word) 형으로 입력해주세요.";
		return ;
	}
};

class change : public commandKey
{
	public:
	void Execute()
	{
		bool flag = false;
		regex re("c\\((\\w+),(\\w+)\\)");
		smatch match;
		if (regex_match(command, re)){
			regex_search(((const string)command).begin(),((const string)command).end(), match, re);
			if (match[1].length() > 75 || match[2].length() > 75){
				console_message = "최대 75바이트 까지만 입력할수 있습니다.";
				return;
			}
			else{
				for (int i = 0; i < pages.size(); i++){
					for (int j = 0; j < pages[i].size(); j++){
						if (pages[i][j] == match[1]){
							flag = true;
							pages[i][j] = match[2];
						}
					}
				}
			}
			if (flag){
				console_message = command;
				set_pages();
			}
			else console_message = "단어를 찾을수 없습니다.";
			return;
		}
		console_message = "c(word,word) 형으로 입력해주세요.";
		return ;
	}
};

class ex : public commandKey
{
	public:
	void Execute()
	{
		console_message = command;
		saveTxt();
		cout << "exit" << endl;
		return ;
	}
};

class ne : public commandKey
{
	public:
	void Execute()
	{
		if (pages_index == pages.size() - 20){
			console_message = "이미 마지막 페이지 입니다.";
			return ;
		}
		else if (pages_index + 40 > pages.size()) pages_index = pages.size() - 20;
		else pages_index += 20;
		console_message = "다음 페이지";
		return ;
	}
};

class post : public commandKey
{
	public:
	void Execute()
	{
		if (pages_index == 0){
			console_message = "이미 첫번째 페이지 입니다.";
			return ;
		}
		else if (pages_index - 20 < 0) pages_index = 0;
		else pages_index -= 20;
		console_message = "이전 페이지";
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

void saveTxt(){
	ofstream out("test.txt");
	for(int i=0; i < words.size(); i++){
		out << words[i] << " ";
	}
	out.close();
}

int stringToInt(string str)
{
	int ret = 0;
	for (int i = 0; i < str.length(); i++){
		ret = (ret * 10) + (str[i] - '0');
	}
	return ret;
}

void printPage()
{
	int k = 0;
	for (int i = pages_index; i < pages_index + 20 && i < pages.size(); i++){
		k++;
		if (k < 10) cout << " " << k << "| ";
		else cout << k << "| ";
		for (int j = 0; j < pages[i].size(); j++){
			cout << pages[i][j] << " ";
		}
		cout << endl;
	}
}

string getTxt()
{
	ifstream File;
	string txt = "";

	File.open("test.txt");
	if (File.is_open()){
		while(!File.eof()){
			getline(File, txt);
		}
	}
	File.close();
	return txt;
}

void set_pages()
{
	vector<string> lines;
	int len = 0 ;
	words.clear();
	for (int i = 0; i < pages.size(); i++){
		for (int j = 0; j < pages[i].size(); j++){
			words.push_back(pages[i][j]);
		}
	}
	pages.clear();
	for (int i = 0; i < words.size(); i++){
		if (len + words[i].length() > 75){
			pages.push_back(lines);
			lines.clear();
			lines.push_back(words[i]);
			len = words[i].length();
		}
		else{
			len += words[i].length();
			lines.push_back(words[i]);
		}
	}
	pages.push_back(lines);
}

void make_pages()
{
	vector<string> lines;
	istringstream ss(txt);
	string word;
	lines.clear();

	while (getline(ss, word, ' ')){
		words.push_back(word);
	}

	int len = 0 ;

	for (int i = 0; i < words.size(); i++){
		if (len + words[i].length() > 75){
			pages.push_back(lines);
			lines.clear();
			lines.push_back(words[i]);
			len = words[i].length();
		}
		else{
			len += words[i].length();
			lines.push_back(words[i]);
		}
	}
	pages.push_back(lines);
}

int main(){
	commandHandler *commands = new commandHandler;

	commandKey *commandInsert = new insert;
	commandInsert->setKey('i');
	commands->addCommand(commandInsert);

	commandKey *commandDelete = new del;
	commandDelete->setKey('d');
	commands->addCommand(commandDelete);

	commandKey *commandSearch = new se;
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

	txt = getTxt();
	make_pages();

	do
	{
		printPage();
		cout << "-----------------------------------------------------------------------------------------------------------" << endl;
		cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------" << endl;
		cout << "(콘솔 메세지) " << console_message << endl;
		cout << "-----------------------------------------------------------------------------------------------------------" << endl;
		cout << "입력: "; cin >> command;
		cout << "-----------------------------------------------------------------------------------------------------------" << endl;

		if (commands->Execute(command[0]) == false) console_message = "invalid command";

	} while (command[0] != 't');
}