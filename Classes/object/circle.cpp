#include "circle.h"

USING_NS_CC;

Circle::Circle() {

}

Circle::~Circle() {

}

void Circle::fliping() {
	bool flip = this->movePosition.x == 1 ? true : false;
	this->sprite->setFlippedX(flip);
}

void Circle::move() {
	Size winSize = CCDirector::getInstance()->getVisibleSize();
	Vec2 position = sprite->getPosition();

	if (position.x > winSize.width || position.x < 0)
		movePosition.x *= -1;

	if (position.y > winSize.height || position.y < 0)
		movePosition.y *= -1;

	position.add(movePosition);

	sprite->setPosition(position);
	streak->setPosition(position);

	fliping();
}