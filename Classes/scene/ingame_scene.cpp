
#include "ingame_scene.h"

using namespace std;

USING_NS_CC;

InGameScene::InGameScene():
fontFilePath("fonts/NanumGothic.otf"),
kLabelFontSIze(40),
kLabelDepth(1),
kMaxiumCircleCount(40),
kStartCircleCount(12),
kBoomCount(3),
kDefaultPlusScore(100),
kClearScore(120),
kComboScore(10),
kUImargin(40),
kCreateInterval(3.0f),
kComboDuration(3.0f),

touchPointSpriteFileName("pointercircle.png"),
backgroundFilePath("background/Pbackground7_2.png"),
mouseStreakFileName("paddle.png"),
stopButtonFileNames{ "gamestopb.png", "gamestopb.png" },
homebuttonFileNames{ "homebutton.png", "testbuttonpush.png" },
replayButtonFileNames{"nextbutton.png", "testbuttonpush.png"},
resultPanelFileName("result.png"),
gameOverImgTextFileName("gameover.png"),
dangerLayerImageFilePath("layer/danger.png"),

counterLableName("counterLabel"),
dangerLayerName("dangerLayer"),
pauseLayerName("pauseLayer"),
gameoverLayerName("gameOverLayer"),
touchDrawLineName("drawLine"),
supportLineName("supportLine"),
startPointName("startPoint"),

_score(0),
_combo(0),
_maxCombo(0),
_playTime(0),
_dangerF(false),
_prevTouchPoint(Vec2(-1, -1)) {

}

InGameScene::~InGameScene() {
	
}

Scene* InGameScene::scene() {
    return InGameScene::create();
}

bool InGameScene::init() {

	if (!Scene::init()) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	_circleList = CircleManager::create(this);

	//Label Object
	TTFConfig ttfConfig(fontFilePath, kLabelFontSIze);
	auto scoreTitle = Label::createWithTTF(ttfConfig, "score: ", TextHAlignment::LEFT, winSize.width);
	scoreTitle->setPosition(kLabelFontSIze + kUImargin, winSize.height - 30);
	this->addChild(scoreTitle, kLabelDepth);

	_scoreLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 150);
	// issue - score Label size
	_scoreUIPosition = Vec2(300, winSize.height - kUImargin);
	_scoreLabel->setPosition(_scoreUIPosition);
	this->addChild(_scoreLabel, kLabelDepth);

	string circleCount = to_string(kStartCircleCount);

	_circleCountLabel = Label::createWithTTF(ttfConfig, circleCount, TextHAlignment::CENTER, winSize.width);
	_circleCountLabel->setPosition(winSize.width / 2, winSize.height - kUImargin);
	this->addChild(_circleCountLabel, kLabelDepth);

	//UI Object
	_touchMovePointSpr = Sprite::create(touchPointSpriteFileName);
	_touchMovePointSpr->setColor(Color3B(0, 20, 255));
	this->addChild(_touchMovePointSpr);

	Sprite* backGround = Sprite::create(backgroundFilePath);
	backGround->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(backGround);

	MenuItemImage* stopButton = MenuItemImage::create(
		stopButtonFileNames[0],
		stopButtonFileNames[1],
		CC_CALLBACK_0(InGameScene::pause, this));

	Menu* stopmenu = Menu::create(stopButton, nullptr);
	stopmenu->setPosition(winSize.width - kUImargin, winSize.height - kUImargin);
	addChild(stopmenu);

	for (int i = 0; i < kStartCircleCount; ++i) {
		_circleList->createCircle();
	}

	gameResume();

	return true;
}

void InGameScene::gameRun() {
	this->schedule(schedule_selector(InGameScene::gameTimer), 1.0);
	this->schedule(schedule_selector(InGameScene::circleCreating), kCreateInterval);
	this->scheduleUpdate();
}

void InGameScene::update(float dt) {
	_circleList->running();
}

void InGameScene::gameTimer(float dt) {
	_playTime++;
}

void InGameScene::gameRunCounter(float dt) {
	Label* counterLabel = nullptr;
	string intToStr = "";

	counterLabel = dynamic_cast<Label*>(getChildByName(counterLableName));
	
	if (counterLabel == nullptr) {
		Size winSize = Director::getInstance()->getWinSize();
		TTFConfig ttfConfig(fontFilePath, kLabelFontSIze);
		counterLabel = Label::createWithTTF(ttfConfig, "3", TextHAlignment::CENTER);
		counterLabel->setPosition(winSize.width / 2, winSize.height / 2);
		counterLabel->setName(counterLableName);

		this->addChild(counterLabel, kLabelDepth);
	}

	intToStr = to_string(_counter);
	counterLabel->setString(intToStr);

	if (_counter <= 0) {
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchesBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(InGameScene::onTouchesMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(InGameScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

		this->removeChildByName(counterLableName);
		gameRun();
		this->unschedule(schedule_selector(InGameScene::gameRunCounter));
	}

	--_counter;
}

void InGameScene::comboTimer(float dt) {
	this->unschedule(schedule_selector(InGameScene::comboTimer));
	_combo = 0;
}

void InGameScene::circleInnerVisual(float dt) {
	auto innerCircle = _circleList->getInnerCircles(_touchMovePoints);
	_circleList->styleClear();

	for (auto circle : innerCircle) {
		circle->getSprite()->updateDisplayedColor(Color3B(0, 100, 0));
	}
}

void InGameScene::circleCreating(float dt) {
	int circleCount = 0;

	for (int i = 0; i < kBoomCount; ++i) {
		_circleList->createCircle();
	}

	circleCount = _circleList->getSize();

	if (circleCount >= kMaxiumCircleCount) {
		gameOver();
	}

	int dangerCount = kMaxiumCircleCount - kStartCircleCount;

	if (circleCount >= dangerCount && !_dangerF) {
		_dangerF = true;
		danger();
	} else if (circleCount < dangerCount && _dangerF) {
		_dangerF = false;
		this->removeChildByName(dangerLayerName);
	}

	string circleCountStr = to_string(circleCount);
	_circleCountLabel->setString(circleCountStr);
}

void InGameScene::circleBoom() {
	auto innerCircle = _circleList->getInnerCircles(_touchMovePoints);

	if (innerCircle.size() == kBoomCount) {
		int comboScore;
		Size winSize = Director::getInstance()->getWinSize();
		for (auto circle : innerCircle) {
			plusScoreAction(circle->getSprite()->getPosition(), kDefaultPlusScore);
			_circleList->removeCircle(circle);
			_score += kDefaultPlusScore;
		}

		_combo++;

		comboScore = _combo >= 2 ? (_combo * kComboScore) : 0;

		_score += comboScore;
		string scoreStr = to_string(_score);
		_scoreLabel->setString(scoreStr);

		if (_combo >= 2) {
			TTFConfig ttfConfig(fontFilePath, kLabelFontSIze);
			string comboStr = to_string(_combo);
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

		if (_circleList->getSize() <= 0) {
			for (int i = 0; i < kStartCircleCount; ++i) {
				_circleList->createCircle();
			}

			_score += kClearScore;
			plusScoreAction(Vec2(winSize.width / 2, (winSize.height / 2) + 40), kClearScore);
		} // clear

		string circleCount = to_string(_circleList->getSize());
		_circleCountLabel->setString(circleCount);

		this->unschedule(schedule_selector(InGameScene::comboTimer));
		this->scheduleOnce(schedule_selector(InGameScene::comboTimer), kComboDuration);
	}
}

void InGameScene::danger() {
	Size winSize = Director::getInstance()->getWinSize();

	Layer* dangerLayer = Layer::create();
	dangerLayer->addChild(Sprite::create(dangerLayerImageFilePath));
	dangerLayer->setPosition(winSize.width/2, winSize.height/2);
	dangerLayer->setName(dangerLayerName);
	this->addChild(dangerLayer);
}

void InGameScene::pause() {
	if (static_cast<kSceneStatus>(_status) != kSceneStatus::Pause) {
		Size winSize = Director::getInstance()->getWinSize();

		this->unscheduleAllCallbacks();

		Layer* pauseLayer = LayerColor::create(Color4B(0, 0, 0, 100), winSize.width, winSize.height);

		MenuItemImage* homeButton = MenuItemImage::create(
			homebuttonFileNames[0],
			homebuttonFileNames[1],
			CC_CALLBACK_0(InGameScene::gameResume, this));

		MenuItemImage* resumeButton = MenuItemImage::create(
			resumeButtonFileNames[0],
			resumeButtonFileNames[1],
			CC_CALLBACK_0(InGameScene::gameResume, this));

		Menu* pauseMenu = Menu::create(homeButton, resumeButton, NULL);
		pauseMenu->alignItemsHorizontally();
		pauseLayer->addChild(pauseMenu);

		pauseLayer->setName(pauseLayerName);
		this->addChild(pauseLayer);

		_status = static_cast<int>(kSceneStatus::Pause);
	}
}

void InGameScene::gameResume() {
	this->removeChildByName(pauseLayerName);

	_counter = 3;
	this->schedule(schedule_selector(InGameScene::gameRunCounter), 1.0f);

	_status = static_cast<int>(kSceneStatus::Normal);
}

void InGameScene::gameOver() {
	Size winSize = Director::getInstance()->getWinSize();

	this->removeChildByName(dangerLayerName);

	Layer* gameOverLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	gameOverLayer->setName(gameoverLayerName);

	Sprite* popUpBack = Sprite::create(resultPanelFileName);
	popUpBack->setPosition(winSize.width / 2, winSize.height / 2);
	popUpBack->setOpacity(0);
	gameOverLayer->addChild(popUpBack, 1);

	Sprite* overTextImg = Sprite::create(gameOverImgTextFileName);
	overTextImg->setPosition(winSize.width / 2, winSize.height / 2);
	overTextImg->setOpacity(0);
	gameOverLayer->addChild(overTextImg, 10);

	TTFConfig ttfConfig(fontFilePath, kLabelFontSIze);
	Label* scoreLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 400);
	scoreLabel->setPosition(winSize.width / 2 + 100, winSize.height / 2 + 80);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setString(to_string(_score));
	scoreLabel->setOpacity(0);
	log("score:%d\n maxcombo:%d", _score, _maxCombo);
	//Size(400, 60)

	Label* playTimeLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 400);
	playTimeLabel->setPosition(winSize.width / 2 + 100, winSize.height / 2);
	playTimeLabel->setColor(Color3B::BLACK);
	playTimeLabel->setString(to_string(_playTime));
	playTimeLabel->setOpacity(0);

	Label* maxComboLabel = Label::createWithTTF(ttfConfig, "0", TextHAlignment::RIGHT, 400);
	maxComboLabel->setPosition(winSize.width / 2 + 100, winSize.height / 2 - 80);
	maxComboLabel->setColor(Color3B::BLACK);
	maxComboLabel->setString(to_string(_maxCombo));
	maxComboLabel->setOpacity(0);

	MenuItemImage *overhomeButton = MenuItemImage::create(
		homebuttonFileNames[0],
		homebuttonFileNames[1],
		CC_CALLBACK_0(InGameScene::gameResume, this));

	MenuItemImage* replayButton = MenuItemImage::create(
		replayButtonFileNames[0],
		replayButtonFileNames[1],
		CC_CALLBACK_0(InGameScene::gameResume, this));

	Menu* overMenu = Menu::create(overhomeButton, replayButton, NULL);
	overMenu->alignItemsHorizontally();
	overMenu->setOpacity(0);
	overMenu->setPosition(winSize.width / 2, winSize.height / 2 - 160);

	gameOverLayer->addChild(overMenu, 3);
	gameOverLayer->addChild(scoreLabel, 3);
	gameOverLayer->addChild(playTimeLabel, 3);
	gameOverLayer->addChild(maxComboLabel, 3);

	CallFunc* resultFade = CallFunc::create([&]() {
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
	_circleList->remove();
}

void InGameScene::plusScoreAction(Vec2 startPoint, int plusScore) {
	TTFConfig ttfConfig(fontFilePath, kLabelFontSIze);
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

bool InGameScene::onTouchesBegan(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	auto touchStartPoint = Sprite::create(touchPointSpriteFileName);
	touchStartPoint->setColor(Color3B(0, 20, 255));
	touchStartPoint->setPosition(touchPosition);
	touchStartPoint->setName(startPointName);
	this->addChild(touchStartPoint);

	auto touchLine = DrawNode::create();
	touchLine->setName(touchDrawLineName);
	addChild(touchLine);

	auto supportLine = DrawNode::create();
	supportLine->setName(supportLineName);
	addChild(supportLine);

	MotionStreak* streak = MotionStreak::create(0.5, 3, 50, Color3B::WHITE, mouseStreakFileName);
	streak->setPosition(touchPosition);
	streak->setTag(123);
	addChild(streak);

	this->schedule(schedule_selector(InGameScene::circleInnerVisual));

	return true;
}

void InGameScene::onTouchesMoved(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();

	MotionStreak* streak = dynamic_cast<MotionStreak*>(getChildByTag(123));

	auto touchLine = dynamic_cast<DrawNode*>(getChildByName(touchDrawLineName));
	auto supportLine = dynamic_cast<DrawNode*>(getChildByName(supportLineName));
	auto startPoint = this->getChildByName(startPointName);

	if (_prevTouchPoint.x != -1) {
		supportLine->clear();
		supportLine->drawLine(startPoint->getPosition(), touchPosition, Color4F::BLUE);
		touchLine->drawLine(_prevTouchPoint, touchPosition, Color4F::BLUE);
	}

	_prevTouchPoint = touchPosition;

	_touchMovePoints.push_back(touchPosition);

	streak->setPosition(touchPosition);
	_touchMovePointSpr->setPosition(touchPosition);
}

void InGameScene::onTouchesEnded(Touch* touch, Event* event) {
	this->removeChildByTag(123);
	this->removeChildByName(startPointName);
	this->removeChildByName(touchDrawLineName);
	this->removeChildByName(supportLineName);

	_touchMovePointSpr->setPosition(-10, -10);

	circleBoom();

	_touchMovePoints.clear();

	_circleList->styleClear();

	_prevTouchPoint = Vec2(-1, -1);

	this->unschedule(schedule_selector(InGameScene::circleInnerVisual));
}