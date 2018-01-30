
#include "test_scene.h"

using namespace std;

USING_NS_CC;

TestScene::TestScene():
score_(0),
combo_(0),
maxCombo_(0),
playTime_(0),
dangerF_(false),
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
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/SHORT_BGM_09.mp3");
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

	gameResume();

	return true;
}

void TestScene::gameRun() {
	this->schedule(schedule_selector(TestScene::gameTimer), 1.0);
	this->schedule(schedule_selector(TestScene::circleCreating), kCreateInterval);
	this->scheduleUpdate();
}

void TestScene::update(float dt) {
	circles_->running();
}

void TestScene::gameTimer(float dt) {
	playTime_++;
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

	intToStr = to_string(counter_);
	counterLabel->setString(intToStr);

	if (counter_ <= 0) {
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(TestScene::onTouchesBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(TestScene::onTouchesMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(TestScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

		this->removeChildByName("counterLabel");
		gameRun();
		this->unschedule(schedule_selector(TestScene::gameRunCounter));
	}

	counter_--;
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

	if (circleCount >= kMaxiumCircleCount - kStartCircleCount && !dangerF_) {
		dangerF_ = true;
		danger();
	} else if (circleCount < kMaxiumCircleCount - kStartCircleCount && dangerF_) {
		dangerF_ = false;
		this->removeChildByName("dangerLayer");
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

		comboScore = combo_ >= 2 ? (combo_ * kComboScore) : 0;

		score_ += comboScore;
		string scoreStr = to_string(score_);
		scoreLabel_->setString(scoreStr);

		if (combo_ >= 2) {
			TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
			string comboStr = to_string(combo_);
			comboStr.append(" combo");
			Label* comboLabel = Label::createWithTTF(ttfConfig, comboStr, TextHAlignment::CENTER, 200);
			comboLabel->setPosition(winSize.width / 2, winSize.height / 2);
			this->addChild(comboLabel);

			auto removeComboLabel = CallFunc::create([this, comboLabel]() {
				this->removeChild(comboLabel);
			});

			Sequence* sequence = Sequence::create(FadeOut::create(1),
				removeComboLabel, nullptr);

			comboLabel->runAction(sequence);

			plusScoreAction(Vec2(winSize.width / 2, (winSize.height / 2) - 40), comboScore);
		}

		if (circles_->getSize() <= 0) {
			for (int i = 0; i < kStartCircleCount; i++) {
				circles_->createCircle();
			}

			score_ += kClearScore;
			plusScoreAction(Vec2(winSize.width / 2, (winSize.height / 2) + 40), kClearScore);
		} // clear

		string circleCount = to_string(circles_->getSize());
		circleCountLabel_->setString(circleCount);

		this->unschedule(schedule_selector(TestScene::comboTimer));
		this->scheduleOnce(schedule_selector(TestScene::comboTimer), kComboDuration);
	}
}

void TestScene::danger() {
	Size winSize = Director::getInstance()->getWinSize();

	Layer* dangerLayer = Layer::create();
	dangerLayer->addChild(Sprite::create("layer/danger.png"));
	dangerLayer->setPosition(winSize.width/2, winSize.height/2);
	dangerLayer->setName("dangerLayer");
	this->addChild(dangerLayer);
}

void TestScene::pause() {
	if (static_cast<kSceneStatus>(status_) != kSceneStatus::Pause) {
		Size winSize = Director::getInstance()->getWinSize();

		this->unscheduleAllCallbacks();

		Layer* pauseLayer = LayerColor::create(Color4B(0, 0, 0, 100), winSize.width, winSize.height);

		MenuItemImage *homeButton = MenuItemImage::create("homebutton.png",
			"testbuttonpush.png",
			CC_CALLBACK_0(TestScene::gameResume, this));

		MenuItemImage *resumeButton = MenuItemImage::create("returnbutton.png",
			"testbuttonpush.png",
			CC_CALLBACK_0(TestScene::gameResume, this));

		Menu* pauseMenu = Menu::create(homeButton, resumeButton, NULL);
		pauseMenu->alignItemsHorizontally();
		pauseLayer->addChild(pauseMenu);

		pauseLayer->setName("pauseLayer");
		this->addChild(pauseLayer);

		status_ = static_cast<int>(kSceneStatus::Pause);
	}
}

void TestScene::gameResume() {
	this->removeChildByName("pauseLayer");

	counter_ = 3;
	this->schedule(schedule_selector(TestScene::gameRunCounter), 1.0f);

	status_ = static_cast<int>(kSceneStatus::Normal);
}

void TestScene::gameOver() {
	Size winSize = Director::getInstance()->getWinSize();

	this->removeChildByName("dangerLayer");

	Layer* gameOverLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	gameOverLayer->setName("gameOverLayer");

	Sprite* popUpBack = Sprite::create("result.png");
	popUpBack->setPosition(winSize.width / 2, winSize.height / 2);
	popUpBack->setOpacity(0);
	gameOverLayer->addChild(popUpBack, 1);

	Sprite* overTextImg = Sprite::create("gameover.png");
	overTextImg->setPosition(winSize.width / 2, winSize.height / 2);
	overTextImg->setOpacity(0);
	gameOverLayer->addChild(overTextImg, 10);

	TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
	Label* scoreLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 400);
	scoreLabel->setPosition(winSize.width / 2 + 100, winSize.height / 2 + 80);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setString(to_string(score_));
	scoreLabel->setOpacity(0);
	log("score:%d\n maxcombo:%d", score_, maxCombo_);
	//Size(400, 60)

	Label* playTimeLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 400);
	playTimeLabel->setPosition(winSize.width / 2 + 100, winSize.height / 2);
	playTimeLabel->setColor(Color3B::BLACK);
	playTimeLabel->setString(to_string(playTime_));
	playTimeLabel->setOpacity(0);

	Label* maxComboLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 400);
	maxComboLabel->setPosition(winSize.width / 2 + 100, winSize.height / 2 - 80);
	maxComboLabel->setColor(Color3B::BLACK);
	maxComboLabel->setString(to_string(maxCombo_));
	maxComboLabel->setOpacity(0);

	MenuItemImage *overhomeButton = MenuItemImage::create("homebutton.png",
		"testbuttonpush.png",
		CC_CALLBACK_0(TestScene::gameResume, this));

	MenuItemImage *replayButton = MenuItemImage::create("nextbutton.png",
		"testbuttonpush.png",
		CC_CALLBACK_0(TestScene::gameResume, this));

	Menu* overMenu = Menu::create(overhomeButton, replayButton, NULL);
	overMenu->alignItemsHorizontally();
	overMenu->setOpacity(0);
	overMenu->setPosition(winSize.width / 2, winSize.height / 2 - 160);

	gameOverLayer->addChild(overMenu, 3);
	gameOverLayer->addChild(scoreLabel, 3);
	gameOverLayer->addChild(playTimeLabel, 3);
	gameOverLayer->addChild(maxComboLabel, 3);

	CallFunc* resultFade = CallFunc::create([=]() {
		popUpBack->runAction(FadeIn::create(1.0));
		overMenu->runAction(FadeIn::create(1.0));
		scoreLabel->runAction(FadeIn::create(1.0));
		playTimeLabel->runAction(FadeIn::create(1.0));
		maxComboLabel->runAction(FadeIn::create(1.0));
	});

	overTextImg->runAction(
		Sequence::create(FadeIn::create(1.0),
		DelayTime::create(1.0),
		FadeOut::create(1.0),
		resultFade,
		NULL)
	);
	
	this->addChild(gameOverLayer);

	this->unscheduleAllCallbacks();
	circles_->remove();
}

void TestScene::plusScoreAction(Vec2 startPoint, int plusScore) {
	TTFConfig ttfConfig(kLabelFont, kLabelFontSIze);
	string plusScoreStr("+");
	plusScoreStr.append(to_string(plusScore));
	Label* comboScoreLabel = Label::createWithTTF(ttfConfig, plusScoreStr, TextHAlignment::CENTER, 100);
	Vec2 endPoint(startPoint.x, startPoint.y + 20);
	comboScoreLabel->setPosition(startPoint);
	this->addChild(comboScoreLabel);

	auto removeLabel = CallFunc::create([this, comboScoreLabel]() {
		this->removeChild(comboScoreLabel);
	});

	Sequence* sequence = Sequence::create(FadeOut::create(1),
										  removeLabel, nullptr);

	comboScoreLabel->runAction(MoveTo::create(1, endPoint));
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