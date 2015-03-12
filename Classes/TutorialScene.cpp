#include "TutorialScene.h"
#include "GameMain.h"

using namespace cocos2d;

TutorialScene::TutorialScene() :
_catchCount(3)
{
    
}

Scene* TutorialScene::scene()
{
    Scene* tutorial_Scene = Scene::create();
    TutorialScene* tutorial_Layer = TutorialScene::create();
    
    tutorial_Scene->addChild(tutorial_Layer);
    return tutorial_Scene;
}

bool TutorialScene::init()
{
    size = Director::getInstance()->getVisibleSize();
    
    Sprite* background = Sprite::create("background/Pbackground9.png");
    background->setPosition(size.width/2, size.height/2);
    addChild(background,1);
    
    Sprite* dong = Sprite::create("tutorial/tudong.png");
    dong->setPosition(1000, size.height-420);
    dong->setTag(DONGTAG);
    addChild(dong, 3);
    
    Sprite* spr_mal = Sprite::create("tutorial/mal.png");
    spr_mal->setPosition(440, size.height-360);
    spr_mal->setTag(MALTAG);
    addChild(spr_mal, 3);
    
    LabelTTF* txt_mal = LabelTTF::create(mal_txt[txtnum], "맑은 고딕", 30, CCSizeMake(550, 300), kCCTextAlignmentLeft);
    
    txt_mal->setPosition(spr_mal->getPositionX()-50, spr_mal->getPositionY()/2+60);
    txt_mal->setColor(ccBLACK);
    txt_mal->setTag(TXTMALTAG);
    addChild(txt_mal, 4);
    
    Layer* tutolayer = LayerColor::create(Color4B(0, 0, 0, 100));
    tutolayer->setTag(LAYERTAG1);
    addChild(tutolayer,2);
    
    schedule(schedule_selector(TutorialScene::tutorialManagement));
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(TutorialScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(TutorialScene::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(TutorialScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

#pragma mark- 터치이벤트

void TutorialScene::touchesBegan(cocos2d::Set *touches, cocos2d::Event *event)
{
    if(touchnum==3){
        SetIterator TouchPoint = touches->begin();
        Touch* touch = (Touch*)(*TouchPoint);
        Point location = touch->getLocation();

        mousecoordinate[coordinatecount][0] = location.x;
        mousecoordinate[coordinatecount][1] = location.y;
        
        cocos2d::MotionStreak* streak = MotionStreak::create(0.5, 3, 10, ccWHITE, "paddle.png" );
        streak->setPosition(location.x,location.y);
        streak->setTag(STREAKTAG);
        addChild(streak,4);
        
        schedule(schedule_selector(TutorialScene::inCircle));
        
    }
}

void TutorialScene::touchesMoved(cocos2d::Set* touches, cocos2d::Event* event)
{
    if(touchnum==3){
        SetIterator TouchPoint = touches->begin();
        Touch* touch = (Touch*)(*TouchPoint);
        Point location = touch->getLocation();
        
        coordinatecount++;
        mousecoordinate[coordinatecount][0] = location.x;
        mousecoordinate[coordinatecount][1] = location.y;
        
        getChildByTag(STREAKTAG)->setPosition(location.x, location.y);
    }
}

void TutorialScene::touchesEnded(cocos2d::Set* touches, cocos2d::Event* event)
{
    Objectcircle temp;
    Objectcircle::Circle* removeObject;
    LabelTTF* temptxt = (LabelTTF*)getChildByTag(TXTMALTAG);
    switch (touchnum) {
        case 1: //대화넘기기
            temptxt->setString(mal_txt[txtnum]);
            txtnum++;
            break;
        case 2: //튜토리얼 장면넘기기
            tutonum++;
            break;
        case 3:
            
            unschedule(schedule_selector(TutorialScene::inCircle));
            clearCircleColor(tutolist);
            
            removeChildByTag(STREAKTAG);
            
            mousecoordinate[coordinatecount][0] = mousecoordinate[0][0];
            mousecoordinate[coordinatecount][1] = mousecoordinate[0][1];

            int count=0;
            int tempX, tempY; //임시로 체크할 구체의 위치를 담음
            Objectcircle::Circle* countlist = tutolist;
            
            //boomcircleS=1;
            //moveList = list;
            
            for(int i=0; i<temp.GetCircleCount(countlist);i++){
                tempX = countlist->Mcir->getPositionX();
                tempY = countlist->Mcir->getPositionY();
                if(inpoly(mousecoordinate, coordinatecount, tempX, tempY)==1)count++;
                countlist = countlist->next;
            }//그린 원안에 있는 구체수 체크
            
            int deleteCount = 0;
            
            if(count == catchCount){ //그린 원안에 구체가 일정수만큼 있을시 실행
                while(deleteCount != catchCount){//삭제된 구체가 일정구체를 넘지않을때까지 반복
                    tempX = countlist->Mcir->getPositionX();
                    tempY = countlist->Mcir->getPositionY();
                    if(inpoly(mousecoordinate, coordinatecount, tempX, tempY)==1){
                        deleteCount++;
                        removeObject = countlist;
                        countlist = countlist->next;
                        log("Delete: %d",removeObject->nodenumber);
                        
                        removeChild(removeObject->Mcir);
                        removeChild(removeObject->streak, true);
                        temp.RemoveCircle(removeObject, &tutolist);
                        
                        //EffectCreate(tempX, tempY);//이펙트 재생
                        //ComboLabelCreate(tempX, tempY);//점수연출 생성
                    }else{
                        countlist = countlist->next;
                    }
                }
                
                /*combonum++;
                
                if(combotimer==0){
                    schedule(schedule_selector(PlaytheGame::ComboTimer));
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
                }
                
                sprintf(tempstring, "%d", temp.GetCircleCount(list));
                circleCount->setString(tempstring);
                
                log("AllCreate큐: %d",queuelist->count);*/
                
            }//구체제거
            
            //countList = list; //초기화
            
            log("원안에 있는 구체수:%d", count);
            
            for(int i=0; i<coordinatecount; i++) {
                mousecoordinate[i][0]=0;
                mousecoordinate[i][1]=0;
            }//그린 점 초기화
            
            break;
    }
    
    coordinatecount=0;
}
#pragma mark- 스케줄러

void TutorialScene::tutorialManagement(float dt)
{
    Sprite* guid_img = NULL;
    Objectcircle temp;
    switch (tutonum){
        case 1:
            ///////////////////////////////////////////////////
            //                      튜토리얼1
            //
            // mal_txt[0] = "Circle Boom을 플레이 해주셔서 감사합니다.";
            // mal_txt[1] = "저는 게임의 진행방법을 설명해 드리러 온 동글이라고 합니다";
            // mal_txt[2] = "그럼 지금부터 게임을 설명해드리겠습니다.";
            // mal_txt[3] = "먼저 게임의 기본 룰 입니다.";
            //
            if(txtnum>4){
                Sprite* help_img = Sprite::create("tutoimg1.png");
                help_img->setTag(HELPIMGTAG);
                help_img->setPosition(400, size.height-310);
                addChild(help_img, 3);
                getChildByTag(TXTMALTAG)->setVisible(false);
                tutonum = 2;
                touchnum = 2;
            }
            break;
            
        case 2:
            ///////////////////////////////////////////////////
            //                      튜토리얼2
            //
            // 예시 이미지 보여주기(대기)
            //
            
            break;
            
        case 3:
            ///////////////////////////////////////////////////
            //                      튜토리얼3
            //
            // mal_txt[4] = "그럼 한번 해보겠습니다";
            //
            
            removeChildByTag(HELPIMGTAG);
            getChildByTag(TXTMALTAG)->setVisible(true);
            break;
            
        case 4:
            ///////////////////////////////////////////////////
            //                      튜토리얼4
            // 말풍선과 케릭터 페이드아웃
            // 실제 예시 이미지를 보여준다.
            // 클릭하면 터치가 활성화되고 직접해보게 된다.
            //
            
            guid_img = Sprite::create("tempguidimg.png");
            guid_img->setTag(GUIDIMGTAG);
            guid_img->setPosition(size.width/2, size.height/2-30);
            addChild(guid_img, 3);
            
            getChildByTag(DONGTAG   )->setVisible(false);
            getChildByTag(MALTAG    )->setVisible(false);
            getChildByTag(TXTMALTAG )->setVisible(false);
            getChildByTag(LAYERTAG1 )->setVisible(false);
            
            for(int i=0; i<3; i ++) temp.FadeCircle(&tutolist, this, settingCircle);
            
            tutonum=5;
            
            break;
        case 5:
            ///////////////////////////////////////////////////
            //                      튜토리얼5
            // 이미지 보여주기(대기)
            //
            tutolist->Mcir->setPosition(size.width/2, size.height/2);
            tutolist = tutolist->next;
            tutolist->Mcir->setPosition(size.width/2-60, size.height/2+50);
            tutolist = tutolist->next;
            tutolist->Mcir->setPosition(size.width/2+60, size.height/2+50);
            tutolist = tutolist->next;
            
            break;
            
        case 6:
            ///////////////////////////////////////////////////
            //                      튜토리얼6
            // 터치활성화
            //
            this->removeChildByTag(GUIDIMGTAG);
            touchnum++;
            tutonum++;
            break;
        case 7:
            ///////////////////////////////////////////////////
            //                      튜토리얼7
            // 
            //
            if(temp.GetCircleCount(tutolist)==0)tutonum++;
            break;
        case 8:
            ///////////////////////////////////////////////////
            //                      튜토리얼8
            // 튜토리얼 끝
            //
            Director::sharedDirector()->replaceScene(TransitionFade::create(0.8, GameMain::scene()));
            tutonum++;
            break;
            
    };
}

void TutorialScene::inCircle(float dt)
{
    inCircleColorChange(tutolist);
}//구체가 안에들어오면 색바꿔주기 스케줄러


#pragma mark- 기타함수

int TutorialScene::inpoly(unsigned int poly[][2], int npoints, int xt, int yt)
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

void TutorialScene::inCircleColorChange(Objectcircle::Circle*  changeColorlist)
{
    int tempX, tempY;
    if(changeColorlist!=NULL){
        do{
            tempX = changeColorlist->Mcir->getPositionX();
            tempY = changeColorlist->Mcir->getPositionY();
            
            if(inpoly(mousecoordinate, coordinatecount, tempX, tempY)==1){
                changeColorlist->Mcir->updateDisplayedColor(Color3B(0,100,0));
                changeColorlist = changeColorlist->next;
            }else{
                changeColorlist->Mcir->updateDisplayedColor(Color3B(255,255,255));
                changeColorlist = changeColorlist->next;
            }
        }while(changeColorlist != tutolist);
    }
}

void TutorialScene::clearCircleColor(Objectcircle::Circle*  changeColorlist)
{
    do{
        changeColorlist->Mcir->updateDisplayedColor(Color3B(255,255,255));
        changeColorlist = changeColorlist->next;
    }while(changeColorlist != tutolist);
}

