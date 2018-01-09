
#include "test_scene.h"

using namespace std;

USING_NS_CC;

TestScene::TestScene():
score_(0),
combo_(0),
gameTimer_(0) {

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

	Size winSize = Director::getInstance()->getWinSize();

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/SHORT_BGM_09.mp3");
	circles_ = Circle::create(this);

	int margin = 30;

	//Label Object
	TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
	auto scoreTitle = Label::createWithTTF(ttfConfig, "score: ", TextHAlignment::LEFT, winSize.width);
	scoreTitle->setPosition(kLabelFontSIze + margin, winSize.height - 30);
	scoreTitle->setName("scoreLabel");
	this->addChild(scoreTitle, kLabelDepth);

	scoreLabel_ = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 150);
	// issue - score Label size
	scoreLabel_->setPosition(300, winSize.height - margin);
	scoreLabel_->setName("scoreLabel");
	this->addChild(scoreLabel_, kLabelDepth);

	circleCountLabel_ = Label::createWithTTF(ttfConfig, "0", TextHAlignment::CENTER, winSize.width);
	circleCountLabel_->setPosition(winSize.width / 2, winSize.height - margin);
	circleCountLabel_->setName("circleCountLabel");
	this->addChild(circleCountLabel_, kLabelDepth);

	//UI Object
	touchMovePointSpr_ = Sprite::create("pointercircle.png");
	touchMovePointSpr_->setColor(Color3B(0, 20, 255));
	this->addChild(touchMovePointSpr_);

	Sprite* backGround = Sprite::create("background/Pbackground7_2.png");
	backGround->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(backGround);

	MenuItemImage* stopButton = MenuItemImage::create("gamestopb.png",
													  "gamestopb.png",
													  CC_CALLBACK_0(TestScene::pause, this));

	Menu *stopmenu = Menu::create(stopButton, nullptr);
	stopmenu->setPosition(winSize.width - margin, winSize.height - margin);
	addChild(stopmenu);

	for (int i = 0; i < 12; i++) {
		circles_->createCircle();
	}

	gameTimer_ = 3;
	this->schedule(schedule_selector(TestScene::gameRunCounter), 1.0);

	return true;
}

void TestScene::update(float dt) {
	circles_->running();
}

void TestScene::gameTimerRunning(float dt) {
	gameTimer_--;
}

void TestScene::gameRunCounter(float dt) {
	Label* counterLabel = nullptr;
	string intToStr = "";

	counterLabel = (Label*)this->getChildByName("counterLabel");
	
	if (counterLabel == nullptr) {
		Size winSize = Director::getInstance()->getWinSize();
		TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
		counterLabel = Label::createWithTTF(ttfConfig, "3", TextHAlignment::CENTER);
		counterLabel->setPosition(winSize.width / 2, winSize.height / 2);
		counterLabel->setName("counterLabel");

		this->addChild(counterLabel, kLabelDepth);
	}

	intToStr = to_string(gameTimer_);
	counterLabel->setString(intToStr);

	if (gameTimer_ <= 0) {
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(TestScene::onTouchesBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(TestScene::onTouchesMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(TestScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

		this->removeChildByName("counterLabel");
		this->schedule(schedule_selector(TestScene::gameTimerRunning));
		this->unschedule(schedule_selector(TestScene::gameRunCounter));
		this->scheduleUpdate();
	}

	gameTimer_--;
}

void TestScene::circleInnerVisual(float dt) {
	auto innerCircle = circles_->getInnerCircles(touchMovePoints_);
	circles_->styleClear();

	for (auto circle : innerCircle) {
		circle->sprite->updateDisplayedColor(Color3B(0, 100, 0));
	}
}

void TestScene::circleBoom() {
	auto innerCircle = circles_->getInnerCircles(touchMovePoints_);

	if (innerCircle.size() == 3) {
		for (auto circle : innerCircle) {
			circles_->remove(circle);
		}

		string circleCount = to_string(circles_->getCircles().size());
		circleCountLabel_->setString(circleCount);
	}
}

void TestScene::pause() {

}

void TestScene::gameOver() {

}

bool TestScene::onTouchesBegan(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	auto touchStartPoint = Sprite::create("pointercircle.png");
	touchStartPoint->setColor(Color3B(0, 20, 255));
	touchStartPoint->setPosition(touchPosition);
	touchStartPoint->setName("startPoint");
	this->addChild(touchStartPoint);

	MotionStreak* streak = MotionStreak::create(0.5, 3, 50, Color3B::WHITE, "paddle.png");
	streak->setPosition(touchPosition);
	streak->setTag(123);
	addChild(streak);

	this->schedule(schedule_selector(TestScene::circleInnerVisual));

	return true;
}

void TestScene::onTouchesMoved(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	MotionStreak* streak = (MotionStreak*)this->getChildByTag(123);

	touchMovePoints_.push_back(touchPosition);

	streak->setPosition(touchPosition);
	touchMovePointSpr_->setPosition(touchPosition);
}

void TestScene::onTouchesEnded(Touch* touch, Event* event) {
	this->removeChildByTag(123);
	this->removeChildByName("startPoint");
	touchMovePointSpr_->setPosition(-10, -10);

	circleBoom();

	touchMovePoints_.clear();

	circles_->styleClear();

	this->unschedule(schedule_selector(TestScene::circleInnerVisual));
}