#include "Console.h"
#include "ConsoleCommand.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

Console::Console(Game* game) {
	_game = game;
	_consoleCommand = new ConsoleCommand(game);
}

void Console::start() {
	while (nextCommand());
}

bool Console::nextCommand() {
	std::vector<std::string> command;
	std::string line, word;
	std::cout << "\n>";

	std::getline(std::cin, line);
	std::istringstream stream(line);

	while (stream >> word) {
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		command.push_back(word);
	}

	if (command.size() < 1) {
		command.push_back("");
	}

	return dispatchCommand(command);
}

bool Console::dispatchCommand(const std::vector<std::string> command) {

	if (command.at(0) == "set" && command.size() == 3) {
		_consoleCommand->set(command.at(1), stol(command.at(2)));
		return true;
	}

	if (command.at(0) == "info") {
		_consoleCommand->info();
		return true;
	}

	if (command.at(0) == "list") {
		_consoleCommand->list();
		return true;
	}

	if (command.at(0) == "generate" && command.size() == 3) {
		_consoleCommand->generate(stol(command.at(1)), stol(command.at(2)));
		return true;
	}

	if (command.at(0) == "find" && command.size() >= 5) {
		long skip = 0;
		if (command.size() >= 6) {
			skip = stol(command.at(5));
		}

		_consoleCommand->find(command.at(1), command.at(2), command.at(3), stof(command.at(4)), skip);
		return true;
	}

	if (command.at(0) == "help") {
		_consoleCommand->help();
		return true;
	}

	if (command.at(0) == "exit") {
		return false;
	}

	std::cout << "Unrecognized command\n";

	return true;
}