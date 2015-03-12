#ifndef __GMAIN_H__
#define __GMAIN_H__

#include "cocos2d.h"
#include "Objectcircle.h"
#include "SimpleAudioEngine.h"

class MainScene: public cocos2d::LayerColor
{
public:
    CocosDenshion::SimpleAudioEngine *m_Sae;
    virtual bool init();
    virtual void onEnter();
    static cocos2d::Scene* scene();
    void menuClickCallback(cocos2d::Object* pSender);
    void mainFadeCircle(int fadetemp);
    void FadeCircle();
    void HellpPopUp();
    void GamEndPopUp();
    
    CREATE_FUNC(MainScene);

private:
	void MainLogic(float dt);
    void CircleMove(float dt);
    
protected:
    int mchantimer,mbacknum,mchangeback,mtimer;
};

class HelpLayer: public cocos2d::Layer
{
	public:
		virtual void onEnter();
		CocosDenshion::SimpleAudioEngine *m_Sae2;
		void helpClickCallback(cocos2d::Object* hSender);
		CREATE_FUNC(HelpLayer);

};

class GameEndLayer: public cocos2d::Layer
{
	public:
		virtual void onEnter();
		CocosDenshion::SimpleAudioEngine *m_Sae3;
		void EndClickCallback(cocos2d::Object* eSender);
		CREATE_FUNC(GameEndLayer);
};


#endif