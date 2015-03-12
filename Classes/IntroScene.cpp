
#include "IntroScene.h"
#include "MainScene.h"
#include "GameMain.h"
#include "TutorialScene.h"

using namespace cocos2d;

Sprite* teammark;//¿Œ∆Æ∑Œ ∏∂≈©

Scene* IntroScene::scene()
{

	Scene *scene  = Scene::create();
    IntroScene *layer = IntroScene::create();
	scene->addChild(layer);

    return scene;

}

bool IntroScene::init(){
	if( !LayerColor::initWithColor(Color4B(0, 0, 0, 0))) return false;
	Size size = Director::getInstance()->getWinSize();
	teammark = CCSprite::create("jack.png");
	teammark->setPosition(size.width/2, size.height/2);
	teammark->setOpacity(0);
	addChild(teammark);
	return true;
}

void IntroScene::onEnter()
{
	CCLayer::onEnter();
	teammark->runAction(CCSequence::create(FadeIn::create(1.0),
										   DelayTime::create(1.0),
										   FadeOut::create(1.0f),
										   callfunc_selector(IntroScene::sceneReplace),NULL));
    //runAction
}

void IntroScene::sceneReplace()
{
    Scene* mainScene = TransitionFade::create(0.8, TutorialScene::scene());
	Director::getInstance()-> replaceScene(mainScene);
}