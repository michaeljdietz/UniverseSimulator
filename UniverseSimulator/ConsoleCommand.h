#pragma once
#include <vector>
#include <iostream>

class Game;

class ConsoleCommand {
public:
	ConsoleCommand(Game*);
	void help();
	void set(const std::string, const long);
	void info();
	void list();
	void generate(long, long);
	void find(const std::string, const std::string, const std::string, const float, const long);

private:
	std::vector<std::string> commands = {"info", "generate [start refId] [end refId]","set [objectType] [refId]", "find [objectType] [property] [operation] [value] [optional offset]","help", "exit"};
	Game* _game;
};