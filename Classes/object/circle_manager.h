#pragma once

#include <list>
#include "cocos2d.h"
#include "circle.h"
#include "common\utility.h"

class CircleManager
{
public:    
	static CircleManager* create(cocos2d::Scene*);

	CircleManager();

	// utils
	void createCircle();
	void styleClear();
	void running();

	// getter & setter
	std::list<Circle*> getCircles();
	std::list<Circle*> getInnerCircles(std::list<cocos2d::Vec2> points);
	int getSize();

	void removeCircle(Circle* removeCircle);
	void remove();

private:
	const int spriteLayer;
	const int streakLayer;
	const std::string _dieEffectFile;

	std::list<Circle*> _circleList;
	cocos2d::Scene* _scene;
};
