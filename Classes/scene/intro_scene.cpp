
#include "Intro_scene.h"
#include "TutorialScene.h"

USING_NS_CC;

Sprite* teammark;

Scene* IntroScene::scene() {
    return IntroScene::create();
}

bool IntroScene::init() {

	if (!Scene::init()) {
		return false;
	}

	Size size = Director::getInstance()->getWinSize();
	teammark = Sprite::create("jack.png");
	teammark->setPosition(size.width/2, size.height/2);
	teammark->setOpacity(0);
	this->addChild(teammark);

	auto moveScene = CallFunc::create([]() {
		Scene* mainScene = TransitionFade::create(0.8, TutorialScene::scene());
		Director::getInstance()->replaceScene(mainScene);
	});

	
	auto sequence = Sequence::create(FadeIn::create(1.0),
	DelayTime::create(1.0),
	FadeOut::create(1.0f),
	moveScene, nullptr);

	teammark->runAction(sequence);
	

	return true;
}
