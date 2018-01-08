#include "circle.h"

using namespace std;

USING_NS_CC;

Circle* Circle::create(Scene* inScene) {
	Circle* newCircle = new Circle;
	newCircle->scene_ = inScene;

	return newCircle;
}

void Circle::createCircle() {
	createCircle("tempcircle.png");
}

void Circle::createCircle(string fileName) {
	float setX, setY;
	FadeIn *fade = FadeIn::create(0.5);

	Size winSize = CCDirector::getInstance()->getVisibleSize();

	circleObj* newCircle = new circleObj;
	Sprite* newCircleSprite = Sprite::create(fileName);
	
	int innerX = winSize.width - newCircleSprite->getContentSize().width;
	int innerY = winSize.height - newCircleSprite->getContentSize().height;

	do {
		setX = (rand() % innerX) + newCircleSprite->getContentSize().width;
		setY = (rand() % innerY) + newCircleSprite->getContentSize().height;
	} while (setX<30 || setX>innerX || setY<30 || setY>innerY);
	// 화면 안쪽으로 구체 배치

	newCircleSprite->setPosition(setX, setY);

	newCircleSprite->setOpacity(0);
	newCircle->sprite = newCircleSprite;

	newCircle->movePosition.x = setMovePosition[rand() % 2];
	newCircle->movePosition.y = setMovePosition[rand() % 2];

	newCircle->moveSpeed = setMoveSpeed[rand() % 2];

	newCircle->streak = MotionStreak::create(0.5, 3, 50, Color3B::WHITE, "paddle.png");

	circleList_.push_back(newCircle);
	scene_->addChild(newCircleSprite);
	scene_->addChild(newCircle->streak);

	newCircleSprite->runAction(fade);
}// 구체 생성, scene에 추가, 리스트에 추가

void Circle::running() {
	Size winSize = CCDirector::getInstance()->getVisibleSize();

	list<circleObj*>::iterator iter;
	for (iter = circleList_.begin(); iter != circleList_.end(); iter++) {
		Sprite* movedSprite = (*iter)->sprite;
		Vec2 position = (*iter)->sprite->getPosition();

		if (position.x > winSize.width || position.x < 0)
			(*iter)->movePosition.x *= -1;
		if (position.y > winSize.height || position.y < 0)
			(*iter)->movePosition.y *= -1;

		position.add((*iter)->movePosition);
		movedSprite->setPosition(position);
		(*iter)->streak->setPosition(position);
	}
}

/*
Circle* Circle::create(string fileName) {
	Circle* newCircle = new Circle;

	int temp1, temp2, tempX, tempY, temp;
    
	newCircle->circleList_ = new list<circleObj>;
	
	circleObj* headObj = new circleObj;
	headObj->sprite = CCSprite::create(fileName);

	circleList_->push_back(*headObj);
    
    Size size2 = CCDirector::getInstance()->getVisibleSize();
	Sprite* headObjSprite = headObj->sprite;
	temp1 = size2.width - headObjSprite->getContentSize().width;
	temp2 = size2.height - headObjSprite->getContentSize().height;
    
	do {
		tempX = (rand()%temp1) + headObjSprite->getContentSize().width;
		tempY = (rand()%temp2) + headObjSprite->getContentSize().height;
	} while(tempX<30 || tempX>temp1 || tempY<30 || tempY>temp2);
	
	headObjSprite->setPosition(tempX,tempY);
	headObj->timer = 0;
    
	temp = rand()%4;
	headObj->moveX = moveX[temp];
	headObj->moveY = moveY[temp];
    
	temp = rand()%2;
	headObj->moveSpeed = moveSpeedSetting[temp];
    
	return newCircle;
}//원형리스트 노드생성
*/
/*
list<Circle::comboLabelNode>* Circle::create()
{
	list<Circle::comboLabelNode>* circleList = new list<Circle::comboLabelNode>;

	return circleList;
}

void Circle::append(Circle::Circle** Head, circle::Circle* newCircle){
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

void circle::AppendCircle(circle::ComboLabelNode** Head, circle::ComboLabelNode* newLabel){
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

int circle::GetCircleCount(Circle* Head){
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

void circle::RemoveCircle(Circle* removeNode, Circle** Head){
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


void circle::RemoveCircle(ComboLabelNode* removeNode, ComboLabelNode** Head){
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

void circle::AllRemoveCircle(Circle** removeNode){
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

void circle::FadeCircle(Circle** list, Layer* childScene, std::string fileName){
	circle::Circle* temp;
    //int moveSpeed[3] = {1, 0.8, 0.6};
	Sprite* Spr_temp;
    
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

void circle::FlipCircle(Sprite* flipObject ,int x){
    if(x==1)flipObject->setFlippedX(true);
    else    flipObject->setFlippedX(false);
}*/