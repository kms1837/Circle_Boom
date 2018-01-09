#pragma once

#include "cocos2d.h"

class Circle
{
public:
	Circle();
	~Circle();
	cocos2d::Sprite* sprite;
	cocos2d::Vec2 movePosition; // 이동각도
	cocos2d::MotionStreak *streak; // 잔상
	int color;
	int timer;

	float moveSpeed; // 이동 속도

	void fliping();
	void move();

private:
	
};