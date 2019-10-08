#include "ConsoleCommand.h"
#include "AstronomicalObject.h"
#include "Game.h"
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>

ConsoleCommand::ConsoleCommand(Game* game) {
	_game = game;
}

void ConsoleCommand::help() {
	std::cout << "Available commands: \n\n";
	
	for (std::string command : commands) {
		std::cout << command << "\n";
	}

	std::cout << "\nobjectType: universe, supercluster, cluster, galaxy\n";
	std::cout << "properties: childcount, mass, luminosity, majorradius, minorradius, temperature\n";
	std::cout << "operation: =, <, >, !=\n\n";
}

void ConsoleCommand::set(const std::string objectType, const long refId) {
	AstronomicalObject* currentObject = _game->getCurrentObject();
	if (!currentObject) {
		std::cout << "No current object set!\n";
		return;
	}

	currentObject = currentObject->getAncestorOrSelfWithChildType(objectType);
	if (!currentObject) {
		std::cout << "Could not find object of type " << objectType << " in hierarchy.\n";
	}

	if (objectType != "universe") {
		_game->setCurrentObject(currentObject->getChild(refId));
	}
	else {
		_game->setCurrentObject(currentObject);
	}


	std::cout << "Set object to " << objectType << " with refId " << std::to_string(refId) << "\n";
	info();
}

void ConsoleCommand::info() {
	AstronomicalObject* currentObject = _game->getCurrentObject();
	std::cout << "Object Type: " << currentObject->getObjectType() << "\n";
	std::cout << "Child Count: " << currentObject->getChildCount() << " " << currentObject->getChildType() << "s\n";
	std::cout << "Mass: " << currentObject->getMass() << " M.\n";
	std::cout << "Luminosity: " << currentObject->getLuminosity() << " L.\n";
	std::cout << "Minor Radius: " << currentObject->getMinorRadius() << " Mpc\n";
	std::cout << "Major Radius: " << currentObject->getMajorRadius() << " Mpc\n";
	std::cout << "Temperature: " << currentObject->getTemperature() << " keV\n";

	if (currentObject->getOrigin().size() >= 3) {
		std::cout << "Origin: "
			<< currentObject->getOrigin().at(0) << ", "
			<< currentObject->getOrigin().at(1) << ", "
			<< currentObject->getOrigin().at(2) << "\n";
	}
}

void ConsoleCommand::list() {
	AstronomicalObject* currentObject = _game->getCurrentObject();

	if (currentObject->getChildren().size() == 0) {
		std::cout << "There are no children for the current object\n";
		return;
	}

	std::cout << "Child RefIds:\n";

	std::unordered_map<long, AstronomicalObject*> children = currentObject->getChildren();
	std::for_each(children.begin(), children.end(),
		[](std::pair<long, AstronomicalObject*> element) {
			std::cout << element.first << "\n";
		});

	std::cout << "\nTotal of " << children.size() << " child objects\n";
}

void ConsoleCommand::generate(const long startRefId, const long endRefId) {
	auto start = std::chrono::high_resolution_clock::now();
	AstronomicalObject* currentObject = _game->getCurrentObject();
	if (!currentObject) {
		std::cout << "No current object set!\n";
		return;
	}

	for (long i = startRefId; i <= endRefId; ++i) {
		currentObject->getChild(i);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	long count = endRefId - startRefId + 1;

	std::cout << "Generated " << count << " objects in " << elapsed.count() << "s\n";
}

void ConsoleCommand::find(const std::string objectType, const std::string propertyName, const std::string operation, float value, long skip)
{
	AstronomicalObject* currentObject = _game->getCurrentObject();
	currentObject = currentObject->getAncestorOrSelfWithChildType(objectType);

	if (!currentObject) {
		std::cout << "Object type not found\n";
		return;
	}

	std::function<bool(float, float)> performOperation = [](float value1, float value2) -> bool { return true; };

	if (operation == "=") {
		performOperation = [](float value1, float value2) -> bool { return value1 == value2; };
	} else if (operation == ">") {
		performOperation = [](float value1, float value2) -> bool { return value1 > value2; };
	} else if (operation == "<") {
		performOperation = [](float value1, float value2) -> bool { return value1 < value2; };
	} else if (operation == "!=") {
		performOperation = [](float value1, float value2) -> bool { return value1 != value2; };
	}

	std::unordered_map<long, AstronomicalObject*> children = currentObject->getChildren();

	std::unordered_map<long, AstronomicalObject*>::const_iterator it = children.begin();

	for (it = children.begin(); it != children.end(); ++it) {
		currentObject = it->second;

		if ((propertyName == "childcount" && performOperation(currentObject->getChildCount(), value))
			|| (propertyName == "mass" && performOperation(currentObject->getMass(), value))
			|| (propertyName == "luminosity" && performOperation(currentObject->getLuminosity(), value))
			|| (propertyName == "minorradius" && performOperation(currentObject->getMinorRadius(), value))
			|| (propertyName == "majorradius" && performOperation(currentObject->getMajorRadius(), value))
			|| (propertyName == "temperature" && performOperation(currentObject->getTemperature(), value))) {
			--skip;
		}

		if (skip == -1) {
			_game->setCurrentObject(currentObject);
			break;
		}
	}

	if (it == children.end()) {
		std::cout << "No matching object was found.\n";
		return;
	}

	std::cout << "Matching object was found with refId " << it->first << "\n";
	info();
}