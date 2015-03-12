
#include "ItemShopScene.h"
#include "MainScene.h"

using namespace cocos2d;

Scene* ItemShopScene::scene()
{

    Scene * scene = Scene::create();
    ItemShopScene *layer = ItemShopScene::create();

	scene->addChild(layer);

    return scene;
}

bool ItemShopScene::init()
{
	if( !LayerColor::create(Color4B(0, 255, 255, 255))) return false;
	return true;
}