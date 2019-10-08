#pragma once
#include <unordered_map>
#include "Reference.h"
#include "stdafx.h"

class AstronomicalObject : public Reference {
public:
	AstronomicalObject(Game*);

	std::string getObjectType();
	std::string getChildType();
	float getMass();
	float getMinorRadius();
	float getMajorRadius();
	float getLuminosity();
	float getTemperature();
	std::vector<float> getOrigin();
	long getChildCount();
	AstronomicalObject* getParent();
	AstronomicalObject* getAncestorOrSelfWithChildType(const std::string);
	std::unordered_map<long, AstronomicalObject*> getChildren();

	void setMass(const float);
	void setMinorRadius(const float);
	void setMajorRadius(const float);
	void setLuminosity(const float);
	void setTemperature(const float);
	void setOrigin(const std::vector<float>);
	void setChildCount(const long);
	void setParent(AstronomicalObject*);
	void setChildren(const std::unordered_map<long, AstronomicalObject*>);
	void addChild(AstronomicalObject*);
	virtual AstronomicalObject* createChild(const long);
	virtual AstronomicalObject* getChild(const long);

protected:
	std::string _objectType;
	std::string _childType;
	std::vector<float> _origin;
	float _mass;
	float _minorRadius;
	float _majorRadius;
	float _luminosity;
	float _temperature;
	AstronomicalObject *_parent;
	std::unordered_map<long, AstronomicalObject*> _children;
	long _childCount;
	float _axisCoordinateCount;
};