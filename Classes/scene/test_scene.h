#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "object\circle_manager.h"
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
	const int kStartCircleCount = 12; // 시작 구체 개수
	const int kBoomCount = 3; // 맞춰야 하는 구체 개수
	const int kDefaultPlusScore = 100; // 기본 추가 점수
	const int kComboScore = 10; // 콤보 가중 점수
	const int kUImargin = 40;
	const float kCreateInterval = 3.0f; // 구체등장 시간
	const float kComboDuration = 3.0f; // 콤보유지 시간

	// UI
	cocos2d::Vec2 scoreUIPosition_;

	// flag
	bool dengerF_;

	// Scheduler
	void update(float dt);
	void gameTimerRunning(float dt);
	void gameRunCounter(float dt);
	void comboTimer(float dt);
	void circleInnerVisual(float dt);
	void circleCreating(float dt);

	void gameRun();
	void circleBoom();
	void pause();
	void gameOver();
	void denger();

	void plusScoreAction(cocos2d::Vec2 startPoint, int plusScore);

	CircleManager* circles_;

	int score_;
	int combo_;
	int gameTimer_;

	cocos2d::Label* scoreLabel_;
	cocos2d::Label* circleCountLabel_;
	cocos2d::Sprite* touchMovePointSpr_;

	cocos2d::Vec2 prevTouchPoint_;

	std::list<cocos2d::Vec2> touchMovePoints_;

	CREATE_FUNC(TestScene);
};

#endif