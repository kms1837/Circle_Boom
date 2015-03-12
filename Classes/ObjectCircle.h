#ifndef __CircleBoom_xcode___ObjectCircle__
#define __CircleBoom_xcode___ObjectCircle__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "dongeri.h"

class Objectcircle
{
public:
    struct Circle{
		cocos2d::Sprite* Mcir;
        cocos2d::MotionStreak *streak;
		int moveX;
		int moveY;
		float moveSpeed;
		int color;
        int timer;
		Circle* next;
		Circle* prev;
        
        int nodenumber;//버그탐색용 삭제무관 Append에 관련 머가 있으니까 제거해도됨
	};
    
    struct ComboLabelNode{
        cocos2d::LabelTTF* comboLable;
        ComboLabelNode* next;
		ComboLabelNode* prev;
        
        int nodenumber;
    };
    
    Circle* Createcircle(std::string fileName); //구체생성
    ComboLabelNode* Createcircle();
	void AppendCircle(Circle** Head, Circle* newCircle);  //리스트에 구체추가
    void AppendCircle(ComboLabelNode** Head, ComboLabelNode* newCircle);
    
    void RemoveCircle(Circle* removeNode, Circle** Head); //구체삭제
    void RemoveCircle(ComboLabelNode* removeNode, ComboLabelNode** Head);
    
    void AllRemoveCircle(Circle** removeNode);
    //구체를 전체삭제하는 함수
    void FadeCircle(Circle** List, cocos2d::Layer* childScene, std::string fileName);
    //페이드인을 하며 구체를 생성하고 리스트에 추가하는 함수
    void FlipCircle(cocos2d::Sprite* flipObject ,int x);
    //구체를 뒤집는 함수
    int GetCircleCount(Circle* Head);
    //구체수를 세는 함수
};

#endif /* defined(__CircleBoom_xcode___ObjectCircle__) */
