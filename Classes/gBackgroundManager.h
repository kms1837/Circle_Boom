#ifndef __GBACKGROUNDMANGER_H__
#define __GBACKGROUNDMANGER_H__

#include "cocos2d.h"

class gMMM
{//백그라운드에 대한 정보를 담는 장소
	public:
		static int MT,MN,MB,MTimer;
		gMMM();
		virtual ~gMMM();
};

#endif

//사용안함