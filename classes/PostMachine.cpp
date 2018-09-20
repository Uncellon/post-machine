#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class PostMachine
{
public:
	PostMachine();
	~PostMachine();

	void readData(string&);
	void readCommands(string&);
	void saveData(string&);
	string start();

private:
	string *data;
	vector<string> *commands;
	int mark;

};

inline PostMachine::PostMachine()
{
	data = new string();
	commands = new vector<string>();
	mark = 0;
}

inline PostMachine::~PostMachine()
{
	delete data;
	delete commands;
}

inline void PostMachine::readData(string& path)
{
	ifstream in(path);
	in >> *data;
	in >> mark;
	in.close();
}

inline void PostMachine::readCommands(string& path)
{
	ifstream in(path);
	while (!in.eof())
	{
		string *command = new string();
		getline(in, *command);
		commands->push_back(*command);
		delete command;
	}
	in.close();
}

inline string PostMachine::start()
{
	int currentCommand = 0;
	while (true)
	{
		string *command = new string();
		if (currentCommand < commands->size())
			*command = commands->at(currentCommand);
		else
			return("Command out of range, can't find stop command!");
		// Left command
		if (command->find("<-") != string::npos)
		{
			--mark;
			// Infinity data
			if (mark < 0)
			{
				data->insert(0, "0");
				++mark;
			}
		}
		// Right command
		else if (command->find("->") != string::npos)
		{
			++mark;
			// Infinity data
			if (mark > data->length())
			{
				data->insert(data->length(), "0");
			}
		}
		// Branching command
		else if (command->find("?") != string::npos)
		{
			if ((*data)[mark] == '0')
			{
				currentCommand = stoi(command->substr(2, command->find(";"))) - 1;
				continue;
			}
			else
			{
				currentCommand = stoi(command->substr(command->find(";") + 1)) - 1;
				continue;
			}
		}
		// Set mark
		else if (command->find("V") != string::npos)
		{
			if ((*data)[mark] == '0')
				(*data)[mark] = '1';
			else
				return("Error set mark");
		}
		// Del mark
		else if (command->find("X") != string::npos)
		{
			if ((*data)[mark] == '1')
				(*data)[mark] = '0';
			else
				return("Error delete mark");
		}
		else
			break;
		++currentCommand;
		delete command;
	}
	return *data;
}
