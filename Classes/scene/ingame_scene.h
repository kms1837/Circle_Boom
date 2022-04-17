#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "object\circle_manager.h"
#include <list>

class InGameScene: public cocos2d::Scene
{
// �ΰ��� ���� Scene�Դϴ�.
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
	const int kMaxiumCircleCount; // ���� ���� ����
	const int kStartCircleCount; // ���� ��ü ����
	const int kBoomCount; // ����� �ϴ� ��ü ����
	const int kDefaultPlusScore; // �⺻ �߰� ����
	const int kClearScore; // ��ü ��� ��Ʈ���� ��� �߰�����
	const int kComboScore; // �޺� ���� ����
	const int kUImargin;
	const float kCreateInterval; // ��ü���� �ð�
	const float kComboDuration; // �޺����� �ð�

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

	void gameRun(); // ���� ��Ÿ�� ����
	void gameResume(); // �����簳 �� ����
	void circleBoom(); // ��ü ����
	void pause(); // ���� ����
	void gameOver();
	void danger();

	void plusScoreAction(cocos2d::Vec2 startPoint, int plusScore);

	CircleManager* _circleList;

	int _score;
	int _combo;
	int _counter;
	int _playTime; // �� �÷����� �ð�
	int _maxCombo; // �ִ� �޺�

	cocos2d::Vec2 _prevTouchPoint;

	std::list<cocos2d::Vec2> _touchMovePoints;

	CREATE_FUNC(InGameScene);
};

#endif