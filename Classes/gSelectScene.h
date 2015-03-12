#ifndef __GSELECT_SCENE_H__
#define __GSELECT_SCENE_H__

//#include "cocos2d.h"
#include "gBackgroundManager.h"
#include "SimpleAudioEngine.h"


class gSelect: public cocos2d::LayerColor
{
	public:
    virtual bool init();
	static cocos2d::CCScene* scene();
	void menuClickCallback(cocos2d::Object* pSender);
	 CREATE_FUNC(gSelect);

	private:
	void SelectLogic(float dt);

};

#endif