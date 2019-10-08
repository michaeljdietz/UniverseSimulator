#include "Reference.h"

long Reference::_nextRefId = 1;

Reference::Reference(Game* game) {
	this->_refId = nextRefId();
	this->_game = game;
}

long Reference::nextRefId() {
	return ++_nextRefId;
}

long Reference::getRefId() {
	return this->_refId;
}