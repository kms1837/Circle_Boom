#include "circle_manager.h"

using namespace std;
USING_NS_CC;

CircleManager* CircleManager::create(Scene* inScene) {
	CircleManager* newCircle = new CircleManager;
	newCircle->scene_ = inScene;

	return newCircle;
}

void CircleManager::createCircle() {
	createCircle("tempcircle.png");
}

void CircleManager::createCircle(string fileName) {
	float setX, setY;
	FadeIn *fade = FadeIn::create(0.5);

	Size winSize = CCDirector::getInstance()->getVisibleSize();

	Circle* newCircle = new Circle;
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

	newCircle->fliping();

	circleList_.push_back(newCircle);
	scene_->addChild(newCircleSprite, kSpriteDepth);
	scene_->addChild(newCircle->streak, kStreakDepth);

	newCircleSprite->runAction(fade);
}// 구체 생성, scene에 추가, 리스트에 추가

void CircleManager::remove(Circle* removeCircle) {
	ParticleSystemQuad* particle = ParticleSystemQuad::create(kDeadEffect);
	particle->setPosition(removeCircle->sprite->getPosition());
	scene_->addChild(particle);

	scene_->removeChild(removeCircle->sprite);
	scene_->removeChild(removeCircle->streak);
	circleList_.remove(removeCircle);
}

list<Circle*> CircleManager::getCircles() {
	return circleList_;
}

list<Circle*> CircleManager::getInnerCircles(list<Vec2> points) {
	list<Circle*> innerCircles;
	Vec2 position;

	for (auto circle : circleList_) {
		position = circle->sprite->getPosition();
		if (Utility::inpoly(points, position)) {
			innerCircles.push_back(circle);
		}
	}

	return innerCircles;
}

void CircleManager::styleClear() {
	for (auto circle : circleList_) {
		circle->sprite->updateDisplayedColor(Color3B(255, 255, 255));
	}
}

void CircleManager::running() {
	for (auto circle : circleList_) {
		circle->move();
	}
}// 구체 동작