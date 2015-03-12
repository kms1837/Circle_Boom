#ifndef __GOPTION_H__
#define __GOPTION_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Management.h"

using namespace cocos2d::extension;

class OptionScene: public cocos2d::LayerColor
{
public:
    virtual bool init();
	static cocos2d::Scene* scene();
    /*
    void optionmenuClickCallback(cocos2d::Object* oSender);
    void valueChanged(cocos2d::Object *sender, cocos2d::extension::Control::EventType);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    
    void valueChanged2(cocos2d::Object* sender, cocos2d::extension::Control::EventType);
     */
	CREATE_FUNC(OptionScene);

private:
    /*
    cocos2d::extension::EditBox* m_pEditName;
    cocos2d::extension::EditBox* m_pEditPassword;
    cocos2d::extension::EditBox* m_pEditEmail;
     */
};

#endif