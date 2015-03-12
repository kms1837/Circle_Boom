#ifndef __CircleBoom_xcode___GameMain__
#define __CircleBoom_xcode___GameMain__

#include "cocos2d.h"
#include "Objectcircle.h"
#include "SimpleAudioEngine.h"
#include "InGameScene.h"
#include "OptionScene.h"
#include "Management.h"


#define SETTING   1
#define GAMESTART 2
#define HELP      3

#define HELPNEXT  1
#define HELPPREV  2

#define CANCEL    3
#define EXIT      4

#define HELPPOPLAYERTAG 100
#define ENDPOPLAYERTAG 101

class GameMain : public cocos2d::Scene
{
public:
    //GameMain();
    //~GameMain();
    virtual bool init();
    
    static cocos2d::Scene* scene();
    void HelpPopup();
    void EndPopup();
    
    CREATE_FUNC(GameMain);
    
private:
	void MainCircleMoveLogic(float dt);
    void MainClickCallback(cocos2d::Object* pSender);
    void HelpClickCallback(cocos2d::Object* pSender);
    void EndClickCallback(cocos2d::Object* pSender);
    
protected:
    int helpnum=1, maxhelpnum=3;
    cocos2d::Size size;
};

#endif
