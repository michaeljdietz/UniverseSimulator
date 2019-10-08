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
		// TODO: add real and reusable command validation
		long refId;
		try {
			refId = stol(command.at(2));
		}
		catch (...) {
			std::cout << "Error. Set command requires 2nd parameter to be a valid reference ID #\n";
			return true;
		}
		_consoleCommand->set(command.at(1), refId);
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
		// TODO: add real and reusable command validation
		long start, end;
		try {
			start = stol(command.at(1));
			end = stol(command.at(2));
		}
		catch (...) {
			std::cout << "Error. Please specify valid numbers for start and end reference IDs\n";
			return true;
		}
		_consoleCommand->generate(start, end);
		return true;
	}

	if (command.at(0) == "find" && command.size() >= 5) {
		long skip;
		float value;

		try {
			value = stof(command.at(4));;
		}
		catch (...) {
			std::cout << "Error. Find command requires the 4th parameter to be a valid number.\n";
			return true;
		}

		try {
			skip = 0;

			if (command.size() >= 6) {
				skip = stol(command.at(5));
			}
		}
		catch (...) {
			std::cout << "Error. Find command requires the 5th parameter to be a valid number.\n";
			return true;
		}

		_consoleCommand->find(command.at(1), command.at(2), command.at(3), value, skip);
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