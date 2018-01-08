
#include "test_scene.h"

using namespace std;

USING_NS_CC;

TestScene::TestScene() {

}

TestScene::~TestScene() {

}

Scene* TestScene::scene() {
    return TestScene::create();
}

bool TestScene::init() {

	if (!Scene::init()) {
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/SHORT_BGM_09.mp3");

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TestScene::onTouchesBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TestScene::onTouchesMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TestScene::onTouchesEnded, this);
	
	circles_ = Circle::create(this);

	for (int i = 0; i < 10; i++) {
		circles_->createCircle();
	}

	this->schedule(schedule_selector(TestScene::update));

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	return true;
}

void TestScene::update(float dt) {
	circles_->running();
}

bool TestScene::onTouchesBegan(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	MotionStreak* streak = MotionStreak::create(0.5, 3, 50, Color3B::WHITE, "paddle.png");
	streak->setPosition(touchPosition);
	streak->setTag(123);
	addChild(streak);

	return true;
}

void TestScene::onTouchesMoved(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	MotionStreak* streak = (MotionStreak*)this->getChildByTag(123);

	streak->setPosition(touchPosition);
	
}

void TestScene::onTouchesEnded(Touch* touch, Event* event) {
	this->removeChildByTag(123);
}