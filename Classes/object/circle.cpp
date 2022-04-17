#include "circle.h"
USING_NS_CC;

Circle::Circle(): 
	defaultSpriteFileName("circle_90.png"),
	streakFileName("paddle.png"),
	circleSpeeds{ 1.f, 1.3f, 1.6f }
{
	init(defaultSpriteFileName);
}

Circle::Circle(const std::string fileName): Circle()
{
	init(fileName);
}

Circle::~Circle() {
	
}

void Circle::init(const std::string fileName) {
	_sprite = Sprite::create(fileName);
	_streak = MotionStreak::create(1, 3, 70, Color3B::GREEN, streakFileName);

	float randomDirection[] = { -1.f, 1.f };

	_moveDirection = { randomDirection[rand() % 2], randomDirection[rand() % 2] };
	_moveSpeed = circleSpeeds[rand() % 2];

	fliping();
}

void Circle::fliping() {
	bool flip = _moveDirection.x == 1 ? true : false;
	_sprite->setFlippedX(flip);
} // sprite µÚÁý±â

void Circle::move() {
	cocos2d::Size winSize = CCDirector::getInstance()->getVisibleSize();
	cocos2d::Vec2 position = _sprite->getPosition();

	if (position.x > winSize.width || position.x < 0) {
		_moveDirection.x *= -1;
	}

	if (position.y > winSize.height || position.y < 0) {
		_moveDirection.y *= -1;
	}

	position.add(_moveDirection);

	_sprite->setPosition(position);
	_streak->setPosition(position);

	fliping();
}

void Circle::release(Scene* scene) {
	scene->removeChild(_sprite);
	scene->removeChild(_streak);
}