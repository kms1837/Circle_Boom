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
	const int kMaxiumCircleCount = 20; // 게임 종료 조건
	const int kStartCircleCount = 12; // 시작 구체 개수
	const int kBoomCount = 3; // 맞춰야 하는 구체 개수
	const int kDefaultPlusScore = 100; // 기본 추가 점수
	const int kClearScore = 120; // 구체 모두 터트렸을 경우 추가점수
	const int kComboScore = 10; // 콤보 가중 점수
	const int kUImargin = 40;
	const float kCreateInterval = 3.0f; // 구체등장 시간
	const float kComboDuration = 3.0f; // 콤보유지 시간

	enum class kSceneStatus:int {Normal, Pause};

	// UI
	cocos2d::Vec2 scoreUIPosition_;

	// flag
	bool dangerF_;
	int status_;

	// Scheduler
	void update(float dt);
	void gameTimer(float dt);
	void gameRunCounter(float dt);
	void comboTimer(float dt);
	void circleInnerVisual(float dt);
	void circleCreating(float dt);

	void gameRun(); // 게임 런타임 시작
	void gameResume(); // 게임재개 및 시작
	void circleBoom(); // 구체 폭팔
	void pause(); // 게임 정지
	void gameOver();
	void danger();

	void plusScoreAction(cocos2d::Vec2 startPoint, int plusScore);

	CircleManager* circles_;

	int score_;
	int combo_;
	int counter_;
	int playTime_; // 총 플레이한 시간
	int maxCombo_; // 최대 콤보

	cocos2d::Label* scoreLabel_;
	cocos2d::Label* circleCountLabel_;
	cocos2d::Sprite* touchMovePointSpr_;

	cocos2d::Vec2 prevTouchPoint_;

	std::list<cocos2d::Vec2> touchMovePoints_;

	CREATE_FUNC(TestScene);
};

#endif