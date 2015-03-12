#include "gSelectScene.h"
#include "InGameScene.h"
#include "Playgame.h"

using namespace cocos2d;

//Sprite* tpSprite2;
//Size size2;
const char* sab[6] = {"Pbackground1.png","Pbackground2.png","Pbackground3.png","Pbackground4.png","Pbackground5.png","Pbackground6.png"};
Scene* gSelect::scene()
{

    Scene * scene = Scene::create();
	//scene = Scene::create();
    gSelect *layer = gSelect::create();
	scene->addChild(layer);

    return scene;

}

bool gSelect::init()
{
	if( !LayerColor::create(Color4B(255, 255, 255, 255))) return false;

	Size size = Director::sharedDirector()->getWinSize();
	/*Sprite* background = Sprite::create(sab[::MN]);
    background->setPosition(ccp(size.width/2, size.height/2));
	background->setOpacity(255);
    this->addChild(background, 0);*/

	MenuItemImage* me1 = MenuItemImage::create("backbutton.png",
                                               "testbuttonpush.png",
                                               CC_CALLBACK_1(gSelect::menuClickCallback, this));
                                               
	me1->setTag(1);
	Menu* pMenu = Menu::create(me1, NULL);
	pMenu->setPosition(80,size.height-80);

	addChild(pMenu);

	MenuItemImage* me2 = MenuItemImage::create("testbutton.png",
                                               "testbuttonpush.png",
                                               CC_CALLBACK_1(gSelect::menuClickCallback, this));
    
	me2->setTag(2);
	Menu* pMenu2 = Menu::create(me2, NULL);
	pMenu2->setPosition(size.width/2, size.height/2);

	addChild(pMenu2);

	return true;
};

void gSelect::menuClickCallback(Object* pSender){
	MenuItem *item = (MenuItem *)pSender;
	Scene *MainS = TransitionFade::create(0.8, InGameScene::scene());
	Scene *GameS = TransitionFade::create(0.8, Playgame::scene());
    
	switch(item->getTag()){
	case 1:  
		Director::getInstance()->pushScene(MainS);
		break;
	case 2:
		Director::getInstance()->pushScene(GameS);
		break;
	default :
		break;
	}
}

