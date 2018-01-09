#include "circle.h"

using namespace std;
USING_NS_CC;

Circle* Circle::create(Scene* inScene) {
	Circle* newCircle = new Circle;
	newCircle->scene_ = inScene;

	return newCircle;
}

void Circle::createCircle() {
	createCircle("tempcircle.png");
}

void Circle::createCircle(string fileName) {
	float setX, setY;
	bool flip;
	FadeIn *fade = FadeIn::create(0.5);

	Size winSize = CCDirector::getInstance()->getVisibleSize();

	circleObj* newCircle = new circleObj;
	Sprite* newCircleSprite = Sprite::create(fileName);
	
	int innerX = winSize.width - newCircleSprite->getContentSize().width;
	int innerY = winSize.height - newCircleSprite->getContentSize().height;

	do {
		setX = (rand() % innerX) + newCircleSprite->getContentSize().width;
		setY = (rand() % innerY) + newCircleSprite->getContentSize().height;
	} while (setX<30 || setX>innerX || setY<30 || setY>innerY);
	// 화면 안쪽으로 구체 배치

	newCircleSprite->setPosition(setX, setY);

	newCircleSprite->setOpacity(0);
	newCircle->sprite = newCircleSprite;

	newCircle->movePosition.x = setMovePosition[rand() % 2];
	newCircle->movePosition.y = setMovePosition[rand() % 2];

	newCircle->moveSpeed = setMoveSpeed[rand() % 2];

	newCircle->streak = MotionStreak::create(1, 3, 70, Color3B::GREEN, "paddle.png");

	flip = newCircle->movePosition.x == 1 ? true : false;
	newCircleSprite->setFlippedX(flip);

	circleList_.push_back(newCircle);
	scene_->addChild(newCircleSprite, kSpriteDepth);
	scene_->addChild(newCircle->streak, kStreakDepth);

	newCircleSprite->runAction(fade);
}// 구체 생성, scene에 추가, 리스트에 추가

void Circle::remove(Circle::circleObj* removeCircle) {
	ParticleSystemQuad* particle = ParticleSystemQuad::create(kDeadEffect);
	particle->setPosition(removeCircle->sprite->getPosition());
	scene_->addChild(particle);

	scene_->removeChild(removeCircle->sprite);
	scene_->removeChild(removeCircle->streak);
	circleList_.remove(removeCircle);
}

list<Circle::circleObj*> Circle::getCircles() {
	return circleList_;
}

list<Circle::circleObj*> Circle::getInnerCircles(list<Vec2> points) {
	list<circleObj*> innerCircles;
	Vec2 position;

	for (auto circle : circleList_) {
		position = circle->sprite->getPosition();
		if (Utility::inpoly(points, position)) {
			innerCircles.push_back(circle);
		}
	}

	return innerCircles;
}

void Circle::styleClear() {
	for (auto circle : circleList_) {
		circle->sprite->updateDisplayedColor(Color3B(255, 255, 255));
	}
}

void Circle::running() {
	Size winSize = CCDirector::getInstance()->getVisibleSize();
	bool flip = false;

	list<circleObj*>::iterator iter;
	for (auto circle : circleList_) {
		Sprite* movedSprite = circle->sprite;
		Vec2 position = movedSprite->getPosition();

		if (position.x > winSize.width || position.x < 0)
			circle->movePosition.x *= -1;

		if (position.y > winSize.height || position.y < 0)
			circle->movePosition.y *= -1;

		flip = circle->movePosition.x == 1 ? true : false;
		movedSprite->setFlippedX(flip);

		position.add(circle->movePosition);

		movedSprite->setPosition(position);
		circle->streak->setPosition(position);
	}
}// 구체 동작