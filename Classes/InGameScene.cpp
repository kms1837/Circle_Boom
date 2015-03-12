#include "InGameScene.h"
#include "GameMain.h"

using namespace cocos2d;
using namespace std;

//=====================================================================================
//                                      게임규칙
//
//                  - 구체는 일정시간이 되면 3개씩 등장한다.(default:3s)
//                  - 구체가 모두 사라지면 보너스점수를 주고 9개를 생성한다.
//                  - 구체가 게임화면 이상,이하로 넘어가면 이동위치를 반전시킨다.
//                  - 귀찮귀찮 ㅎㅎㅎㅎㅎ
//                  - 졸리다ㅠㅠ
//
//=====================================================================================

//참고:polygon clipping convex concave 구글링
//http://visibone.com/inpoly/
//http://kldp.org/node/65088

LabelTTF* circleCount = NULL;
LabelTTF* gameCountLabel = NULL;

std::string settingCircle = "tempcircle.png";

#pragma mark- 초기화

Scene* InGameScene::scene()
{
    Scene* gameScene = Scene::create();
    InGameScene* Game_layer = InGameScene::create();
    
	gameScene->addChild(Game_layer);
    return gameScene;
}

bool InGameScene::init()
{
    
    size = Director::sharedDirector()->getVisibleSize();
    
    Sprite* backGround = Sprite::create("Pbackground7_2.png");
    backGround->setPosition(size.width/2,size.height/2);
    addChild(backGround);
    
    MenuItemImage* stopButton = MenuItemImage::create("gamestopb.png",
                                                      "gamestopb.png",
                                                      CC_CALLBACK_0(InGameScene::GameStop, this));
    
    Menu *stopmenu = Menu::create(stopButton, nullptr);
    
    stopmenu->setPosition(50,size.height-40);
    addChild(stopmenu);
    //stopMenu
    
    circleCount = LabelTTF::create("0", "맑은 고딕", 60);
    circleCount->setPosition(size.width-40, 40);
    circleCount->setColor(Color3B(255,255,255));
    addChild(circleCount,2);
    
    LabelTTF* comboLabel = LabelTTF::create("0", "맑은 고딕", 80);
    comboLabel->setPosition(size.width/2, size.height/2);
    comboLabel->setTag(COMBOLABELTAG);
    comboLabel->setColor(Color3B(255,255,255));
    comboLabel->setOpacity(0);
    addChild(comboLabel, 5);
    //Combo Label
    
    LabelTTF* scoreLabel = LabelTTF::create("0", "맑은 고딕", 50, CCSizeMake(400, 100), kCCTextAlignmentRight);
    scoreLabel->setPosition(size.width-300, size.height-80);
    scoreLabel->setColor(Color3B(255,255,255));
    scoreLabel->setTag(SCORELABELTAG);
    addChild(scoreLabel, 5);
    //Score Label
    
    setTouchEnabled(true);
    
    return true;
}

void InGameScene::onEnter()
{
    Layer::onEnter();
    Objectcircle temp;
    
    gamestopS=1; //카운트를 위해 처음에 멈추게 설정
    gamedengerS=0;
    list=NULL;
    gameCountNum = 3;
    char tempstring[20]={0,};
    
    for(int i=1;i<=12;i++) temp.FadeCircle(&list, this, settingCircle); //첫 화면을 불러올시 생성할 구체
    
    
    sprintf(tempstring, "%d", temp.GetCircleCount(list));
    circleCount->setString(tempstring);
    
    moveList  = list;
    countList = list;
    
    GameCountStart();
    schedule(schedule_selector(InGameScene::CircleMove));
    schedule(schedule_selector(InGameScene::CircleCreate),createTimer);
    
}

#pragma mark- 스케쥴

void InGameScene::CircleMove(float dt)
{
    float tempX, tempY;
    float spriteSizeW, spriteSizeH;
    if(gamestopS==0&&boomcircleS==0&&feverswitch==0){
        Objectcircle temp;
        while(list!=NULL){
            tempX = moveList->Mcir->getPositionX();
            tempY = moveList->Mcir->getPositionY();
            
            spriteSizeW = moveList->Mcir->getContentSize().width/2;
            spriteSizeH = moveList->Mcir->getContentSize().height/2;
                        
            if(tempX + spriteSizeW >size.width|| tempX - spriteSizeW<0){
                moveList->moveX*=-1;
                moveList->moveSpeed = rand()%4+1;
                moveList->timer = 60;
                temp.FlipCircle(moveList->Mcir, moveList->moveX);
            }
            
            if(tempY + spriteSizeH>size.height || tempY - spriteSizeH<0){
                moveList->moveY*=-1;
                moveList->moveSpeed = rand()%4+1;
                moveList->timer = 60;
                temp.FlipCircle(moveList->Mcir, moveList->moveX);
            }
            
            if(moveList->timer==0){
                moveList->moveSpeed = 1;
            }else{
                moveList->timer--;
            }
            
            moveList->Mcir->setPosition(tempX+moveList->moveX*moveList->moveSpeed, tempY+moveList->moveY*moveList->moveSpeed);
            moveList->streak->setPosition(tempX,tempY);
            moveList = moveList->next;
            if(moveList==list)break;
        }
    }
}//구체 움직이기 스케쥴러

void InGameScene::CircleCreate(float dt)
{
    if(gamestopS==0){
        char tempstring[20] = {0};
        Objectcircle temp;
        
        for(int i=1; i<=3; i++) temp.FadeCircle(&list, this, settingCircle);
        log("%d",temp.GetCircleCount(list));
        if(temp.GetCircleCount(list)>=gameOverMaxCircle) GameOver();
        
        if(temp.GetCircleCount(list)>=gameOverMaxCircle-12 && gamedengerS==0){
            GameDenger();
        }else if(temp.GetCircleCount(list)<gameOverMaxCircle-12 && gamedengerS==1){
            gamedengerS=0;
            this->removeChildByTag(GAMEDENGERLAYERTAG);
        }
        sprintf(tempstring, "%d", temp.GetCircleCount(list));
        circleCount->setString(tempstring);
    }
}//매초마다 구체 생성스케쥴러

void InGameScene::inCircle(float dt)
{
    inCircleColorChange(list);
}//구체가 안에들어오면 색바꿔주기 스케줄러

void InGameScene::EffectDequeue(float dt)
{
    if(queuelist!=NULL){
        EffectQueue temp;
        temp.particleDequeue(&queuelist);
    }else{
        unschedule(schedule_selector(InGameScene::EffectDequeue));
    }
}//이펙트 큐에서 Dequeue

void InGameScene::EndEffectPlay(float dt)
{
    if(list!=NULL){
        Objectcircle temp;
        int tempX = list->Mcir->getPositionX();
        int tempY = list->Mcir->getPositionY();
        EffectCreate(tempX, tempY);
        removeChild(list->Mcir);
        removeChild(list->streak);
        temp.RemoveCircle(list, &list);
    }else{
        unschedule(schedule_selector(InGameScene::EndEffectPlay));
    }
}//게임클리어, 오버시 구체들을 터트리기위한 스케줄러

void InGameScene::GameCount(float dt)
{
    char tempstring[20]={0,};
    int temp = std::atoi(gameCountLabel->getString().c_str());
    sprintf(tempstring, "%d", temp);
    if(gameCountNum > 0){
        gameCountNum--;
        sprintf(tempstring, "%d", gameCountNum);
        gameCountLabel->setString(tempstring);
    }else{
        gamestopS = 0;
        gameCountNum = 3;
        removeChild(gameCountLabel);
        unschedule(schedule_selector(InGameScene::GameCount));
    }
}//3초 카운트를 해주기위한 스케줄러

void InGameScene::ComboLabelMove(float dt)
{
    char tempstring[100000]={0,};
    LabelTTF* temptxt = (LabelTTF*)getChildByTag(SCORELABELTAG);
    if(gamestopS==0){
        float tempX, tempY;
        Objectcircle temp;
        if(comboLabelList==NULL){
            unschedule(schedule_selector(InGameScene::ComboLabelMove));
        }else{
            while(comboLabelList!=NULL){
                tempX = comboMoveLabelList->comboLable->getPositionX();
                tempY = comboMoveLabelList->comboLable->getPositionY();
                tempX = tempX+0.1*((size.width -60)-tempX);
                tempY = tempY+0.1*((size.height-40)-tempY);
                
                comboMoveLabelList->comboLable->setPosition(tempX, tempY);
                if(tempX>=(size.width -60)-1 && tempY>=(size.height-40)-1){
                    Objectcircle::ComboLabelNode* removeNode;
                    removeNode = comboMoveLabelList;
                    comboMoveLabelList = comboMoveLabelList->next;

                    removeChild(removeNode->comboLable);
                    temp.RemoveCircle(removeNode,
                                      &comboLabelList);
                    
                    gamescore +=100;
                    sprintf(tempstring, "%d", gamescore);
                    temptxt->setString(tempstring);
                    log("%d", gamescore);
                    
                }else{
                    comboMoveLabelList = comboMoveLabelList->next;
                }
                //log("(x:%f y:%f)(x:%f y:%f)", tempX, tempY,size.width -60, size.height-40);
                if(comboLabelList==comboMoveLabelList)break;
            }
        }
        
    }
}//콤보 레이블을 이동시키기위한 스케줄러

void InGameScene::ComboTimer(float dt)
{
    combotimer--;
    //log("%d",combotimer);
    if(combotimer==0){
        unschedule(schedule_selector(InGameScene::ComboTimer));
        combonum = 0;
    }
}//콤보 유지시간을 위한 스케줄러

void InGameScene::feverTimer(float dt)
{
    
    fevertimernum--;
    if(fevertimernum==0){
        schedule(schedule_selector(InGameScene::CircleCreate),createTimer);
        schedule(schedule_selector(InGameScene::CircleMove));
        
        unschedule(schedule_selector(InGameScene::feverTimer));
        schedule(schedule_selector(InGameScene::allFadeRemoveFeverCircle));
        feverswitch = 0;
    }
}//피버 유지시간을 위한 스케줄러

void InGameScene::allFadeRemoveFeverCircle(float dt)
{
    if(feverlist!=NULL){
        Objectcircle temp;
        Objectcircle::Circle* templist = feverlist;
        Objectcircle::Circle* removeobject;
        int tempopacity;
        do{
            tempopacity = templist->Mcir->getOpacity();
            
            if(tempopacity-2<=0){
                removeobject = templist;
                templist = templist->next;
                
                removeChild(removeobject->Mcir);
                removeChild(removeobject->streak);
                temp.RemoveCircle(removeobject, &feverlist);
                
            }else{
                templist->Mcir->setOpacity(tempopacity-2);
                templist = templist->next;
            }
        }while(templist!=feverlist);
    }else{
        unschedule(schedule_selector(InGameScene::allFadeRemoveFeverCircle));
    }
}//마지막 페이드아웃으로 피버동그리를 제거하는 스케줄러

#pragma mark- 터치이벤트

void InGameScene::touchesBegan(cocos2d::Set *touches, cocos2d::Event *event)
{
    SetIterator TouchPoint = touches->begin();
    Touch* touch = (Touch*)(*TouchPoint);
    Point location = touch->getLocation();
    
    Objectcircle temp;
    
    if(gamestopS==0 && feverswitch==0){
        testt[0][0] = location.x;
        testt[0][1] = location.y;

        streak = MotionStreak::create(0.5, 3, 10, ccWHITE, "paddle.png" );
        streak->setPosition(location.x,location.y);
        addChild(streak,4);
        
        schedule(schedule_selector(InGameScene::inCircle));
    }else if(feverswitch==1&&feverlist!=NULL){
        int tempX, tempY, spriteSizeW, spriteSizeH;
        Objectcircle::Circle* tmeplist = feverlist;
        Objectcircle::Circle* removeObject;
        
        do{
            log("탐색");
            tempX = tmeplist->Mcir->getPositionX();
            tempY = tmeplist->Mcir->getPositionY();
            spriteSizeW = tmeplist->Mcir->getContentSize().width/2;
            spriteSizeH = tmeplist->Mcir->getContentSize().height/2;
            
            if((tempX-spriteSizeW <= location.x && tempX+spriteSizeW >= location.x) && (tempY-spriteSizeH <= location.y && tempY+spriteSizeH >= location.y)){
                
                combonum++;
                ComboCenterLabelPlay();
                
                removeObject = tmeplist;
                tmeplist = tmeplist->next;
                
                removeChild(removeObject->Mcir);
                removeChild(removeObject->streak);
                temp.RemoveCircle(removeObject, &feverlist);
                
                EffectCreate(tempX, tempY);//이펙트 재생
                ComboLabelCreate(tempX, tempY);//점수연출 생성
                
                break;
            }else{
                tmeplist = tmeplist->next;
            }
        }while(tmeplist != feverlist);
    }
}//터치시

void InGameScene::touchesMoved(cocos2d::Set *touches, cocos2d::Event *event)
{
    if(gamestopS==0&&feverswitch==0){
        SetIterator TouchPoint = touches->begin();
        Touch* touch = (Touch*)(*TouchPoint);
        Point location = touch->getLocation();
        
        testc++;
        testt[testc][0] = location.x;
        testt[testc][1] = location.y;
        
    
        if(location.x>=0&&location.x<=size.width&&location.y>=0&&location.y<=size.height){
            streak->setPosition(location.x,location.y);
        }
    }
}//터치중 이동할때

//=====================================================================================
//                                      순서
//
//          1. 게임이 정지된 상태인지 체크
//          2. 첫 터치좌표와 마지막 터치좌표의 거리를 구해 일정거리에서 터지를 완료했는지 체크
//          3. 다각형 안의 구체수 체크
//          4. 다각형 안의 구체수가 3개이면 삭제실행
//          5. 만일 모두 삭제된 경우 12개 생성
//          6. 콤보가 5이면 피버실행
//          7. 초기화
//
//=====================================================================================

void InGameScene::touchesEnded(cocos2d::Set* touches, cocos2d::Event* event)
{
    SetIterator TouchPoint = touches->begin();
    Touch* touch = (Touch*)(*TouchPoint);
    Point location = touch->getLocation();
    
    Objectcircle temp;
    Objectcircle::Circle* removeObject;
    
    char tempstring[20] = {0};
    
    allCircleColorChange(list, Color3B(255,255,255));//색초기화
    
    if(gamestopS==0 && feverswitch==0){
        
        testt[testc][0] = location.x;
        testt[testc][1] = location.y;
        
        float jum = sqrt(pow(testt[testc][0]-testt[0][0], 2) + pow(testt[testc][1]-testt[0][1], 2));
        
        //log("%f",jum);
        if(true){ //jum <= setDistance
            
            testt[testc][0] = testt[0][0];
            testt[testc][1] = testt[0][1];
            
            unschedule(schedule_selector(InGameScene::CircleMove));
            unschedule(schedule_selector(InGameScene::CircleCreate));
            //버그방지로 스캐줄러 잠시 해제
            
            int count=0;
            int tempX, tempY; //임시로 체크할 구체의 위치를 담음
            
            boomcircleS=1;
            moveList = list;
            
            for(int i=0; i<temp.GetCircleCount(countList);i++){
                tempX = countList->Mcir->getPositionX();
                tempY = countList->Mcir->getPositionY();
                if(inpoly(testt, testc, tempX, tempY)==1)count++;
                //log("원안에 있는 구체수:%d", count);
                countList = countList->next;
            }//그린 원안에 있는 구체수 체크
            
            int deleteCount = 0;
            
            if(count==catchCount){ //그린 원안에 구체가 일정수만큼 있을시 실행
                while(deleteCount != catchCount){//삭제된 구체가 일정구체를 넘지않을때까지 반복
                    tempX = countList->Mcir->getPositionX();
                    tempY = countList->Mcir->getPositionY();
                    if(inpoly(testt, testc, tempX, tempY)==1){
                        deleteCount++;
                        removeObject = countList;
                        countList = countList->next;
                        log("Delete: %d",removeObject->nodenumber);
                        
                        removeChild(removeObject->Mcir);
                        removeChild(removeObject->streak);
                        temp.RemoveCircle(removeObject, &list);
                        
                        EffectCreate(tempX, tempY);//이펙트 재생
                        ComboLabelCreate(tempX, tempY);//점수연출 생성
                    }else{
                        countList = countList->next;
                    }
                }
                
                combonum++;
                ComboCenterLabelPlay();
                
                if(combonum==setfevernum){
                    feverswitch=1;
                    for(int i=0; i<50; i++){
                        temp.FadeCircle(&feverlist, this, settingCircle);
                    }
                    allCircleColorChange(feverlist, Color3B(100,0,0));
                    schedule(schedule_selector(InGameScene::feverTimer),1.0f);
                    fevertimernum = 5;
                }//피버!
                
                sprintf(tempstring, "%d", temp.GetCircleCount(list));
                circleCount->setString(tempstring);
                
                log("AllCreate큐: %d",queuelist->count);
            }//구체제거
            
            countList = list; //초기화
            if(temp.GetCircleCount(countList)==0)for(int i=0; i<12; i++)temp.FadeCircle(&list, this, settingCircle);//구체를 모두없애면 12개를 생성해줌
            
            //log("원안에 있는 구체수:%d", count);

            for(int i=0; i<testc; i++){
                testt[i][0]=0;
                testt[i][1]=0;
            }//그린 점 초기화
            
            boomcircleS=0;
            moveList = list;
            
            if(feverswitch!=1){
                schedule(schedule_selector(InGameScene::CircleCreate),createTimer);
                schedule(schedule_selector(InGameScene::CircleMove));
            }
            
            unschedule(schedule_selector(InGameScene::inCircle));
            
        }
    }
    
    testc = 0;
    
}//터치에서 손을 땠을때

#pragma mark- 게임정지

void InGameScene::GameStop() //GameStop 레이어 생성
{
    if(gamestopS==0){
        gamestopS=1;
        Layer* gameStopLayer = LayerColor::create(Color4B(0, 0, 0, 100));
        gameStopLayer->setTag(GAMESTOPLAYERTAG);
        
        MenuItemImage *homeButton = MenuItemImage::create("homebutton.png",
                                                          "testbuttonpush.png",
                                                          CC_CALLBACK_1(InGameScene::StopMenuCallback, this));
        
        MenuItemImage *resultButton = MenuItemImage::create("returnbutton.png",
                                                            "testbuttonpush.png",
                                                            CC_CALLBACK_1(InGameScene::StopMenuCallback, this));
        
        homeButton->setTag(HOME);
        resultButton->setTag(RESULTGAME);
        
        Menu* stopMenu = Menu::create(homeButton, resultButton, NULL);
        stopMenu->alignItemsHorizontally();
        gameStopLayer->addChild(stopMenu);
        this->addChild(gameStopLayer, 3);
    }
}

void InGameScene::StopMenuCallback(Object* pSender)
{
    Objectcircle temp;
    MenuItem* itemTag = (MenuItem *)pSender;
    switch (itemTag->getTag()) {
        case RESULTGAME:
            this->removeChildByTag(GAMESTOPLAYERTAG);
            GameCountStart();
            break;
        case HOME:
            if(list!=NULL) temp.AllRemoveCircle(&list);
            Director::getInstance()->replaceScene(TransitionFade::create(0.8, GameMain::scene()));
            break;
        default:
            break;
    }
}

#pragma mark- 게임오버

void InGameScene::GameOver()
{
    char tempstring[20] = {0,};
    
    gamestopS=1;
    this->removeChildByTag(GAMEDENGERLAYERTAG);
    
    Layer* gameOverLayer = LayerColor::create(Color4B(0, 0, 0, 100));
    gameOverLayer->setTag(GAMEOVERLAYERTAG);
    
    Sprite* popUpBack = Sprite::create("Result.png");
    popUpBack->setPosition(size.width/2, size.height/2);
    popUpBack->setOpacity(0);
    
    Sprite* overTextImg = Sprite::create("gameover.png");
    overTextImg->setPosition(size.width/2, size.height/2);
    overTextImg->setOpacity(0);
    
    LabelTTF* endscorelabel = LabelTTF::create("0", "맑은 고딕", 30, CCSizeMake(400, 60),kCCTextAlignmentRight);
    endscorelabel->setPosition(size.width/2+100, size.height/2+80);
    endscorelabel->setColor(ccBLACK);
    endscorelabel->setOpacity(0);
    sprintf(tempstring, "%d",gamescore);
    endscorelabel->setString(tempstring);
    log("score:%d\nmaxcombo:%d", gamescore, maxcombo);
    
    LabelTTF* endplaytimelabel = LabelTTF::create("0", "맑은 고딕", 30, CCSizeMake(400, 60),kCCTextAlignmentRight);
    endplaytimelabel->setPosition(ccp(size.width/2+100, size.height/2));
    endplaytimelabel->setColor(ccBLACK);
    endplaytimelabel->setOpacity(0);
    
    LabelTTF* endmaxcombolabel = LabelTTF::create("0", "맑은 고딕", 30, CCSizeMake(400, 60),kCCTextAlignmentRight);
    endmaxcombolabel->setPosition(size.width/2+100, size.height/2-80);
    endmaxcombolabel->setColor(ccBLACK);
    sprintf(tempstring, "%d",maxcombo);
    endmaxcombolabel->setString(tempstring);
    
    MenuItemImage *overhomeButton = MenuItemImage::create("homebutton.png",
                                                          "testbuttonpush.png",
                                                          CC_CALLBACK_1(InGameScene::OverMenuCallback, this));
    
    MenuItemImage *replayButton = MenuItemImage::create("nextbutton.png",
                                                        "testbuttonpush.png",
                                                        CC_CALLBACK_1(InGameScene::OverMenuCallback, this));
    
    
    overhomeButton->setTag(HOME); replayButton->setTag(REPLAY);
    
    Menu* overMenu = Menu::create(overhomeButton, replayButton, NULL);
    overMenu->alignItemsHorizontally();
    overMenu->setOpacity(0);
    overMenu->setPosition(size.width/2, size.height/2-160);
    
    gameOverLayer->addChild(overMenu,3);
    gameOverLayer->addChild(popUpBack,1);
    gameOverLayer->addChild(overTextImg,10);
    gameOverLayer->addChild(endscorelabel,3);
    gameOverLayer->addChild(endplaytimelabel,3);
    gameOverLayer->addChild(endmaxcombolabel,3);
    
    this->addChild(gameOverLayer);
    
    overTextImg     ->runAction(Sequence::create(FadeIn::create(1.0),
                                                 DelayTime::create(1.0),
                                                 FadeOut::create(1.0),
                                                 NULL));
    popUpBack       ->runAction(Sequence::create(DelayTime::create(3.0),
                                                 FadeIn::create(1.0),
                                                 NULL));
    overMenu        ->runAction(Sequence::create(DelayTime::create(3.0),
                                                 FadeIn::create(1.0),
                                                 NULL));
    endscorelabel   ->runAction(Sequence::create(DelayTime::create(3.0),
                                                 FadeIn::create(1.0),
                                                 NULL));
    endplaytimelabel->runAction(Sequence::create(DelayTime::create(3.0),
                                                 FadeIn::create(1.0),
                                                 NULL));
    endmaxcombolabel->runAction(Sequence::create(DelayTime::create(3.0),
                                                 FadeIn::create(1.0),
                                                 NULL));
    
    schedule(schedule_selector(InGameScene::EndEffectPlay),0.1f);
    
}

void InGameScene::OverMenuCallback(Object* pSender)
{
    //Objectcircle temp;
    MenuItem* itemTag = (MenuItem *)pSender;
    switch (itemTag->getTag()) {
        case HOME:
            //temp.AllRemoveCircle(&list);
            Director::getInstance()->replaceScene(TransitionFade::create(0.8, GameMain::scene()));
            break;
        case REPLAY:
            //temp.AllRemoveCircle(&list);
            Director::getInstance()->replaceScene(TransitionFade::create(0.8, InGameScene::scene()));
            break;
        default:
            break;
    }
}

#pragma mark- 게임위험

void InGameScene::GameDenger()
{
    gamedengerS=1;
    Layer* gameDengerLayer = Layer::create();
    gameDengerLayer->setTag(GAMEDENGERLAYERTAG);
    
    Sprite* denger = Sprite::create("Danger.png");
    denger->setPosition(size.width/2, size.height/2);
    gameDengerLayer->addChild(denger, 5);
    this->addChild(gameDengerLayer);
}

#pragma mark- 함수

int InGameScene::inpoly(unsigned int poly[][2], int npoints, int xt, int yt)
{
    unsigned int xnew,ynew;
    unsigned int xold,yold;
    unsigned int x1,y1;
    unsigned int x2,y2;
    int i;
    int inside=0;
    
    if (npoints < 3) {
        return(0);
    }
    xold=poly[npoints-1][0];
    yold=poly[npoints-1][1];
    for (i=0 ; i < npoints ; i++) {
        xnew=poly[i][0];
        ynew=poly[i][1];
        if (xnew > xold) {
            x1=xold;
            x2=xnew;
            y1=yold;
            y2=ynew;
        }
        else {
            x1=xnew;
            x2=xold;
            y1=ynew;
            y2=yold;
        }
        if ((xnew < xt) == (xt <= xold)
            && ((long)yt-(long)y1)*(long)(x2-x1)
            < ((long)y2-(long)y1)*(long)(xt-x1)) {
            inside=!inside;
        }
        xold=xnew;
        yold=ynew;
    }
    return inside;
}//다각형 안의 점 판단

void InGameScene::EffectCreate(int x, int y){
    EffectQueue effectTemp;
    if(queuelist==NULL){ //리스트가 생성되있지않으면 스케줄 생성
        effectTemp.particleQueueCreate(&queuelist);
        schedule(schedule_selector(InGameScene::EffectDequeue),1.0f);
    }
    
    effectTemp.particleAppend(queuelist, effectTemp.particleNodeCreate("ExplodingRing.plist"));
    
    queuelist->Rear->particle->setPosition(x, y);
    addChild(queuelist->Rear->particle);
}//이펙트 생성및 배치

void InGameScene::GameCountStart()
{
    
    gameCountLabel = LabelTTF::create("3", "맑은 고딕", 60);
    gameCountLabel->setPosition(size.width/2, size.height/2);
    gameCountLabel->setColor(Color3B(255,255,255));
    addChild(gameCountLabel,2);
    schedule(schedule_selector(InGameScene::GameCount),1.0f);
}

void InGameScene::ComboLabelCreate(int x, int y)
{
    if(comboLabelList==NULL)schedule(schedule_selector(InGameScene::ComboLabelMove));
    
    Objectcircle temp;
    Objectcircle::ComboLabelNode* tempNode;
    tempNode = temp.Createcircle();
    tempNode->comboLable = LabelTTF::create("+100", "맑은 고딕", 40);
    tempNode->comboLable->setPosition(x, y);
    tempNode->comboLable->setColor(Color3B(255,255,255));
    addChild(tempNode->comboLable);
    temp.AppendCircle(&comboLabelList, tempNode);
    
    comboMoveLabelList = comboLabelList;
}

void InGameScene::ComboCenterLabelPlay()
{
    char tempstring[20]={0,};
    if(combotimer==0){
        schedule(schedule_selector(InGameScene::ComboTimer));
        combotimer = setcombotimer;
    }else{
        combotimer = setcombotimer;
        LabelTTF* templabel = (LabelTTF*)getChildByTag(COMBOLABELTAG);
        sprintf(tempstring, " %dcombo!",combonum);
        templabel->setString(tempstring);
        templabel->runAction(Sequence::create(FadeIn::create(0.5),
                                              DelayTime::create(0.5),
                                              FadeOut::create(0.5),
                                              NULL));
        
        if(maxcombo<combonum) maxcombo = combonum;
        
    }
}

void InGameScene::inCircleColorChange(Objectcircle::Circle*  changeColorlist)
{
    if(changeColorlist!=NULL){
        int tempX, tempY;
        do{
            tempX = changeColorlist->Mcir->getPositionX();
            tempY = changeColorlist->Mcir->getPositionY();
            
            if(inpoly(testt, testc, tempX, tempY)==1){
                changeColorlist->Mcir->updateDisplayedColor(Color3B(0,100,0));
                changeColorlist = changeColorlist->next;
            }else{
                changeColorlist->Mcir->updateDisplayedColor(Color3B(255,255,255));
                changeColorlist = changeColorlist->next;
            }
        }while(changeColorlist != list);
    }
}

void InGameScene::allCircleColorChange(Objectcircle::Circle*  changeColorlist, Color3B settingcolor)
{
    Objectcircle::Circle* templist = changeColorlist;
    do{
        templist->Mcir->updateDisplayedColor(settingcolor);
        templist = templist->next;
    }while(templist != changeColorlist);
}//리스트의 모든 객체의 색상을 바꾸기위한 함수

/*bool InGameScene::updateFadeRemoveCircle(Objectcircle::Circle* fadenode)
{
    int tempopacity = fadenode->Mcir->getOpacity();
    fadenode->Mcir->setOpacity(tempopacity-2);
    
    if(fadenode->Mcir->getOpacity()<=0){
        return TRUE;
    }else{
        return FALSE;
    }
    
}*/

