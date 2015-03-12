#ifndef __CircleBoom_xcode___EfeectQueue__
#define __CircleBoom_xcode___EfeectQueue__

#include "cocos2d.h"
#include "ObjectCircle.h"

class EffectQueue{
public:
    struct effectNode{
        cocos2d::ParticleSystemQuad* particle;
        effectNode* next;
    };
    
    struct QueueList{
        effectNode* Front;
        effectNode* Rear;
        int count;
    };

    
    void particleQueueCreate(QueueList** Queue);
    void particleAppend(QueueList* Queue, effectNode* newNode);
    
    void particleDequeue(QueueList** Queue);
    
    effectNode* particleNodeCreate(std::string particleName);
    
private:
    
};

#endif /* defined(__CircleBoom_xcode___EfeectQueue__) */
