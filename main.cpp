#include <string>
#include "Classes/PostMachine.cpp"

int main()
{
	auto postMachine = new PostMachine();
	string *path = new string();
	string *commands = new string();
	*path = "input.txt";
	*commands = "commands.txt";
	postMachine->readData(*path);
	postMachine->readCommands(*commands);
	string *result = new string();
	*result = postMachine->start();
	cout << *result;
	delete path, delete commands, delete result;
	return 0;
}
