#ifndef __CircleBoom_xcode___dongeri__
#define __CircleBoom_xcode___dongeri__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

class dongeri : public cocos2d::Node, public cocosbuilder::NodeLoaderListener
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(dongeri, create);
    
    dongeri();
    virtual ~dongeri();
    
    virtual void onNodeLoaded(cocos2d::Node * pNode, cocosbuilder::NodeLoader * pNodeLoader);
    void setAnimationManager(cocos2d::ActionManager *pAnimationManager);
    
    void    update();
    void    setDirection( int dir );
    void    setIsDead( bool dead );
    
public:
    bool        isDeleted;
    
private:
    cocos2d::ActionManager *animationManager;
    cocos2d::Point velocity;
    bool isDead;
    int direction;
};

class CCBReader;

class dongeriLoader : public cocosbuilder::NodeLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(dongeri, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(dongeri);
};

#endif