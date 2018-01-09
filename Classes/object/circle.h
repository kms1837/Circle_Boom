#include <list>
#include "cocos2d.h"
#include "common\utility.h"

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
    
	static Circle* create(cocos2d::Scene*);

	// util
	void createCircle();
	void createCircle(std::string fileName);
	void styleClear();
	void running();

	// getter & setter
	std::list<circleObj*> getCircles();
	std::list<circleObj*> getInnerCircles(std::list<cocos2d::Vec2> points);

	void remove(circleObj* removeCircle);

private:
	const int kSpriteDepth = 2;
	const int kStreakDepth = 1;
	const std::string kDeadEffect = "ExplodingRing.plist";

	std::list<circleObj*> circleList_;
	cocos2d::Scene* scene_;

	double setMovePosition[2] = { -1, 1 };
	double setMoveSpeed[3] = { 1, 1.3, 1.6 };
};
