#pragma once

#include <list>
#include "cocos2d.h"
#include "circle.h"
#include "common\utility.h"

class CircleManager
{
public:    
	static CircleManager* create(cocos2d::Scene*);

	// util
	void createCircle();
	void createCircle(std::string fileName);
	void styleClear();
	void running();

	// getter & setter
	std::list<Circle*> getCircles();
	std::list<Circle*> getInnerCircles(std::list<cocos2d::Vec2> points);

	void remove(Circle* removeCircle);

private:
	const int kSpriteDepth = 2;
	const int kStreakDepth = 1;
	const std::string kDeadEffect = "ExplodingRing.plist";

	std::list<Circle*> circleList_;
	cocos2d::Scene* scene_;

	double setMovePosition[2] = { -1, 1 };
	double setMoveSpeed[3] = { 1, 1.3, 1.6 };
};
