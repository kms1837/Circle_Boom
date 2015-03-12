#include "MainScene.h"
#include "OptionScene.h"
//#include "Playgame.h"
#include "gSelectScene.h"
#include "IntroScene.h"
#include "InGameScene.h"

#include <string>

using namespace cocos2d;

Objectcircle::Circle* HomeCircleList = NULL;

#define ABSOLUTE_PATHS "/Users/kms/development/workspace/CircleBoom-xcode-/CircleBoom-xcode-/Resources/"

int helpswitch=0, helpnum=1, maxhelpnum=3; // µµøÚ∏ª»∞º∫»≠, «ˆ¿Á µµøÚ∏ª¿ÃπÃ¡ˆ º˝¿⁄, µµøÚ∏ª ¿ÃπÃ¡ˆ¿« ∞πºˆ
int exits=0;
const std::string BackGroundimg[6] = {"Pbackground1.png","Pbackground2.png","Pbackground3.png","Pbackground4.png"};
const std::string hab[4]           = {"", "helpim1.png" , "helpim3.png","helpim9.png"};

Sprite* pSprite;
Sprite* tpSprite;
Sprite* gHelpT;
Size size;
Label* helppoint;

HelpLayer* hlayer;
GameEndLayer* elayer;
MainScene* main_layer;

Scene* mainScene;

Scene* MainScene::scene()
{
    mainScene = Scene::create();
    MainScene* main_layer = MainScene::create();
	mainScene->addChild(main_layer);

    return mainScene;

}

bool MainScene::init()
{
	size = Director::getInstance()->getWinSize();
    
	////////////////////////////////////////////////////////배경
    
	//mbacknum = (rand()%3)+1;
    int mainBack_randnum = (rand()%3)+1;
	pSprite = Sprite::create(BackGroundimg[mainBack_randnum]);
    pSprite->setPosition(size.width/2, size.height/2);
	pSprite->setOpacity(255);
    this->addChild(pSprite, 0);
	////////////////////////////////////////////////////////////////

	Sprite* imgGameTitle = Sprite::create("title.png");
	imgGameTitle->setPosition(size.width/2, size.height/2);
	this->addChild(imgGameTitle,6);

	MenuItemImage *helpb = MenuItemImage::create("helpbutton.png",
                                                 "testbuttonpush.png",
                                                 CC_CALLBACK_1(MainScene::menuClickCallback, this));
    //도움말

	Menu* pMenu = Menu::create(helpb, NULL);
    pMenu->setPosition(75,75);
	helpb->setTag(1);

	MenuItemImage *settingb = MenuItemImage::create("settingbutton.png",
                                                    "testbuttonpush.png",
                                                    CC_CALLBACK_1(MainScene::menuClickCallback, this));
    //옵션(미구현-표시안함상태)

	Menu* pMenu2 = Menu::create(settingb, NULL);
    pMenu2->setPosition(1200,75);
	settingb->setTag(2);

	MenuItemImage *playb = MenuItemImage::create("playb.png",
                                                 "playb.png",
                                                 CC_CALLBACK_1(MainScene::menuClickCallback, this));
    //게임시작

	MenuItemImage *exitb = MenuItemImage::create("exitb.png",
                                                 "exitb.png",
                                                 CC_CALLBACK_1(MainScene::menuClickCallback, this));
    //종료

	Menu* pMenu3 = Menu::create(playb, exitb, NULL);
	pMenu3->setPosition(size.width/2, 100);
	pMenu3->alignItemsVertically();
	playb->setTag(3); exitb->setTag(4);

	pMenu->setOpacity(0);
    
	pMenu2->setOpacity(0);
	pMenu2->setVisible(false);
    
	pMenu3->setOpacity(0);
    
	addChild(pMenu, 2);
	addChild(pMenu2, 2);
	addChild(pMenu3, 2);
    
    pMenu->runAction(Sequence::create(DelayTime::create(1.0),  FadeIn::create(1.0),NULL));
    pMenu3->runAction(Sequence::create(DelayTime::create(1.0), FadeIn::create(1.0),NULL));
    
	schedule(schedule_selector(MainScene::MainLogic));

	return true;
};

void MainScene::onEnter(){
    Layer::onEnter();
    for(int i=0; i<=39; i++) MainScene::FadeCircle(); //간지용 구체생성
}

void MainScene::menuClickCallback(Ref* pSender)
{
    Objectcircle temp;
	//char string[12] = {0};
    
	MenuItem *item = (MenuItem *)pSender;
	Scene *OptionS;
	Scene *SelectS;
	if(helpswitch==0){
		m_Sae->playEffect("sound/Button_04.wav");
		switch(item->getTag()){
			case 1://도움말 팝업
				helpswitch=1;
				hlayer = HelpLayer::create();
				addChild(hlayer,5);
				break;
			case 2: //옵션
				OptionS = TransitionFade::create(0.8, OptionScene::scene());
				Director::getInstance()->pushScene(OptionS);
				break;
			case 3: //게임플레이
                temp.AllRemoveCircle(&HomeCircleList);
				SelectS = TransitionFade::create(0.8, InGameScene::scene());
				Director::getInstance()->pushScene(SelectS);
				break;
			case 4: //게임종료팝업
				helpswitch=1;
				elayer = GameEndLayer::create();
				addChild(elayer, 5);
				break;
		}
	}
}

void MainScene::MainLogic(float dt){
	int temp;
	if(mchangeback==1){
		if(tpSprite->getOpacity()==255 && pSprite->getOpacity()==0){
			removeChild(tpSprite,1);
			pSprite->setTexture(BackGroundimg[mbacknum]);
			pSprite->setOpacity(255);
			mchangeback=0;
		}
	}else{
		if((mtimer++)==300){
			mtimer = 0;

			ActionInterval *FadeBy1 = FadeIn::create(2);
			ActionInterval *FadeBy2 = FadeOut::create(2);

			do{ temp = (rand()%4); }while(temp==mbacknum);
			mbacknum=temp;
			tpSprite = Sprite::create(BackGroundimg[mbacknum]);
			tpSprite->setPosition(size.width/2, size.height/2);
			tpSprite->setOpacity(0);
			this->addChild(tpSprite, 1);

			tpSprite -> runAction(FadeBy1);
			pSprite -> runAction(FadeBy2);
			mchangeback=1;

		}
	}
    
    //Objectcircle tempfunc;
    //int loop_circlecount = tempfunc.GetCircleCount(HomeCircleList);
    
    Objectcircle::Circle* tempnode = HomeCircleList;
    if(tempnode!=NULL){
        while(true){
            int tempX=tempnode->Mcir->getPositionX();
            int tempY=tempnode->Mcir->getPositionY();

            if(tempX>size.width  || tempX<0) tempnode->moveX *= -1;
            if(tempY>size.height || tempY<0) tempnode->moveY *= -1;
            
            tempnode->Mcir->setPosition(tempX+tempnode->moveX * 1, tempY+tempnode->moveY * 1);
            tempnode = tempnode->next;
            if(tempnode==HomeCircleList)break;
        }
    }
}

void MainScene::FadeCircle(){
	Objectcircle nnn;
	Objectcircle::Circle* temp;
    float moveSpeed[3] = {1.0, 0.8, 0.6};
	Sprite* Spr_temp;
    
    FadeIn *FadeBy = FadeIn::create(0.5);
	//FadeTo *FadeBy = FadeTo::create(0.5,(rand()%205)+50);
	temp = nnn.Createcircle("circle2.png");
    temp->moveSpeed = moveSpeed[rand()%3];
	Spr_temp = temp->Mcir;
    Spr_temp->setScale(-0.2);
	Spr_temp->setOpacity(0);
	this->addChild(Spr_temp,2);
	Spr_temp->runAction(FadeBy);
	nnn.AppendCircle(&HomeCircleList, temp);
}

//-----------------------------------도움말 팝업 레이어-----------------------------------
void HelpLayer::onEnter()
{
    Layer::onEnter();
	char string[12] = {0};
	LayerColor* help_layer = LayerColor::create(Color4B(0, 0, 0, 100));
	
	/*pMenu3->setVisible(false);
	help_Menu1->setVisible(true);
	hhMenu2->setVisible(true);*/
    
    MenuItemImage *helpb_Exit = MenuItemImage::create("Xbutton.png",
                                                      "Xbuttonpush.png",
                                                      CC_CALLBACK_1(HelpLayer::helpClickCallback, this));
    //종료버튼
    
	MenuItemImage *helpb_Next = MenuItemImage::create("sbutton.png",
                                                      "Xbuttonpush.png",
                                                      CC_CALLBACK_1(HelpLayer::helpClickCallback, this));
    //다음
    
	MenuItemImage *helpb_Prev = MenuItemImage::create("sbutton.png",
                                                      "Xbuttonpush.png",
                                                      CC_CALLBACK_1(HelpLayer::helpClickCallback, this));
    //이전
    
	helpb_Next->setRotation(180);
	
    Menu* help_Menu1 = Menu::create(helpb_Exit, NULL);
	help_Menu1->setPosition(size.width/2+180, size.height/2+230);
    
	Menu* help_Menu2 = Menu::create(helpb_Prev, helpb_Next, NULL);
	help_Menu2->alignItemsHorizontally();
	help_Menu2->setPosition(size.width/2, 110);
    
    
	helpb_Exit->setTag(1); helpb_Prev->setTag(2); helpb_Next->setTag(3);
    
	helpb_Prev->setPosition(-70,0);
	helpb_Next->setPosition(70,0);
    
	//help_Menu1->setVisible(false);
	//help_Menu2->setVisible(false);
	addChild(help_Menu1,7);
	addChild(help_Menu2,7);
    
	Sprite* gHelppopup = Sprite::create("helpback.png");
	gHelppopup->setPosition(size.width/2,size.height/2);
    addChild(gHelppopup,6);
    
	sprintf(string, "%d / %d", helpnum, maxhelpnum);
	helppoint = Label::createWithTTF(string, "맑은 고딕", 25);
	helppoint->setColor(Color3B(0,0,0));
	helppoint->setPosition(size.width / 2, 110);
    char *paths;
    strcpy(paths,ABSOLUTE_PATHS);
	Sprite* gHelpT = Sprite::create(strcpy(paths,hab[helpnum].c_str()));
    gHelpT->setPosition(size.width/2,size.height/2);
    
	hlayer->addChild(helppoint, 7);
	hlayer->addChild(gHelpT,7);
	hlayer->addChild(help_layer,5);
}

void HelpLayer::helpClickCallback(Ref* hSender)
{
	
	char string[12] = {0};
	MenuItem *item = (MenuItem *)hSender;
	switch(item->getTag()){
			case 1:
				helpswitch=0;
				removeChild(hlayer);
				break;
			case 2: //이전
				if(helpnum>1){
					m_Sae2->playEffect("sound/Button_04.wav");
					helpnum--;
					sprintf(string, "%d / %d", helpnum, maxhelpnum);
					helppoint->setString(string);
                    gHelpT->setTexture(hab[helpnum]);
                }
				break;
			case 3: //다음
				if(helpnum<maxhelpnum){
					m_Sae2->playEffect("sound/Button_04.wav");
					helpnum++;
					sprintf(string, "%d / %d", helpnum, maxhelpnum);
					helppoint->setString(string);
                    gHelpT->setTexture(hab[helpnum]);
				}
				break;
	}
	
}

//-----------------------------------게임종료 팝업 레이어-----------------------------------

void GameEndLayer::onEnter()
{
    Layer::onEnter();
	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 100));
    
    MenuItemImage* endpopb_end = MenuItemImage::create("closebutton.png",
                                                       "closebutton.png",
                                                       CC_CALLBACK_1(GameEndLayer::EndClickCallback, this));
    //종료
    
	MenuItemImage* endpopb_cancel = MenuItemImage::create("cancelbutton.png",
                                                          "bu1push.png",
                                                          CC_CALLBACK_1(GameEndLayer::EndClickCallback, this));
    //취소
    
	endpopb_end->setTag(1);
    endpopb_cancel->setTag(2);
    
	Menu* endpop_Menu = Menu::create(endpopb_end, endpopb_cancel, NULL);
	endpop_Menu->alignItemsHorizontally();
	endpop_Menu->setPosition(size.width/2, (size.height/2)-100);
	elayer->addChild(endpop_Menu, 7);
    
	Sprite* gExitpopup = Sprite::create("what.png");
	gExitpopup->setPosition(size.width/2, size.height/2);
	m_Sae3 = CocosDenshion::SimpleAudioEngine::getInstance();
	elayer->addChild(gExitpopup, 6);
	elayer->addChild(layer, 5);
}

void GameEndLayer::EndClickCallback(Ref* eSender)
{
	m_Sae3->playEffect("sound/Click.wav");
	MenuItem* item = (MenuItem*)eSender;
    
	switch(item->getTag()){
		case 1:
			Director::getInstance()->end();
			break;
		case 2:
			helpswitch=0;
            elayer->removeChild(elayer,true);
			break;
	}
}
