#pragma once

#include "cocos2d.h"

class Circle
{
public:
	Circle();
	Circle(const std::string);
	~Circle();

	// getter & setter
	cocos2d::Sprite* getSprite() { return _sprite; }
	cocos2d::MotionStreak* getStreak() { return _streak; }

	void init(const std::string fileName);
	void fliping();
	void move();

	void release(cocos2d::Scene* scene);

private:
	const std::string defaultSpriteFileName;
	const std::string streakFileName;
	const float circleSpeeds[3];

	cocos2d::Sprite* _sprite;
	cocos2d::Vec2 _moveDirection; // 이동각도
	cocos2d::MotionStreak* _streak; // 잔상
	int _color;
	int _timer;

	float _moveSpeed; // 이동 속도
};