#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"

class IntroScene: public cocos2d::Scene
{
public:
	static cocos2d::Scene* scene();
	virtual bool init();
	CREATE_FUNC(IntroScene);
};

#endif