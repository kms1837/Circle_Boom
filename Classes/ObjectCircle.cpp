#include "ObjectCircle.h"

using namespace cocos2d;

Objectcircle::Circle* Objectcircle::Createcircle(std::string fileName)
{
    float moveX[4]={-1,1,-1,1};
    float moveY[4]={1,1,-1,-1};
    //float moveX[4]={-1, -0.8, 0.8, 1};
    float moveSpeedSetting[3]={1, 1.3, 1.6};
	int temp1, temp2, tempX, tempY,temp;
    
	Circle* newcircle = new Circle;
	newcircle->next = NULL;
	newcircle->prev = NULL;
    newcircle->Mcir = CCSprite::create(fileName);
    
    Size size2 = CCDirector::getInstance()->getVisibleSize();
	temp1 = size2.width - newcircle->Mcir->getContentSize().width;
	temp2 = size2.height - newcircle->Mcir->getContentSize().height;
    
	do{
		tempX = (rand()%temp1)+newcircle->Mcir->getContentSize().width;
		tempY = (rand()%temp2)+newcircle->Mcir->getContentSize().height;
	}while(tempX<30 || tempX>temp1 || tempY<30 || tempY>temp2);
	
	newcircle->Mcir->setPosition(tempX,tempY);
    newcircle->timer = 0;
    
	temp = rand()%4;
	newcircle->moveX = moveX[temp];
	newcircle->moveY = moveY[temp];
    
	temp = rand()%2;
	newcircle->moveSpeed = moveSpeedSetting[temp];
    
	return newcircle;
}//원형리스트 노드생성

Objectcircle::ComboLabelNode* Objectcircle::Createcircle()
{
	ComboLabelNode* newcircle = new ComboLabelNode;
	newcircle->next = NULL;
	newcircle->prev = NULL;

	return newcircle;
}

void Objectcircle::AppendCircle(Objectcircle::Circle** Head, Objectcircle::Circle* newCircle){
	if((*Head) == NULL){
		*Head = newCircle;
		(*Head)->next = *Head;
		(*Head)->prev = *Head;
        (*Head)->nodenumber = 1;
        
	}else{
        Circle* Tail = (*Head)->prev;
        
        Tail->next->prev = newCircle;
        Tail->next = newCircle;

        newCircle->next = *Head;
        newCircle->prev = Tail;
        
        newCircle->nodenumber = newCircle->prev->nodenumber+1;
	}
}//리스트 노드연결

void Objectcircle::AppendCircle(Objectcircle::ComboLabelNode** Head, Objectcircle::ComboLabelNode* newLabel){
	if((*Head) == NULL){
		*Head = newLabel;
		(*Head)->next = *Head;
		(*Head)->prev = *Head;
        (*Head)->nodenumber = 1;
        
	}else{
        ComboLabelNode* Tail = (*Head)->prev;
        
        Tail->next->prev = newLabel;
        Tail->next = newLabel;
        
        newLabel->next = *Head;
        newLabel->prev = Tail;
        
        newLabel->nodenumber = newLabel->prev->nodenumber+1;
	}
}//리스트 노드연결2

int Objectcircle::GetCircleCount(Circle* Head){
    int count=0;
    if(Head!=NULL){
        Circle* searchNode = Head;
        while(searchNode->next!=Head){
            count++;
            searchNode = searchNode->next;
        }
        if(searchNode->next==Head)count++;
    }
    return count;
}//리스트의 노드수 카운터

void Objectcircle::RemoveCircle(Circle* removeNode, Circle** Head){
    if(removeNode!=NULL&&*Head!=NULL){
        if(removeNode==*Head){
            if((*Head)->next == *Head){ //순환방지
                (*Head)->next = NULL;
                (*Head)->prev = NULL;
                *Head = NULL;
                
                log("헤드제거");
            }else{
                (*Head)->next->prev = removeNode->prev; //헤드의 다음노드는 제거할 노드의 이전을 가르키게 된다.
                (*Head)->prev->next = removeNode->next; //헤드의 Tail의 다음노드는 제거할 노드의 다음노드가 된다.
                
                *Head = removeNode->next; //헤드교체
                
                removeNode->prev = NULL; //헤드 하나만 남으면 문제가 될 수 있기때문에 NULL값을 넣었다.
                removeNode->next = NULL;
                
                log("헤드교체");
            }
        }else{
            removeNode->next->prev = removeNode->prev;
            removeNode->prev->next = removeNode->next;
            
            removeNode->next = NULL;
            removeNode->prev = NULL;
        }
        
        delete removeNode;
    }
}//리스트의 노드 제거


void Objectcircle::RemoveCircle(ComboLabelNode* removeNode, ComboLabelNode** Head){
    if(removeNode==*Head){
        if((*Head)->next == *Head){ //순환방지
            (*Head)->next = NULL;
            (*Head)->prev = NULL;
            *Head = NULL;
        }else{
            (*Head)->next->prev = removeNode->prev; //헤드의 다음노드는 제거할 노드의 이전을 가르키게 된다.
            (*Head)->prev->next = removeNode->next; //헤드의 Tail의 다음노드는 제거할 노드의 다음노드가 된다.
            
            *Head = removeNode->next; //헤드교체
            
            removeNode->prev = NULL; //헤드 하나만 남으면 문제가 될 수 있기때문에 NULL값을 넣었다.
            removeNode->next = NULL;
            
            log("헤드교체");
        }
    }else{
        removeNode->next->prev = removeNode->prev;
        removeNode->prev->next = removeNode->next;
        
        removeNode->next = NULL;
        removeNode->prev = NULL;
    }
    
    delete removeNode;
}//리스트의 노드 제거2

void Objectcircle::AllRemoveCircle(Circle** removeNode){
    if(removeNode!=NULL){
        Circle* head = *removeNode;
        Circle* deleteNode;
        do{
            deleteNode = *removeNode;
            *removeNode = (*removeNode)->next;
            delete deleteNode;
        }while(*removeNode==head);
        
        delete *removeNode;
        
        *removeNode=NULL;
    }
}//리스트의 노드 모두제거

void Objectcircle::FadeCircle(Circle** list, Layer* childScene, std::string fileName){
	Objectcircle::Circle* temp;
    //int moveSpeed[3] = {1, 0.8, 0.6};
	Sprite* Spr_temp;
    
    /*cocos2d::extension::CCNodeLoaderLibrary *ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("Bug1", Bug1Loader::loader());*/
    
    FadeIn *FadeBy = FadeIn::create(0.5);
	temp = Createcircle(fileName); // A
    temp->streak = CCMotionStreak::create(1, 3, 70, Color3B::GREEN, "paddle.png");//페이드속도, 생성간격 , 너비, 색, 텍스쳐
    
    //temp->moveSpeed = moveSpeed[rand()%2+1];
    //temp->moveSpeed = rand()%2+1;
    temp->moveSpeed = UserDefault::getInstance()->getIntegerForKey("moveSpeed");
    
	Spr_temp = temp->Mcir; //B
	Spr_temp->setOpacity(0);
    
    FlipCircle(Spr_temp, temp->moveX);
    
	childScene->addChild(Spr_temp,2);
    childScene->addChild(temp->streak,1);
    
	Spr_temp->runAction(FadeBy);
	AppendCircle(&*list, temp);
    
    
}//객체생성 및 페이드

void Objectcircle::FlipCircle(Sprite* flipObject ,int x){
    if(x==1)flipObject->setFlippedX(true);
    else    flipObject->setFlippedX(false);
}
