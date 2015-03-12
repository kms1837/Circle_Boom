#include "TestScene.h"

using namespace cocos2d;

Scene* TestScene::scene()
{

	Scene * scene = Scene::create();
    TestScene *layer = TestScene::create();
	scene->addChild(layer);

    return scene;

}

bool TestScene::init(){
    if( !LayerColor::create(Color4B(0, 0, 0, 0)))return false;
	return true;
}