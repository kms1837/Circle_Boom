#ifndef __GTEST_SCENE_H__
#define __GTEST_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

/* 테스트용으로 마련된 씬입니다 실제 게임에선 사용되지 않습니다.*/
class TestScene: public cocos2d::LayerColor
{
    
public:
    virtual bool init();
	static cocos2d::Scene* scene();
	CREATE_FUNC(TestScene);
};

#endif