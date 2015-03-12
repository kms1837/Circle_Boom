#include "GameMain.h"

USING_NS_CC;
USING_NS_CC_EXT;

Objectcircle::Circle* mainCricleList = NULL;

//CCLayer* HelpPopupLayer;
//CCLayer* EndPopupLayer;

const char* helpPopupImgName[4] = {"", "help/helpim1.png" , "help/helpim3.png","help/helpim9.png"};

Label* helppointText;
Sprite* helpPopupImg;

bool popupS = false;

#define ABSOLUTE_PATHS "/Users/kms/development/workspace/CircleBoom-xcode-/CircleBoom-xcode-/Resources/"

#pragma mark - 메인 씬

Scene* GameMain::scene()
{
    Scene* gameMainScene = Scene::create();
    GameMain* main_layer = GameMain::create();
	gameMainScene->addChild(main_layer);
    
    return gameMainScene;
}

bool GameMain::init(){
    size = Director::getInstance()->getWinSize();
    //CCLog("sound_volume : %f",Management::sound_volume);
    
    Sprite* imgGameTitle = Sprite::create("main/title.png");
	imgGameTitle->setPosition(size.width/2, size.height/2+50);
	this->addChild(imgGameTitle,1);
    
    Sprite* mainBackgrount = Sprite::create("background/Pbackground8.png");
    mainBackgrount->setPosition(size.width/2, size.height/2);
    this->addChild(mainBackgrount,0);
    
	MenuItemImage* helpb = MenuItemImage::create("main/helpbutton2.png",
                                                 "main/helpbutton2.png",
                                                 CC_CALLBACK_1(GameMain::MainClickCallback, this));
    //도움말
    
    helpb->setTag(HELP);
	Menu* helpMenu = Menu::create(helpb, nullptr);
    helpMenu->setPosition(0, size.height/2 - 250);
    
	MenuItemImage* settingb = MenuItemImage::create("main/settingbutton2.png",
                                                    "main/settingbutton2.png",
                                                    CC_CALLBACK_1(GameMain::MainClickCallback, this));
    //옵션
    settingb->setTag(SETTING);
	Menu* settingMenu = Menu::create(settingb, nullptr);
    settingMenu->setPosition(size.width, size.height/2 - 250);
    
    log("height Size : %f", size.height);
    
    MenuItemImage* playb = MenuItemImage::create("main/playb3.png",
                                                 "main/playb3.png",
                                                 CC_CALLBACK_1(GameMain::MainClickCallback, this));
    //게임시작
    /*
	MenuItemImage *exitb =MenuItemImage::create( //종료
                                                     "exitb.png",
                                                     "exitb.png",
                                                     this,
                                                     CC_CALLBACK_1(GameMain::MainClickCallback));
     */

    playb->setTag(GAMESTART);
    //exitb->setTag(EXIT);
    
    Menu* mainMenu = Menu::create(playb, nullptr);
	mainMenu->setPosition(size.width/2, size.height/2 - 250);
	//mainMenu->alignItemsVertically();
    
    addChild(helpMenu, 2);
	addChild(settingMenu, 2);
	addChild(mainMenu, 2);
    
    helpMenu    ->setOpacity(0);
    settingMenu ->setOpacity(0);
    mainMenu    ->setOpacity(0);
    
    helpMenu    ->runAction(Sequence::create(DelayTime::create(1.0),FadeIn::create(1.0),NULL));
    settingMenu ->runAction(Sequence::create(DelayTime::create(1.0),FadeIn::create(1.0),NULL));
    mainMenu    ->runAction(Sequence::create(DelayTime::create(1.0),FadeIn::create(1.0),NULL));
    
    return true;
}

void GameMain::MainClickCallback(Ref* pSender)
{
    MenuItem* pMenuItem = (MenuItem *)pSender;
    Director* director = Director::getInstance();
    
    if(popupS==false){
        switch (pMenuItem->getTag()) {
            case HELP:
                HelpPopup();
                break;
            case GAMESTART:
                director->replaceScene(TransitionFade::create(0.8, InGameScene::scene()));
                break;
            case SETTING:
                director->replaceScene(TransitionSlideInR::create(0.3, OptionScene::scene()));
                break;
            case EXIT:
                EndPopup();
                break;
        }
    }
}

#pragma mark - 도움말 팝업 레이어

void GameMain::HelpPopup()
{
    if(popupS==false){
        char string[12] ={0,};
        
        popupS=true;
        
        Layer* HelpPopupLayer = LayerColor::create(Color4B(0, 0, 0, 100));
        HelpPopupLayer->setTag(HELPPOPLAYERTAG);
        Sprite* gHelppopup = Sprite::create("main/helpback.png");
        gHelppopup->setPosition(size.width/2, size.height/2);
        
        MenuItemImage *helpb_Exit = MenuItemImage::create("other/Xbutton.png",
                                                          "other/Xbuttonpush.png",
                                                          CC_CALLBACK_1(GameMain::HelpClickCallback, this));
        //종료버튼
        
        MenuItemImage *helpb_Next = MenuItemImage::create("other/sbutton.png",
                                                          "other/Xbuttonpush.png",
                                                          CC_CALLBACK_1(GameMain::HelpClickCallback, this));
        //다음
        
        MenuItemImage *helpb_Prev = MenuItemImage::create("other/sbutton.png",
                                                          "other/Xbuttonpush.png",
                                                          CC_CALLBACK_1(GameMain::HelpClickCallback, this));
        //이전
        
        helpb_Exit->setTag(CANCEL);
        helpb_Next->setTag(HELPNEXT);
        helpb_Prev->setTag(HELPPREV);
        
        helpb_Next->setRotation(180);
        helpb_Next->setPosition(70,0);
        helpb_Prev->setPosition(-70,0);
        
        Menu* HelpMenu = Menu::create(helpb_Next, helpb_Prev, NULL);
        HelpMenu->setPosition(size.width/2, 110);
        
        Menu* HelpExitMenu = Menu::create(helpb_Exit, NULL);
        HelpExitMenu->setPosition(size.width/2+180, size.height/2+230);
        
        sprintf(string, "%d / %d", helpnum, maxhelpnum);
        helppointText = Label::createWithTTF(string, "font/NanumGothic.ttc", 25);
        helppointText->setColor(Color3B(0,0,0));
        helppointText->setPosition(size.width / 2, 110);
        
        helpPopupImg =Sprite::create(helpPopupImgName[1]);
        helpPopupImg->setPosition(size.width/2, size.height/2);
        
        HelpPopupLayer->addChild(helpPopupImg,7);
        HelpPopupLayer->addChild(helppointText, 7);
        HelpPopupLayer->addChild(gHelppopup, 6);
        HelpPopupLayer->addChild(HelpMenu, 7);
        HelpPopupLayer->addChild(HelpExitMenu, 7);
        this->addChild(HelpPopupLayer, 5);
    }
}

void GameMain::HelpClickCallback(Ref* pSender)
{
    MenuItem* pMenuItem = (MenuItem *)pSender;
    
    char string[10] = {0};
    switch (pMenuItem->getTag()) {
        case HELPNEXT:
            if(helpnum<maxhelpnum){
                helpnum++;
                sprintf(string, "%d / %d", helpnum, maxhelpnum);
                helppointText->setString(string);
                helpPopupImg->setTexture(helpPopupImgName[helpnum]);
            }
            break;
        case HELPPREV:
            if(helpnum>1){
                helpnum--;
                sprintf(string, "%d / %d", helpnum, maxhelpnum);
                helppointText->setString(string);
                helpPopupImg->setTexture(helpPopupImgName[helpnum]);
            }
            break;
        case CANCEL:{
            popupS = false;
            this->removeChildByTag(HELPPOPLAYERTAG);
            this->removeChild(this->getChildByTag(ENDPOPLAYERTAG));
            break;
        }
            
    }
}

#pragma mark - 게임종료 팝업 레이어

void GameMain::EndPopup()
{
    if(popupS==false){
        popupS=true;
        Layer* EndPopupLayer = LayerColor::create(Color4B(0, 0, 0, 100));
        EndPopupLayer->setTag(ENDPOPLAYERTAG);
        MenuItemImage* endpopb_end = MenuItemImage::create("closebutton.png",
                                                           "closebutton.png",
                                                           CC_CALLBACK_1(GameMain::EndClickCallback, this));
        //종료
        
        MenuItemImage* endpopb_cancel = MenuItemImage::create("cancelbutton.png",
                                                              "cancelbutton.png",
                                                              CC_CALLBACK_1(GameMain::EndClickCallback, this));
        //취소
        
        endpopb_end->setTag(EXIT);
        endpopb_cancel->setTag(CANCEL);
        Menu* EndMenu =Menu::create(endpopb_end, endpopb_cancel, NULL);
        EndMenu->alignItemsHorizontally();
        EndMenu->setPosition(size.width/2, (size.height/2)-100);
        
        Sprite* exitPopup =Sprite::create("what.png");
        exitPopup->setPosition(size.width/2, size.height/2);
        
        EndPopupLayer->addChild(exitPopup, 6);
        EndPopupLayer->addChild(EndMenu,7);
        this->addChild(EndPopupLayer, 5);
    }
}

void GameMain::EndClickCallback(Ref* pSender)
{
    MenuItem* pMenuItem = (MenuItem *)pSender;
    Director *director = Director::getInstance();
    
    switch (pMenuItem->getTag()) {
        case EXIT:
            director->end();
            break;
        case CANCEL:
            popupS = false;
            this->removeChild(this->getChildByTag(ENDPOPLAYERTAG));
            break;
    }
}
