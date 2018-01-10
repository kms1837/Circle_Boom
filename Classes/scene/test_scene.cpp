
#include "test_scene.h"

using namespace std;

USING_NS_CC;

TestScene::TestScene():
score_(0),
combo_(0),
gameTimer_(0),
dengerF_(false),
prevTouchPoint_(Vec2(-1, -1)) {

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
	circles_ = CircleManager::create(this);

	//Label Object
	TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
	auto scoreTitle = Label::createWithTTF(ttfConfig, "score: ", TextHAlignment::LEFT, winSize.width);
	scoreTitle->setPosition(kLabelFontSIze + kUImargin, winSize.height - 30);
	scoreTitle->setName("scoreLabel");
	this->addChild(scoreTitle, kLabelDepth);

	scoreLabel_ = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 150);
	// issue - score Label size
	scoreUIPosition_ = Vec2(300, winSize.height - kUImargin);
	scoreLabel_->setPosition(scoreUIPosition_);
	scoreLabel_->setName("scoreLabel");
	this->addChild(scoreLabel_, kLabelDepth);

	string circleCount = to_string(kStartCircleCount);

	circleCountLabel_ = Label::createWithTTF(ttfConfig, circleCount, TextHAlignment::CENTER, winSize.width);
	circleCountLabel_->setPosition(winSize.width / 2, winSize.height - kUImargin);
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
	stopmenu->setPosition(winSize.width - kUImargin, winSize.height - kUImargin);
	addChild(stopmenu);

	for (int i = 0; i < kStartCircleCount; i++) {
		circles_->createCircle();
	}

	gameTimer_ = 3;
	this->schedule(schedule_selector(TestScene::gameRunCounter), 1.0);

	return true;
}

void TestScene::gameRun() {
	this->schedule(schedule_selector(TestScene::gameTimerRunning));
	this->schedule(schedule_selector(TestScene::circleCreating), kCreateInterval);
	this->scheduleUpdate();
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
		gameRun();
		this->unschedule(schedule_selector(TestScene::gameRunCounter));
	}

	gameTimer_--;
}

void TestScene::comboTimer(float dt) {
	this->unschedule(schedule_selector(TestScene::comboTimer));
	combo_ = 0;
}

void TestScene::circleInnerVisual(float dt) {
	auto innerCircle = circles_->getInnerCircles(touchMovePoints_);
	circles_->styleClear();

	for (auto circle : innerCircle) {
		circle->sprite->updateDisplayedColor(Color3B(0, 100, 0));
	}
}

void TestScene::circleCreating(float dt) {
	int circleCount = 0;

	for (int i = 0; i < kBoomCount; i++) {
		circles_->createCircle();
	}

	circleCount = circles_->getSize();

	if (circleCount >= kMaxiumCircleCount) {
		gameOver();
	}

	if (circleCount >= kMaxiumCircleCount - kStartCircleCount && !dengerF_) {
		dengerF_ = true;
		denger();
	} else if (circleCount < kMaxiumCircleCount - kStartCircleCount && dengerF_) {
		dengerF_ = false;
		//this->removeChildByTag(GAMEDENGERLAYERTAG);
	}

	string circleCountStr = to_string(circleCount);
	circleCountLabel_->setString(circleCountStr);
}

void TestScene::circleBoom() {
	auto innerCircle = circles_->getInnerCircles(touchMovePoints_);

	if (innerCircle.size() == kBoomCount) {
		int comboScore;
		Size winSize = Director::getInstance()->getWinSize();
		for (auto circle : innerCircle) {
			plusScoreAction(circle->sprite->getPosition(), kDefaultPlusScore);
			circles_->removeCircle(circle);
			score_ += kDefaultPlusScore;
		}

		combo_++;

		comboScore = (combo_ * kComboScore);

		score_ += comboScore;
		string scoreStr = to_string(score_);
		scoreLabel_->setString(scoreStr);

		if (circles_->getSize() <= 0) {
			for (int i = 0; i < kStartCircleCount; i++) {
				circles_->createCircle();
			}
		}

		string circleCount = to_string(circles_->getSize());
		circleCountLabel_->setString(circleCount);

		plusScoreAction(Vec2(winSize.width/2, winSize.height/2), comboScore);

		this->unschedule(schedule_selector(TestScene::comboTimer));
		this->scheduleOnce(schedule_selector(TestScene::comboTimer), kComboDuration);
	}
}

void TestScene::denger() {

}

void TestScene::pause() {

}

void TestScene::gameOver() {
	this->unscheduleAllSelectors();
	//circles_->remove();
}

void TestScene::plusScoreAction(Vec2 startPoint, int plusScore) {
	TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
	string plusScoreStr = to_string(plusScore);
	Label* comboScoreLabel = Label::createWithTTF(ttfConfig, plusScoreStr, TextHAlignment::CENTER, 100);
	comboScoreLabel->setPosition(startPoint);
	this->addChild(comboScoreLabel);

	auto removeLabel = CallFunc::create([this, comboScoreLabel]() {
		this->removeChild(comboScoreLabel);
	});

	auto sequence = Sequence::create(FadeOut::create(0.5f),
									 removeLabel, nullptr);

	comboScoreLabel->runAction(MoveTo::create(0.5f, scoreUIPosition_));
	comboScoreLabel->runAction(sequence);
}

bool TestScene::onTouchesBegan(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	auto touchStartPoint = Sprite::create("pointercircle.png");
	touchStartPoint->setColor(Color3B(0, 20, 255));
	touchStartPoint->setPosition(touchPosition);
	touchStartPoint->setName("startPoint");
	this->addChild(touchStartPoint);

	auto touchLine = DrawNode::create();
	touchLine->setName("drawLine");
	addChild(touchLine);

	auto supportLine = DrawNode::create();
	supportLine->setName("supportLine");
	addChild(supportLine);

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

	auto touchLine = (DrawNode*)this->getChildByName("drawLine");
	auto supportLine = (DrawNode*)this->getChildByName("supportLine");
	auto startPoint = this->getChildByName("startPoint");

	if (prevTouchPoint_.x != -1) {
		supportLine->clear();
		supportLine->drawLine(startPoint->getPosition(), touchPosition, Color4F::BLUE);
		touchLine->drawLine(prevTouchPoint_, touchPosition, Color4F::BLUE);
	}

	prevTouchPoint_ = touchPosition;

	touchMovePoints_.push_back(touchPosition);

	streak->setPosition(touchPosition);
	touchMovePointSpr_->setPosition(touchPosition);
}

void TestScene::onTouchesEnded(Touch* touch, Event* event) {
	this->removeChildByTag(123);
	this->removeChildByName("startPoint");
	this->removeChildByName("drawLine");
	this->removeChildByName("supportLine");

	touchMovePointSpr_->setPosition(-10, -10);

	circleBoom();

	touchMovePoints_.clear();

	circles_->styleClear();

	prevTouchPoint_ = Vec2(-1, -1);

	this->unschedule(schedule_selector(TestScene::circleInnerVisual));
}