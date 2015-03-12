#ifndef __CircleBoom_xcode___PlayGame__
#define __CircleBoom_xcode___PlayGame__

#include "ObjectCircle.h"
#include "EfeectQueue.h"
#include "cocos-ext.h"
#include <math.h>

#define GAMESTOP 1

#define RESULTGAME 1
#define HOME 2
#define REPLAY 3

#define catchCount 3 //묶어야할 구체수

#define GAMESTOPLAYERTAG 201
#define GAMEOVERLAYERTAG    202
#define GAMEDENGERLAYERTAG  203

#define COMBOLABELTAG 204
#define SCORELABELTAG 205

class InGameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    static cocos2d::Scene* scene();

    //void touchNamo();
    void StopMenuCallback(cocos2d::Object* pSender);
    void OverMenuCallback(cocos2d::Object* pSender);

    CREATE_FUNC(InGameScene);
    
private:
    
    //////////////////////////////
    //Touch Event
    virtual void touchesBegan(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void touchesMoved(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void touchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
    
    //////////////////////////////
    //Schedule & Function
    void CircleCreate(float dt);//구체생성 스케줄러
    void CircleMove(float dt);//구체이동 스케줄러
    void inCircle(float dt);//구체가 안에들어오면 색바꿔주기 스케줄러
    void inCircleColorChange(Objectcircle::Circle* changeColorlist);//안에들어오면 색을 바꿔준다.
    void allCircleColorChange(Objectcircle::Circle* changeColorlist, cocos2d::Color3B settingcolor);//리스트의 모든 객체의 색상을 바꾸기위한 함수
    
    void EffectDequeue(float dt);//이펙트삭제 스케줄러
    void EndEffectPlay(float dt);//게임오버시 이펙트생성, 리스트삭제 스케줄러
    void EffectCreate(int x, int y);//이펙트 생성 함수
    
    void GameCount(float dt);//정지해제시 카운트 스케줄러
    void GameCountStart();
    
    void ComboLabelMove(float dt);//연출
    void ComboLabelCreate(int x, int y);
    void ComboCenterLabelPlay();//중앙 콤보수 연출 함수
    
    void GameStop(); //게임정지처리
    void GameOver(); //게임오버처리
    void GameDenger(); //게임위험처리
    
    void ComboTimer(float dt); //콤보타이머
    
    void feverTimer(float dt);
    
    void allFadeRemoveFeverCircle(float dt); //모든 구체를 페이드아웃으로 삭제 스케줄러(피버구체전용)
    //bool updateFadeRemoveCircle(Objectcircle::Circle* fadenode);
    
    int inpoly(unsigned int poly[][2], int npoints, int xt, int yt); //다각형 내부 점 인식
    
protected:
    
    //////////////////////////////
    //List
    Objectcircle::Circle* list = NULL;                          //구체리스트
    Objectcircle::Circle* moveList = NULL;                      //구체를 움직이기 위한 리스트
    Objectcircle::Circle* countList = NULL;
    Objectcircle::Circle* feverlist = NULL;                     //피버구체 리스트
    Objectcircle::ComboLabelNode* comboLabelList = NULL;        //콤보연출을 위한 리스트
    Objectcircle::ComboLabelNode* comboMoveLabelList = NULL;
    EffectQueue::QueueList* queuelist = NULL;                   //파티클 리스트 큐
    
    //////////////////////////////
    //switch
    int gamestopS;      //게임정지여부
    int gamedengerS;    //게임위험표시여부
    int boomcircleS;    //버그방지
    int feverswitch;    //피버여부
    
    //////////////////////////////
    //game setting
    int gameOverMaxCircle   = cocos2d::UserDefault::sharedUserDefault()->getIntegerForKey("gameOverCircle");        //게임오버조건
    int setcombotimer       = cocos2d::UserDefault::sharedUserDefault()->getIntegerForKey("gameComboTimer") * 60;   //콤보시간
    int setfevernum         = 5;//피버조건
    
    //////////////////////////////
    //other
    unsigned int testt[100][2];
    int testc = 0;
    int gameCountNum; //게임카운터
    
    int combotimer = 0;//콤보 타이머
    int combonum = 0; //게임콤보
    
    int gamescore = 0; //게임스코어
    int maxcombo = 0; //최대콤보
    int playtime = 0; //플레이타임
    
    int fevertimernum = 0;
    
    cocos2d::MotionStreak *streak; //터치시 잔상
    cocos2d::Size size;            //게임 사이즈
    
    //////////////////////////////
    //Timer
    //float createTimer = 3.0f; //구체등장 시간 설정
    float createTimer   = cocos2d::UserDefault::sharedUserDefault()->getFloatForKey("createSpeed");
    int setDistance     = cocos2d::UserDefault::sharedUserDefault()->getIntegerForKey("distance");
   
};

#endif
