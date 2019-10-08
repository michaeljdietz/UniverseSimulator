#pragma once

class Game;

class Reference {
public:
	Reference(Game*);
	static long nextRefId();
	long getRefId();

protected:
	long _refId;
	static long _nextRefId;
	Game* _game;
};