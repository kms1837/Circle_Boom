#include "EfeectQueue.h"

void EffectQueue::particleQueueCreate(QueueList** Queue){
    *Queue = new QueueList;
    (*Queue)->Front = NULL;
    (*Queue)->Rear = NULL;
    (*Queue)->count = 0;
}


EffectQueue::effectNode* EffectQueue::particleNodeCreate(std::string particleName){
    EffectQueue::effectNode* newNode = new EffectQueue::effectNode;
    newNode->particle = cocos2d::ParticleSystemQuad::create(particleName);
    newNode->next = NULL;
    
    return newNode;
}

void EffectQueue::particleAppend(QueueList* Queue, effectNode* newNode){
    if(Queue->Front == NULL){
        Queue->Front = newNode;
        Queue->Rear = newNode;
        Queue->count++;
    }else{
        Queue->Rear->next = newNode;
        Queue->Rear = newNode;
        Queue->count++;
    }
}


void EffectQueue::particleDequeue(QueueList** Queue)
{
    if(*Queue!=NULL){
        if((*Queue)->Front->next == NULL){
            (*Queue)->Front = NULL;
            (*Queue)->Rear = NULL;
            delete (*Queue);
            
            (*Queue) = NULL;
            
        }else{
            EffectQueue::effectNode* tempFront = (*Queue)->Front;
            (*Queue)->Front = (*Queue)->Front->next;
            (*Queue)->count--;
            delete tempFront;
        }
        
    }
}

