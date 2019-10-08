#pragma once
#include <vector>
#include <iostream>

class ConsoleCommand;
class Game;

class Console {
public:
	Console(Game*);
	void start();

protected:
	Game* _game;
	ConsoleCommand* _consoleCommand;

	bool nextCommand();
	bool dispatchCommand(std::vector<std::string>);
};