#include "circle_manager.h"

using namespace std;
USING_NS_CC;

CircleManager::CircleManager() :
	_dieEffectFile("ExplodingRing.plist"),
	spriteLayer(2),
	streakLayer(1) {
}

CircleManager* CircleManager::create(Scene* inScene) {
	CircleManager* newCircle = new CircleManager;
	newCircle->_scene = inScene;

	return newCircle;
}

void CircleManager::createCircle() {
	float setX, setY;
	FadeIn* fade = FadeIn::create(0.5f);

	Size winSize = CCDirector::getInstance()->getVisibleSize();

	Circle* newCircle = new Circle();
	Sprite* circleSprite = newCircle->getSprite();

	int circleWidth = static_cast<int>(circleSprite->getContentSize().width);
	int circleHeight = static_cast<int>(circleSprite->getContentSize().height);
	
	int innerX = winSize.width - circleWidth;
	int innerY = winSize.height - circleHeight;

	do {
		setX = (rand() % innerX) + circleWidth;
		setY = (rand() % innerY) + circleHeight;
	} while (setX < 30 || setX > innerX || setY < 30 || setY > innerY);
	// 화면 안쪽으로 구체 배치

	log("Random Number : %d %d", setX, setY);

	circleSprite->setPosition(setX, setY);

	circleSprite->setOpacity(0);

	_circleList.push_back(newCircle);
	_scene->addChild(circleSprite, spriteLayer);
	_scene->addChild(newCircle->getStreak(), streakLayer);

	circleSprite->runAction(fade);
}// 구체 생성, scene에 추가, 리스트에 추가

void CircleManager::removeCircle(Circle* removeCircle) {
	ParticleSystemQuad* particle = ParticleSystemQuad::create(_dieEffectFile);
	particle->setPosition(removeCircle->getSprite()->getPosition());
	_scene->addChild(particle);

	removeCircle->release(_scene);
	_circleList.remove(removeCircle);
}

void CircleManager::remove() {
	auto removeList = _circleList;
	for (auto circle : removeList) {
		removeCircle(circle);
	}
}

list<Circle*> CircleManager::getCircles() {
	return _circleList;
}

int CircleManager::getSize() {
	return _circleList.size();
}

list<Circle*> CircleManager::getInnerCircles(list<Vec2> points) {
	list<Circle*> innerCircles;
	Vec2 position;

	for (auto circle : _circleList) {
		position = circle->getSprite()->getPosition();
		if (Utility::inpoly(points, position)) {
			innerCircles.push_back(circle);
		}
	}

	return innerCircles;
}

void CircleManager::styleClear() {
	for (auto circle : _circleList) {
		circle->getSprite()->updateDisplayedColor(Color3B(255, 255, 255));
	}
}

void CircleManager::running() {
	for (auto circle : _circleList) {
		circle->move();
	}
}// 구체 동작