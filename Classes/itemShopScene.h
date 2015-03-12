#ifndef __GSHOP_SCENE_H__
#define __GSHOP_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class ItemShopScene: public cocos2d::LayerColor
{
	public:
    virtual bool init();
	static cocos2d::Scene* scene();
	void menuClickCallback(cocos2d::Object* pSender);
	CREATE_FUNC(ItemShopScene);

};

#endif