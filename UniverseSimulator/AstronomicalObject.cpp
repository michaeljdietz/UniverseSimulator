#include "AstronomicalObject.h"
#include "Game.h"
#include "Universe.h"
#include <vector>

AstronomicalObject::AstronomicalObject(Game* game)
: Reference(game) 
{}

std::string AstronomicalObject::getObjectType()
{
	return _objectType;
}

std::string AstronomicalObject::getChildType()
{
	return _childType;
}

float AstronomicalObject::getMass() {
	return _mass;
}

float AstronomicalObject::getMinorRadius() {
	return _minorRadius;
}

float AstronomicalObject::getMajorRadius()
{
	return _majorRadius;
}

float AstronomicalObject::getLuminosity() {
	return _luminosity;
}

float AstronomicalObject::getTemperature() {
	return _temperature;
}

std::vector<float> AstronomicalObject::getOrigin() {
	return _origin;
}

long AstronomicalObject::getChildCount()
{
	return _childCount;
}

AstronomicalObject* AstronomicalObject::getParent() {
	return _parent;
}

AstronomicalObject* AstronomicalObject::getAncestorOrSelfWithChildType(const std::string childType)
{
	AstronomicalObject* currentObject = _game->getCurrentObject();

	if (childType == "universe") {
		return _game->getUniverse();
	}

	while (childType != currentObject->getChildType() && currentObject->getParent()) {
		currentObject = currentObject->getParent();
	}

	if (childType != currentObject->getChildType()) {
		return nullptr;
	}

	return currentObject;
}

std::unordered_map<long, AstronomicalObject*> AstronomicalObject::getChildren() {
	return _children;
}

void AstronomicalObject::setMass(const float value) {
	_mass = value;
}

void AstronomicalObject::setMinorRadius(float value) {
	_minorRadius = value;
}

void AstronomicalObject::setMajorRadius(const float value)
{
	_majorRadius = value;
}

void AstronomicalObject::setLuminosity(const float value) {
	_luminosity = value;
}

void AstronomicalObject::setTemperature(const float value) {
	_temperature = value;
}

void AstronomicalObject::setOrigin(const std::vector<float> origin) {
	_origin = origin;
}

void AstronomicalObject::setParent(AstronomicalObject* body) {
	_parent = body;
}

void AstronomicalObject::setChildren(const std::unordered_map<long, AstronomicalObject*> bodies) {
	_children = bodies;
}

void AstronomicalObject::addChild(AstronomicalObject* body) {
	_children.emplace(body->getRefId(), body);

	setMass(getMass() + body->getMass());
	setLuminosity(getLuminosity() + body->getLuminosity());
	setTemperature(getTemperature() + body->getTemperature());
}

AstronomicalObject* AstronomicalObject::createChild(const long) {
	return new AstronomicalObject(_game);
}

AstronomicalObject* AstronomicalObject::getChild(const long refId) {
	std::unordered_map<long, AstronomicalObject*>::const_iterator it = _children.find(refId);
	
	if (it == _children.end() && _childCount > (long)_children.size()) {
		AstronomicalObject* child = createChild(refId);
		_children.emplace(refId, child);
		return child;
	}
	
	return it->second;
}

void AstronomicalObject::setChildCount(const long count) {
	_childCount = count;
}