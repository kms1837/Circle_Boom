#ifndef __GINTRO_SCENE_H__
#define __GINTRO_SCENE_H__

#include "cocos2d.h"
#include "Objectcircle.h"
#include "SimpleAudioEngine.h"

class IntroScene: public cocos2d::LayerColor
{
public:
    virtual bool init();
	virtual void onEnter();
	void sceneReplace();
	static cocos2d::Scene* scene();
	CREATE_FUNC(IntroScene);

};

#endif