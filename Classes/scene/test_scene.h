#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "object\circle.h"
#include <list>

class TestScene: public cocos2d::Scene
{
// 인게임 실험 Scene입니다.
public:
	TestScene();
	~TestScene();
	static cocos2d::Scene* scene();

private:
	// Touch Event
	virtual bool init();
	virtual bool onTouchesBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchesMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// game set constant
	const std::string kLabelFont = "fonts/NanumGothic.otf";
	const int kLabelFontSIze = 40;
	const int kLabelDepth = 1;
	const int kMaxiumCircleCount = 50; // 게임 종료 조건

	//Scheduler
	void update(float dt);
	void gameTimerRunning(float dt);
	void gameRunCounter(float dt);
	void comboTimer(float dt);
	void circleInnerVisual(float dt);

	void circleBoom();
	void pause();
	void gameOver();

	Circle* circles_;

	int score_;
	int combo_;
	int gameTimer_;

	cocos2d::Label* scoreLabel_;
	cocos2d::Label* circleCountLabel_;
	cocos2d::Sprite* touchMovePointSpr_;

	std::list<cocos2d::Vec2> touchMovePoints_;

	CREATE_FUNC(TestScene);
};

#endif