#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "object\circle.h"

class TestScene: public cocos2d::Scene
{
// 인게임 실험 Scene입니다.
public:
	TestScene();
	~TestScene();
	static cocos2d::Scene* scene();

private:
	virtual bool init();
	virtual bool onTouchesBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchesMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void update(float dt);

	Circle* circles_;

	int score_;
	int combo_;

	CREATE_FUNC(TestScene);
};

#endif