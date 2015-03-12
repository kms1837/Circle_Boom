
#include "OptionScene.h"
#include "GameMain.h"
#include "Playgame.h"

#define SETTINGTAG0 0
#define SETTINGTAG1 1
#define SETTINGTAG2 2
#define SETTINGTAG3 3
#define SETTINGTAG4 4

#define SETTINGSTEPPERTAG0 10
#define SETTINGSTEPPERTAG1 11
#define SETTINGSTEPPERTAG2 12
#define SETTINGSTEPPERTAG3 13
#define SETTINGSTEPPERTAG4 14

using namespace cocos2d;

LabelTTF* optionScenetitle;

Scene* OptionScene::scene()
{
    Scene * scene = Scene::create();
    OptionScene *layer = OptionScene::create();

	scene->addChild(layer);

    return scene;
}

bool OptionScene::init()
{
	if( !LayerColor::initWithColor(Color4B(255, 80, 255, 100))) return false;
	Size size = Director::sharedDirector()->getWinSize();
    /*
	MenuItemImage *me1 = MenuItemImage::create("backbutton.png",
                                               "testbuttonpush.png",
                                                CC_CALLBACK_1(OptionScene::optionmenuClickCallback, this));

	Menu* pMenu = Menu::create(me1, NULL);
	pMenu->setPosition(size.width - 80,75);

	this->addChild(pMenu);

    //제목
	optionScenetitle = LabelTTF::create("Option", "맑은고딕", 34);
	optionScenetitle->setPosition(size.width / 2, size.height - 50);
	addChild(optionScenetitle);
	
    ////////////////////////
    //세팅들
    LabelTTF* setting0 = LabelTTF::create("콤보유지시간", "맑은고딕", 34);
	setting0->setPosition(size.width/2-50, size.height/2+200);
    setting0->setTag(SETTINGTAG0);
	addChild(setting0);
    
    LabelTTF* setting1 = LabelTTF::create("게임오버조건", "맑은고딕", 34);
	setting1->setPosition(size.width/2-50, size.height/2+100);
    setting1->setTag(SETTINGTAG1);
	addChild(setting1);
    
    LabelTTF* setting2 = LabelTTF::create("초가구체생성 속도", "맑은고딕", 34);
	setting2->setPosition(size.width/2-50, size.height/2);
    setting2->setTag(SETTINGTAG2);
	addChild(setting2);
    
    LabelTTF* setting3 = LabelTTF::create("이동속도", "맑은고딕", 34);
	setting3->setPosition(size.width/2-50, size.height/2-100);
    setting3->setTag(SETTINGTAG3);
	addChild(setting3);
    
    LabelTTF* setting4 = LabelTTF::create("원 그리기 거리제한", "맑은고딕", 34);
	setting4->setPosition(size.width/2-50, size.height/2-200);
    setting4->setTag(SETTINGTAG4);
	addChild(setting4);
    
    //슬라이더바 세팅
    
	cocos2d::extension::ControlSlider *slider = cocos2d::extension::ControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
    slider->setAnchorPoint(Vec2(0.5f, 1.0f));
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(100.0f); // Sets the max value of range
    slider->setPosition(size.width / 2.0f, size.height / 2 - 300);

    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(this, control_selector(OptionScene::valueChanged), ControlEventValueChanged);
	addChild(slider);
    
    Point visibleOrigin = GLView::sharedOpenGLView()->getVisibleOrigin();
    Size visibleSize = GLView::sharedOpenGLView()->getVisibleSize();
    Size editBoxSize = CCSizeMake(visibleSize.width - 100, 60);
    
    m_pEditName = EditBox::create(editBoxSize, Scale9Sprite::create("Pbackground1.png"));
    m_pEditName->setPosition(p(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
    m_pEditName->setFontName("맑은 고딕");
    m_pEditName->setFontSize(50);
    m_pEditName->setFontColor(wHITE);
    m_pEditName->setPlaceHolder("아직 세팅되지 않음");
    m_pEditName->setPlaceholderFontColor(WHITE);
    m_pEditName->setMaxLength(50);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    //m_pEditName->setDelegate(this);
    //addChild(m_pEditName);
    
    Sprite *minusSprite0 = Sprite::create("other1.png");
    Sprite *plusSprite0  = Sprite::create("other1.png");
    
    //게임오버조건
    extension::ControlStepper *stepper0 = extension::ControlStepper::create(minusSprite0, plusSprite0);
    stepper0->setPosition(size.width/2+200, size.height/2+200);
    stepper0->addTargetWithActionForControlEvents(this, control_selector(OptionScene::valueChanged2), ControlEventValueChanged);
    stepper0->setMinimumValue(1);
    stepper0->setMaximumValue(20);
    stepper0->setValue((double)UserDefault::sharedUserDefault()->getIntegerForKey("gameComboTimer"));
    stepper0->setTag(SETTINGSTEPPERTAG0);
    addChild(stepper0);

    
    Sprite *minusSprite = Sprite::create("other1.png");
    Sprite *plusSprite  = Sprite::create("other1.png");
    
    //게임오버조건
    extension::ControlStepper *stepper1 = extension::ControlStepper::create(minusSprite, plusSprite);
    stepper1->setPosition(size.width/2+200, size.height/2+100);
    stepper1->addTargetWithActionForControlEvents(this, control_selector(OptionScene::valueChanged2), ControlEventValueChanged);
    stepper1->setMinimumValue(30);
    stepper1->setMaximumValue(100);
    stepper1->setValue((double)UserDefault::sharedUserDefault()->getIntegerForKey("gameOverCircle"));
    stepper1->setTag(SETTINGSTEPPERTAG1);
    addChild(stepper1);
    
    Sprite *minusSprite2 = Sprite::create("other1.png");
    Sprite *plusSprite2  = Sprite::create("other1.png");
    
    //구체생성속도
    extension::ControlStepper *stepper2 = extension::ControlStepper::create(minusSprite2, plusSprite2);
    stepper2->setPosition(size.width/2+200, size.height/2);
    stepper2->addTargetWithActionForControlEvents(this, control_selector(OptionScene::valueChanged2), ControlEventValueChanged);
    stepper2->setMinimumValue(1);
    stepper2->setMaximumValue(10);
    stepper2->setValue((double)UserDefault::sharedUserDefault()->getFloatForKey("createSpeed"));
    stepper2->setTag(SETTINGSTEPPERTAG2);
    addChild(stepper2);
    
    Sprite *minusSprite3 = Sprite::create("other1.png");
    Sprite *plusSprite3  = Sprite::create("other1.png");
    
    //구체이동속도
    extension::ControlStepper *stepper3 = extension::ControlStepper::create(minusSprite3, plusSprite3);
    stepper3->setPosition(size.width/2+200, size.height/2-100);
    stepper3->addTargetWithActionForControlEvents(this, control_selector(OptionScene::valueChanged2), ControlEventValueChanged);
    stepper3->setMinimumValue(1);
    stepper3->setMaximumValue(10);
    stepper3->setValue((double)UserDefault::sharedUserDefault()->getIntegerForKey("moveSpeed"));
    stepper3->setTag(SETTINGSTEPPERTAG3);
    addChild(stepper3);
    
    Sprite *minusSprite4 = Sprite::create("other1.png");
    Sprite *plusSprite4  = Sprite::create("other1.png");
    
    //원 그리기 제한
    extension::ControlStepper *stepper4 = extension::ControlStepper::create(minusSprite4, plusSprite4);
    stepper4->setPosition(size.width/2+200, size.height/2-200);
    stepper4->addTargetWithActionForControlEvents(this, control_selector(OptionScene::valueChanged2), ControlEventValueChanged);
    stepper4->setMinimumValue(50);
    stepper4->setMaximumValue(300);
    stepper4->setValue((double)UserDefault::sharedUserDefault()->getIntegerForKey("distance"));
    stepper4->setTag(SETTINGSTEPPERTAG4);
    addChild(stepper4);
    
	
     */
    return true;
}

/*
#pragma mark -슬라이더바

void OptionScene::optionmenuClickCallback(Object* oSender)
{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, GameMain::scene()));
}

void OptionScene::valueChanged(Object* sender, ControlEvent* controlEvent)
{
    ControlSlider* item = (ControlSlider* )sender;
    optionScenetitle->setString(String::createWithFormat("%f", item->getValue())->getCString());
    
}

#pragma mark -텍스트박스

void OptionScene::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    CCLog("editBox %p DidBegin !", editBox);
}

void OptionScene::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    CCLog("editBox %p DidEnd !", editBox);
}

void OptionScene::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

#pragma mark -플마바

void OptionScene::valueChanged2(Object *sender, ControlEvent controlEvent)
{
    ControlStepper* item = (ControlStepper *)sender;
    LabelTTF* tempLabel=NULL;
    switch (item->getTag())
    {
        case SETTINGSTEPPERTAG0:
            tempLabel = (LabelTTF*)this->getChildByTag(SETTINGTAG0);
            UserDefault::sharedUserDefault()->setIntegerForKey("gameComboTimer", item->getValue());
            break;
        case SETTINGSTEPPERTAG1:
            tempLabel = (LabelTTF*)this->getChildByTag(SETTINGTAG1);
            UserDefault::sharedUserDefault()->setIntegerForKey("gameOverCircle", item->getValue());
            break;
        case SETTINGSTEPPERTAG2:
            tempLabel = (LabelTTF*)this->getChildByTag(SETTINGTAG2);
            UserDefault::sharedUserDefault()->setFloatForKey("createSpeed", item->getValue());
            break;
        case SETTINGSTEPPERTAG3:
            tempLabel = (LabelTTF*)this->getChildByTag(SETTINGTAG3);
            UserDefault::sharedUserDefault()->setIntegerForKey("moveSpeed", item->getValue());
            break;
        case SETTINGSTEPPERTAG4:
            tempLabel = (LabelTTF*)this->getChildByTag(SETTINGTAG4);
            UserDefault::sharedUserDefault()->setIntegerForKey("distance", item->getValue());
            break;
    }
    
    if(tempLabel!=NULL){
        tempLabel->setString(String::createWithFormat("%d", (int)item->getValue())->getCString());
    }
    
}
 */
