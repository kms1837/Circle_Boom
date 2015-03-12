#ifndef HELLOWORLD_SCENE_H
#define HELLOWORLD_SCENE_H

#include "Objectcircle.h"
#include "SimpleAudioEngine.h"

class Playgame : public cocos2d::LayerColor
{
public:
    
    Playgame();
    
    virtual bool init();
    virtual void touchesBegan(cocos2d::Set *touches, cocos2d::Event* event);
    virtual void touchesMoved(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void touchesEnded(cocos2d::Set* touches, cocos2d::Event* event);

    static cocos2d::Scene* scene();

    void fristgamemmm();
    void boomParticles(int px, int py);
    void menuClickCallback(cocos2d::Object* pSender);
    //void FadeCircle(int fadetemp, int colortemp);
    void FadeCircle();
    void gameover();
    CocosDenshion::SimpleAudioEngine *m_Sae;
    CREATE_FUNC(Playgame);

private:
    void GameLogic(float dt);

protected:
    cocos2d::MotionStreak *streak;
};

class GameStopLayer : public cocos2d::LayerColor
{
	public:
		virtual void onEnter();
		void StopClickCallback(cocos2d::Object* stopSender);
		CREATE_FUNC(GameStopLayer);
};

class GameOverLayer : public cocos2d::LayerColor
{
	public:
		virtual void onEnter();
		CREATE_FUNC(GameOverLayer);
};

class GameClearLayer : public cocos2d::LayerColor
{
	public:
		virtual void onEnter();
		CREATE_FUNC(GameClearLayer);
};

#endif  // __HELLOWORLD_SCENE_H__

