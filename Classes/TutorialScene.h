#ifndef __CircleBoom_xcode___TutorialScene__
#define __CircleBoom_xcode___TutorialScene__

#include "cocos2d.h"
#include "ObjectCircle.h"

#define DONGTAG 99
#define MALTAG 100
#define TXTMALTAG 101
#define HELPIMGTAG 102
#define GUIDIMGTAG 103
#define STREAKTAG 104
#define LAYERTAG1 105

class TutorialScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    TutorialScene();
    
    CREATE_FUNC(TutorialScene);
    
private:
    virtual void touchesBegan(cocos2d::Set *touches, cocos2d::Event* event);
    virtual void touchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void touchesMoved(cocos2d::Set* touches, cocos2d::Event* event);
    void tutorialManagement(float dt);
    void inCircle(float dt);
    void inCircleColorChange(Objectcircle::Circle*  changeColorlist);
    void clearCircleColor(Objectcircle::Circle*  changeColorlist);
    
    int tutonum=1;
    int touchnum=1;
    int txtnum = 0;
    
    std::string mal_txt[10]={"Circle Boom을 플레이 해주셔서 감사합니다.",
                             "저는 게임의 진행방법을 설명해 드리러 온 동글이라고 합니다",
                             "그럼 지금부터 게임을 설명해드리겠습니다.",
                             "먼저 게임의 기본 룰 입니다.",
                             "그럼 한번 해보겠습니다",
                             };
    
    cocos2d::Size size;
    
    int _catchCount;
    
protected:
    Objectcircle::Circle* tutolist = NULL;
    std::string settingCircle = "tempcircle.png";
    
    unsigned int mousecoordinate[100][2];
    int coordinatecount = 0;
    
    //////////////////////////////////
    // Function
    
    int inpoly(unsigned int poly[][2], int npoints, int xt, int yt);

    
};

#endif