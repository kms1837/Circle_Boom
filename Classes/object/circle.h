#include <list>
#include "cocos2d.h"

class Circle
{
public:
    struct circleObj {
		cocos2d::Sprite* sprite;
		cocos2d::Vec2 movePosition; // 이동각도
		cocos2d::MotionStreak *streak; // 잔상
		int color;
        int timer;

		float moveSpeed; // 이동 속도
	};
    /*
    struct comboLabelNode{
        cocos2d::Label* comboLable;
		comboLabelNode* next;
		comboLabelNode* prev;
        
        int nodenumber;
    };*/
    
	static Circle* create(cocos2d::Scene*);

	void createCircle();
	void createCircle(std::string fileName);
	void running();

	//static Circle* create(std::string fileName); // 리스트 생성
	
	/*
	void append(circleObj** Head, circleObj* newCircle);  //리스트에 구체추가
    void append(comboLabelNode** Head, comboLabelNode* newCircle);
    
    void RemoveCircle(Circle* removeNode, Circle** Head); //구체삭제
    void RemoveCircle(ComboLabelNode* removeNode, ComboLabelNode** Head);
    
    void AllRemoveCircle(Circle** removeNode);
    //구체를 전체삭제하는 함수
    void FadeCircle(Circle** List, cocos2d::Layer* childScene, std::string fileName);
    //페이드인을 하며 구체를 생성하고 리스트에 추가하는 함수
    void FlipCircle(cocos2d::Sprite* flipObject ,int x);
    //구체를 뒤집는 함수
    int GetCircleCount(Circle* Head);
    //구체수를 세는 함수*/
private:
	std::list<circleObj*> circleList_;
	cocos2d::Scene* scene_;

	double setMovePosition[2] = { -1, 1 };
	double setMoveSpeed[3] = { 1, 1.3, 1.6 };
};
