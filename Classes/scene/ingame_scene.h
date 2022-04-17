#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "object\circle_manager.h"
#include <list>

class InGameScene: public cocos2d::Scene
{
// 인게임 실험 Scene입니다.
public:
	InGameScene();
	~InGameScene();
	static cocos2d::Scene* scene();

private:
	// Touch Event
	virtual bool init();
	virtual bool onTouchesBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchesMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// game set constant
	const std::string fontFilePath;
	const int kLabelFontSIze;
	const int kLabelDepth;
	const int kMaxiumCircleCount; // 게임 종료 조건
	const int kStartCircleCount; // 시작 구체 개수
	const int kBoomCount; // 맞춰야 하는 구체 개수
	const int kDefaultPlusScore; // 기본 추가 점수
	const int kClearScore; // 구체 모두 터트렸을 경우 추가점수
	const int kComboScore; // 콤보 가중 점수
	const int kUImargin;
	const float kCreateInterval; // 구체등장 시간
	const float kComboDuration; // 콤보유지 시간

	enum class kSceneStatus:int { Normal, Pause };

	// UI constant
	const std::string touchPointSpriteFileName;
	const std::string backgroundFilePath;
	const std::string mouseStreakFileName;

	const std::string stopButtonFileNames[2];
	const std::string homebuttonFileNames[2];
	const std::string resumeButtonFileNames[2];
	const std::string replayButtonFileNames[2];

	const std::string resultPanelFileName;
	const std::string gameOverImgTextFileName;
	const std::string dangerLayerImageFilePath;

	// UI
	cocos2d::Vec2 _scoreUIPosition;
	cocos2d::Label* _scoreLabel;
	cocos2d::Label* _circleCountLabel;
	cocos2d::Sprite* _touchMovePointSpr;

	std::string counterLableName;
	std::string dangerLayerName;
	std::string pauseLayerName;
	std::string gameoverLayerName;

	std::string touchDrawLineName;
	std::string supportLineName;
	std::string startPointName;

	// flag
	bool _dangerF;
	int _status;

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

	CircleManager* _circleList;

	int _score;
	int _combo;
	int _counter;
	int _playTime; // 총 플레이한 시간
	int _maxCombo; // 최대 콤보

	cocos2d::Vec2 _prevTouchPoint;

	std::list<cocos2d::Vec2> _touchMovePoints;

	CREATE_FUNC(InGameScene);
};

#endif