#include "Playgame.h"
#include "GameMain.h"
#include <string.h>
#include <stdio.h>

using namespace cocos2d;
using namespace std;

Objectcircle::Circle* PlayGameCircleList = NULL;
Objectcircle::Circle* tempNode;
Objectcircle bbb;

ParticleSystem *particles[1000000];

Sprite* CPointF, *CPointE;
Sprite* temp[1000000];
//Sprite* Mcir[1000000]; //±∏√ºµÈ¿ª ¥„¿Ω
Sprite* ComboText;
Sprite* Danger;
Menu *gStopMenu;
Menu *gGameoverMenu;
Label* score;
Label* plusscore;
Label* pLabel;
Label* ComboLabel;
Label* stimeN;
Label* ScorePlusLabel;
Label* jum;
Label* jum2;
Label* jum3;
Label* wincircle;
Size size2;
Sprite* overtext;//∞‘¿”ø¿πˆ±€¿⁄
Sprite* backpopup;//≈¨∏ÆæÓ, ∞‘¿”ø¿πˆΩ√ ª˝±Ë

GameStopLayer* stoplayer;
GameClearLayer* Clayer;
GameOverLayer* overlayer;

float Mcirmove[1000000][3]={0,}; //∞¯¿« øÚ¡˜¿”¿ª ¥„¥¬∫Øºˆ
int Mcirboom[100][2]={0,}; //∆ƒ∆º≈¨¿ª ¿Áª˝Ω√≈≥ ¿ßƒ°¿˙¿Â∫Øºˆ
int Colorboom[1000000]={0,}; //∞¯¿« ªˆ¿ª¥„¥¬ ∫Øºˆ

int Pc=0;//∆ƒ∆º≈¨ ƒ´øÓ≈Õ

int streakS=0;//º±±ﬂ±‚ πˆ±◊πÊ¡ˆøÎ

int scorenum=0;//¡°ºˆ
int scoresum=0;//¡°ºˆ ø¨√‚øÎ ∫Øºˆ1
int scorecounter=0;//¡°ºˆ ø¨√‚øÎ ∫Øºˆ2
int scorecounterS=0;//¡°ºˆ∞° 1æøø¿∏£¥¬ø¨√‚Ω∫¿ßƒ°
int scoretimer=0;//1æøø¿∏£¥¬ ø¨√‚¿ª¿ß«— ≈∏¿Ã∏”∫Øºˆ
int scorecounttemp=0;
int scorecounterc=0;

int fristgame=1;//Ω√¿€Ω√ ƒ´øÓ∆Æ Ω∫¿ßƒ°
int gamestop=1;//∞‘¿”¿ª ¡§¡ˆ«‘(0-»∞º∫, 1-¡§¡ˆ)
int explosionS=0; //±∏√º∆¯πﬂ Ω∫¿ßƒ°(0-¥Î±‚, 1-∆¯πﬂ∏º«¿Áª˝)
int etimer=0; //∞≥√º∞£ ∆¯πﬂ∞£∞› Ω√∞£
int explosionNum;

int comboS=0; //ƒﬁ∫∏Ω∫¿ßƒ°
int combotimer=0; //ƒﬁ∫∏≈∏¿Ã∏”
int comboL=60*3; //ƒﬁ∫∏ ƒ´øÓ∆Æ ¿Ø»ø Ω√∞£
int combo=0; //ƒﬁ∫∏
int MaxCombo=0;//√÷¥Îƒﬁ∫∏
int timer=0;
int gSecond=1; //∞‘¿”Ω√∞£
int second=0;//√ (∫∏¿Ã¡ˆæ ¿Ω)
int minute=0;//∫–(∫∏¿Ã¡ˆæ ¿Ω)

int stimes=0; //¡§¡ˆ»ƒ ¥ŸΩ√ Ω««‡Ω√ 3√ ƒ´øÓ∆Æ∏¶ ¿ß«— ∫Øºˆ
int stime; //ƒ´øÓ∆Æ«“ √ (∞‘¿”Ω√¿€Ω√ø°µµ ªÁøÎ)
int stimer=0;

int WScircletimer=0;//«œæ·ªˆ ±∏√º∞° ≥™ø¿¥¬ ≈∏¿Ã∏”
int WScircleMaxtime=300;//«œæ·ªˆ ±∏√º∞° ≥™ø¿¥¬ Ω√∞£º≥¡§(60->1√ )
int WMaxCreate=51;//«œæ·ªˆ ±∏√ºª˝º∫ √÷¥Î∞πºˆ

int BlueS=0;//∆ƒ∂ıªˆ ±∏√º∞° ≥™ø¿≥ƒ æ»≥™ø¿≥™ Ω∫¿ßƒ°
int BScircletimer=0;//∆ƒ∂ıªˆ ±∏√º∞° ≥™ø¿¥¬ ≈∏¿Ã∏”
int BScircleMaxtime=0;
int BMaxCreate=0;
int BCreateCount=0;

int RedS=0;//ª°∞£ªˆ ±∏√º∞° ≥™ø¿≥ƒ æ»≥™ø¿≥™ Ω∫¿ßƒ°
int RScircletimer=0;//ª°∞£ªˆ ±∏√º∞° ≥™ø¿¥¬ ≈∏¿Ã∏”
int RScircleMaxtime=0;
int RMaxCreate=0;
int RCreateCount=0;

int catchC=3; //¿‚æ∆≥ªæﬂ«œ¥¬ ±∏√ººˆ
int MaxCircle=51; //√—±∏√ººˆ(≈¨∏ÆæÓ∆«¡§ø° ¿ÃøÎ)
int CountCircle=0; //«ˆ¿Á ¿‚æ∆≥Ω ±∏√ººˆ(≈¨∏ÆæÓ∆«¡§ø° ¿ÃøÎ)
float GameoverCircle=0;//∞‘¿”ø¿πˆ ¡∂∞«
int GameoverS = 0;//∞‘¿”ø¿πˆ Ω∫¿ßƒ°(1-∏µÁ±∏√º∞° º“∏Í)
int GameoverMenu = 0;//∞‘¿”ø¿πˆΩ√ ªÁøÎµ«æÓ¡ˆ¥¬ πˆ∆∞

int c=0,Mc=0; //mc->«ˆ¿Á »≠∏ÈªÛ¿« ±∏√º∞≥ºˆ
int tc = 0; //±◊∏≤∆«(≥™¡ﬂø° ¡ˆøÔ∞Õ)

float Max[5][3]={0,};
/* 0 - Ω√¿€¡°¿« ¡¬«•
   1 - X¿« √÷¥Î¡§¡°(y∞™µµ ∆˜«‘)
   2 - Y¿« √÷¥Î¡§¡°(x∞™µµ ∆˜«‘)
*/
float Min[2][3]={0,};
/*§∫
   0 - X¿« √÷º“¡§¡°(y∞™µµ ∆˜«‘)
   1 - Y¿« √÷º“¡§¡°(x∞™µµ ∆˜«‘)
*/
float my=0;
float MinY[2] = {99999,0};
float MaxY[2] = {0,0};
float MaxX[2] = {0,0};
float MinX[2] = {99999,0};
float tempmoveSpeed=0;

Playgame::Playgame()
{
    
}

Scene* Playgame::scene()
{
    Scene * scene = Scene::create();
    Playgame *layer = Playgame::create();
	scene->addChild(layer);
    return scene;
}

void Playgame::fristgamemmm(){ //∞‘¿” √ ±‚»≠ «‘ºˆ
	scorenum=0;//¡°ºˆ
	fristgame=1;//Ω√¿€Ω√ ƒ´øÓ∆Æ Ω∫¿ßƒ°
	gamestop=1;//∞‘¿”¿ª ¡§¡ˆ«‘(0-»∞º∫, 1-¡§¡ˆ)
	explosionS=0; //±∏√º∆¯πﬂ Ω∫¿ßƒ°(0-¥Î±‚, 1-∆¯πﬂ∏º«¿Áª˝)
	etimer=0; //∞≥√º∞£ ∆¯πﬂ∞£∞› Ω√∞£
	explosionNum=0;

	comboS=0; //ƒﬁ∫∏Ω∫¿ßƒ°
	combotimer=0; //ƒﬁ∫∏≈∏¿Ã∏”
	comboL=60*3; //ƒﬁ∫∏ ƒ´øÓ∆Æ ¿Ø»ø Ω√∞£
	combo=0; //ƒﬁ∫∏
	MaxCombo=0; //√÷¥Îƒﬁ∫∏
    
	timer=0;
	gSecond=1; //∞‘¿”Ω√∞£
	second=0;//√ (∫∏¿Ã¡ˆæ ¿Ω)
	minute=0;//∫–(∫∏¿Ã¡ˆæ ¿Ω)

	stimes=0; //¡§¡ˆ»ƒ ¥ŸΩ√ Ω««‡Ω√ 3√ ƒ´øÓ∆Æ∏¶ ¿ß«— ∫Øºˆ
	stime=0; //ƒ´øÓ∆Æ«“ √ (∞‘¿”Ω√¿€Ω√ø°µµ ªÁøÎ)
	stimer=0;

	WScircletimer=0;//«œæ·ªˆ ±∏√º∞° ≥™ø¿¥¬ ≈∏¿Ã∏”
	WScircleMaxtime=120;//«œæ·ªˆ ±∏√º∞° ≥™ø¿¥¬ Ω√∞£º≥¡§(60->1√ )
	WMaxCreate=51;//«œæ·ªˆ ±∏√ºª˝º∫ √÷¥Î∞πºˆ

	BlueS=0;//∆ƒ∂ıªˆ ±∏√º∞° ≥™ø¿≥ƒ æ»≥™ø¿≥™ Ω∫¿ßƒ°
	BScircletimer=0;//∆ƒ∂ıªˆ ±∏√º∞° ≥™ø¿¥¬ ≈∏¿Ã∏”
	BScircleMaxtime=600;
	BMaxCreate=0;
	BCreateCount=0;

	RedS=0;//ª°∞£ªˆ ±∏√º∞° ≥™ø¿≥ƒ æ»≥™ø¿≥™ Ω∫¿ßƒ°
	RScircletimer=0;//ª°∞£ªˆ ±∏√º∞° ≥™ø¿¥¬ ≈∏¿Ã∏”
	RScircleMaxtime=840;
	RMaxCreate=0;
	RCreateCount=0;

	catchC=3; //¿‚æ∆≥ªæﬂ«œ¥¬ ±∏√ººˆ
	MaxCircle=51; //√—±∏√ººˆ(≈¨∏ÆæÓ∆«¡§ø° ¿ÃøÎ)
	CountCircle=0; //«ˆ¿Á ¿‚æ∆≥Ω ±∏√ººˆ(≈¨∏ÆæÓ∆«¡§ø° ¿ÃøÎ)
	GameoverCircle=0;//∞‘¿”ø¿πˆ ¡∂∞«
	GameoverS = 0;//∞‘¿”ø¿πˆ Ω∫¿ßƒ°(1-∏µÁ±∏√º∞° º“∏Í)
	GameoverMenu = 0;//∞‘¿”ø¿πˆΩ√ ªÁøÎµ«æÓ¡ˆ¥¬ πˆ∆∞
	c=0,Mc=0; //mc->«ˆ¿Á »≠∏ÈªÛ¿« ±∏√º∞≥ºˆ

	//moveSpeed = 1; //¿Ãµøº”µµ
}

bool Playgame::init()
{

    fristgamemmm();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/SHORT_BGM_09.mp3");//πÃ∏Æ ∏ﬁ∏∏Æø° ø√∏≤
		
    if( !LayerColor::create(Color4B(255, 255, 255, 255)))return false;
		
    size2 = Director::getInstance()->getWinSize();
    m_Sae = CocosDenshion::SimpleAudioEngine::getInstance();

    //∞‘¿”√ ±‚ºº∆√
    Danger = Sprite::create("Danger.png");
    addChild(Danger,2);
    Danger->setPosition(size2.width/2, size2.height/2);
    Danger->setOpacity(0);

    //GameoverCircle=((float)MaxCircle/100)*60;
    GameoverCircle=50;//게임오버 조건
    //

    //√πΩ√¿€Ω√ ƒ´øÓ∆Æ
    fristgame = 1;
    stime = 3;
    stimeN = Label::createWithTTF("3", "∏º¿∫ ∞ÌµÒ", 40);
    stimeN->setPosition(size2.width/2,size2.height/2);
    addChild(stimeN,10);
    //

    //¿”Ω√ ¡°ºˆ∆«
    jum = Label::createWithTTF("sadasd", "Arial", 46.0);
    jum->setPosition(size2.width/2+200,size2.height/2+90);
    jum->setColor(Color3B(0,0,0));
    addChild(jum,10);
    jum->setOpacity(0);

    jum2 = Label::createWithTTF("sadasd", "Arial", 46.0);
    jum2->setPosition(size2.width/2+200,size2.height/2+13);
    jum2->setColor(Color3B(0,0,0));
    addChild(jum2,10);
    jum2->setOpacity(0);

    jum3 = Label::createWithTTF("sadasd", "Arial", 46.0);
    jum3->setPosition(size2.width/2+200,size2.height/2-60);
    jum3->setColor(Color3B(0,0,0));
    addChild(jum3,10);
    jum3->setOpacity(0);

    wincircle = Label::createWithTTF("0", "∏º¿∫ ∞ÌµÒ", 60);
    wincircle->setPosition(size2.width-40, 40);
    addChild(wincircle,2);
    //

    ComboText = Sprite::create("Good.png");
    ComboText->setPosition(size2.width/2, size2.height/2);
    addChild(ComboText,3);
    ComboText->setOpacity(0);

    //≈ÿΩ∫∆Æ
    pLabel = Label::createWithTTF("Ready?", "∏º¿∫ ∞ÌµÒ", 24);
    pLabel->setPosition(size2.width / 2, size2.height - 50);
    this->addChild(pLabel, 1);
    //

    //πË∞Ê
    Sprite* pSprite = Sprite::create("Pbackground1.png");
    pSprite->setPosition(size2.width/2, size2.height/2);
    this->addChild(pSprite, 0);
    //

    Label* scorename = Label::createWithTTF("score :", "∏º¿∫ ∞ÌµÒ", 20);
    scorename->setPosition(1120,720-30);
    addChild(scorename,2);

    ComboLabel = Label::createWithTTF("0 Combo","∏º¿∫ ∞ÌµÒ", 27); //ƒﬁ∫∏
    ComboLabel->setPosition(size2.width/2,size2.height/2);
    ComboLabel->setOpacity(0);
    addChild(ComboLabel,2);

    ScorePlusLabel = Label::createWithTTF("+0","∏º¿∫ ∞ÌµÒ", 20); //√ﬂ∞°µ»¡°ºˆ
    ScorePlusLabel->setPosition(size2.width/2,size2.height/2-100);
    ScorePlusLabel->setOpacity(0);
    addChild(ScorePlusLabel,2);

    score = Label::createWithTTF("0", "∏º¿∫ ∞ÌµÒ", 20);
    score->setPosition(1200,720-30);
    addChild(score,2);

    plusscore = Label::createWithTTF("0", "∏º¿∫ ∞ÌµÒ", 20);
    plusscore->setPosition(1200,720-50);
    plusscore->setOpacity(0);
    addChild(plusscore,2);
    
    MenuItemImage *gme1 = MenuItemImage::create("gamestopb.png",
                                                "gamestopb.png",
                                                CC_CALLBACK_1(Playgame::menuClickCallback, this));
    Menu *gmnuMain = Menu::create(gme1, NULL);

    gme1->setTag(7);
    gmnuMain->setPosition(64,720-50);
    addChild(gmnuMain,2);

    ////////////////////////////////////////¡§¡ˆºº∆√
    /*
    MenuItemImage *tempghomeb = MenuItemImage::create("homebutton.png",
                                                      "testbuttonpush.png",
                                                      CC_CALLBACK_1(GameStopLayer::StopClickCallback, this));
    tempghomeb->setTag(2);
    //¿”Ω√
    
    MenuItemImage *gRetryb = MenuItemImage::create("returnbutton.png",
                                                   "testbuttonpush.png",
                                                   CC_CALLBACK_1(GameStopLayer::StopClickCallback, this));

    MenuItemImage *ghomeb = MenuItemImage::create("homebutton.png",
                                                  "testbuttonpush.png",
                                                  CC_CALLBACK_1(GameStopLayer::StopClickCallback, this));
    
    gRetryb->setTag(1); ghomeb->setTag(2);
    
    gGameoverMenu = Menu::create(tempghomeb, NULL);
    gGameoverMenu->setVisible(false);
    gStopMenu = Menu::create(gRetryb, ghomeb, NULL);
    gStopMenu->setVisible(false);
    gStopMenu->setPosition(size2.width/2, size2.height/2);
    gGameoverMenu->setPosition(size2.width/2, size2.height/2);
    gStopMenu->alignItemsHorizontally();
    
    addChild(gStopMenu,10);
    addChild(gGameoverMenu,10);
     */
    /////////////////////////////////////////////////////////////////

		
		
    //∞≥√ºµÈ
    CPointF = Sprite::create("pointercircle.png"); //Ω√¿€¡°
    CPointF->setColor(Color3B(0,20,255));
    CPointF->setPosition(0,0);

    CPointE = Sprite::create("pointercircle.png"); //≥°¡°
    CPointE->setPosition(0,0);

    addChild(CPointE);
    addChild(CPointF);
    
    //초반구체 12개 생성
    for(int i=0; i<12; i++) FadeCircle();

    auto listener = EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(Playgame::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Playgame::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Playgame::onTouchesEnded, this);

    return true;
}

void Playgame::menuClickCallback(Ref* pSender)
{
	MenuItem *item = (MenuItem *)pSender;
	if(gamestop==0){
		switch(item->getTag()){
			case 5 :
				tc=1;
				break;
			case 6 :
				tc=0;
				break;
			case 7:
				gamestop=1;
				stoplayer = GameStopLayer::create();
				addChild(stoplayer, 5);
				break;
		}
	}
}

void Playgame::touchesBegan(__Set* touches, Event* event){
	if(gamestop==0){
		__SetIterator TouchPoint = touches->begin();
		Touch* touch = (Touch*)(*TouchPoint);
		Point location = touch->getLocation();
		CPointF->setPosition(location.x,location.y);
		Max[0][0] = location.x;
		Max[0][1] = location.y;
		//±◊∏±Ω√ º±¿Ã ≥™≈∏≥™µµ∑œ«‘
		if(location.x>=0&&location.x<=size2.width&&location.y>=0&&location.y<=size2.height){
            streak = MotionStreak::create(0.5, 3, 10, Color3B::WHITE, "paddle.png" );
			addChild(streak,4);
			streak->setPosition(location.x,location.y);
			streakS=1;
		}
		//

	}
}

void Playgame::touchesMoved(__Set* touches, Event* event)
{
	if(gamestop==0){
		__SetIterator TouchPoint = touches->begin();
		Touch* touch = (Touch*)(*TouchPoint);
		Point location = touch->getLocation();
		CPointE->setPosition(location.x, location.y);

		if(location.x>=0&&location.x<=size2.width&&location.y>=0&&location.y<=size2.height&&streakS==1){
			streak->setPosition(location.x,location.y);
		}

		if(MaxX[0]<location.x)MaxX[0]=location.x;MaxX[1]=location.y;
		if(MinX[0]>location.x)MinX[0]=location.x;MinX[1]=location.y;
		if(MaxY[1]<location.y)MaxY[1]=location.y;MaxY[0]=location.x;
		if(MinY[1]>location.y)MinY[1]=location.y;MaxY[0]=location.x;
		c++;
	}
}

void Playgame::touchesEnded(__Set* touches, cocos2d::Event* event)
{
	float tempX,tempY;
	int ccc=0;//원안에 들어온 구체의수를 담는변수
	//int ccc2=0;//구체의 색이 같은가를 담는 변수
	//int tempColor=0;//ªˆ±∏∫∞¿ª ¿ß«—
	int tempscore=0;//¿”Ω√¡°ºˆ
	char tempstring[20] = {0};
	if(gamestop==0){
		streakS=0;
		removeChild(streak,1);
        
        int circleCount = bbb.GetCircleCount(PlayGameCircleList);
        Objectcircle::Circle* tempCircle = PlayGameCircleList;
		if(circleCount>=0){
            while(tempCircle->next!=PlayGameCircleList){
				tempX=tempCircle->Mcir->getPositionX();
				tempY=tempCircle->Mcir->getPositionY();
                
				if(tempX<=MaxX[0] && tempX>=MinX[0] && tempY<=MaxY[1] && tempY>=MinY[1]){
					ccc++;
					Mcirboom[ccc][0]=tempX;
					Mcirboom[ccc][1]=tempY;
                    /*
					if(tempColor==0){
						ccc2++;
						tempColor=Colorboom[j];//∏«∏’¿˙ ¿ŒΩƒµ» ∞¯¿« ªˆ¿ª πﬁ¿Ω
					}else if(tempColor==Colorboom[j]){//∞∞¿∫ ªˆ¿« ∞¯¿Œ¡ˆ ∆«¥‹
						ccc2++;
					}*/
				}
                bbb.GetCircleCount(PlayGameCircleList);
                tempCircle = tempCircle->next;
			}

			if(ccc==catchC){ //터트리기 성공
				combo++;
				CountCircle = CountCircle+catchC;
				if(comboS==1){//이펙트 텍스트
					ActionInterval *MoveBy1 = FadeOut::create(0.5);
					ActionInterval *MoveBy2 = FadeIn::create(0.5);
					float temp = (float)combotimer/60.0;

					if(temp<=0.6){
						ComboText->setTexture("Exellent.png");
					}else if(temp<=1.1){
						ComboText->setTexture("Perfect.png");
					}else if(temp<=1.5){
						ComboText->setTexture("Great.png");
					}else if(temp<=1.9){
						ComboText->setTexture("Cool.png");
					}else if(temp<=2.4){
						ComboText->setTexture("Nice.png");
					}else{
						ComboText->setTexture("Good.png");
					}

					
					ActionInterval *MoveBy3 = FadeOut::create(1);
					ActionInterval *MoveBy4 = FadeOut::create(1);
					ActionInterval *MoveBy5 = FadeOut::create(1);
                    
                    //콤보점수 환산
					if(combo>=3){
						if(combo<7){
							tempscore = (combo-2)*100;
						}else if(combo<15){
							tempscore = 500+(combo-7)*150;
						}else if(combo<26){
							tempscore = 1700 +(combo-15)*250;
						}else if(combo<39){
							tempscore = 4450 +(combo-26)*400;
						}else if(combo<54){
							tempscore = 9650 +(combo-39)*600;
						}else{
							tempscore = 18650 +(combo-54)*1000;
						}
						scorenum = scorenum+(combo*100)+tempscore;

						sprintf(tempstring, " + %d",(combo*100)+tempscore);
						/*plusscore->setString(tempstring);
						plusscore->setOpacity(255);
						plusscore->runAction(MoveBy5);*/
					}else{
						tempscore=combo*100;
						scorenum = scorenum+tempscore;
						sprintf(tempstring, " + %d",tempscore);
					}

					plusscore->setString(tempstring);
					plusscore->setOpacity(255);
					plusscore->runAction(MoveBy5);

					sprintf(tempstring, "%d", scorenum);
					score->setString(tempstring);

					sprintf(tempstring, "+ %d", (combo*100)+tempscore);
					ScorePlusLabel->setString(tempstring);
					ScorePlusLabel->setOpacity(255);

					sprintf(tempstring, "%d Combo", combo);
					ComboLabel->setString(tempstring);
					ComboLabel->setOpacity(255);

					ComboLabel->runAction(MoveBy3);
					ScorePlusLabel->runAction(MoveBy4);
					//

					ComboLabel->setPosition(size2.width/2, size2.height/2-60);
					ComboLabel->setOpacity(255);
					//ComboText->setOpacity(255);
					ComboText->runAction(Sequence::create(MoveBy2, MoveBy1, NULL));
					//Log("√—≈∏¿Ã∏”:%d, %d/60=%f ",combotimer, combotimer, temp);
				}else{
					ActionInterval *MoveBy6 = FadeOut::create(1);

					tempscore=combo*100;
					scorenum = scorenum+tempscore;
					//scoresum=scoresum+tempscore;
					sprintf(tempstring, "%d", scorenum);
					score->setString(tempstring);

					sprintf(tempstring, " + %d",tempscore);
					plusscore->setString(tempstring);
					plusscore->setOpacity(255);
					plusscore->runAction(MoveBy6);

				}

				explosionNum=0;
				explosionS=1;
				comboS=1;
				combotimer=0;//콤보타이머
                tempCircle = PlayGameCircleList;
                int countttttt = 0;
                while(tempCircle->next!=PlayGameCircleList){
                    countttttt++;
                    tempX = tempCircle->Mcir->getPositionX();
                    tempY = tempCircle->Mcir->getPositionY();
                    if(tempX<=MaxX[0] && tempX>=MinX[0] && tempY<=MaxY[1] && tempY>=MinY[1]){
                        log("delete : %d",countttttt);
                        removeChild(tempCircle->Mcir,1);
                        //bbb.RemoveCircle(tempCircle);
                        circleCount = bbb.GetCircleCount(PlayGameCircleList);
                    }
                    tempCircle = tempCircle->next;
                }
                
                /*
				for(int z=1; z<=Mc ; z++)
                { //터트린 구체 제거
					for(int y=1; y<=Mc ; y++){
						//tempX=Mcir[y]->getPositionX();
						//tempY=Mcir[y]->getPositionY();
						if(tempX<=MaxX[0] && tempX>=MinX[0] && tempY<=MaxY[1] && tempY>=MinY[1]){
							log("Mcir[%d]delete",y);
							if(Mc>1){
								//removeChild(Mcir[y],1);
								Mc--;
								for(int j=y; j<=Mc; j++){
									Colorboom[j] = Colorboom[j+1];
									Mcirmove[j][0]=Mcirmove[j+1][0];
									Mcirmove[j][1]=Mcirmove[j+1][1];
									//Mcir[j]=Mcir[j+1];
								}
								if(Mc==1){
									//removeChild(Mcir[1],1);
									Mc--;
								}
							}
						}
					}
				}*/
			}
		}
		CPointF->setPosition(0,0);
		CPointE->setPosition(0,0);
		MaxX[0]=0;
		MaxY[1]=0;
		MinX[0]=99999;
		MinY[1]=99999;
	}
}

void Playgame::GameLogic(float dt){
	
    char tempstring[20] = {0};

	if(fristgame==1){ //3초 카운트
		if((stimer++)==60){
			m_Sae->playEffect("sound/Button_01.wav");
			stime--;
			stimer=0;
			sprintf(tempstring, "%d", stime);
			stimeN->setString(tempstring);
		}
		if(stime==0){
			gamestop=0;
			fristgame=0;
			removeChild(stimeN,10);
		}
	}

	if(stimes==1){ //일시정지후 다시 게임재개시 시간 카운터
		if((stimer++)==60){
			stime--;
			stimer=0;
			sprintf(tempstring, "%d", stime);
			stimeN->setString(tempstring);
		}
		if(stime==0){
			gamestop=0;
			stimes=0;
			removeChild(stimeN,10);
		}
	}

	if(gamestop==0 && stimes==0){
		if(comboS==1){ //ƒﬁ∫∏¿Ø¡ˆΩ√∞£
			if((combotimer++)==comboL){
				if(MaxCombo<combo)MaxCombo=combo;
				scorecounter=scorenum+scoresum;
				combo=0;
				comboS=0;
				scoresum=0;
				scorecounterS=1;
				for(int i=0;i<=Pc;i++){
					removeChild(particles[i], 4);
				}
				Pc=0;
			}
		}
        
		if(bbb.GetCircleCount(PlayGameCircleList)>=1){
			Objectcircle::Circle* tempCircle = PlayGameCircleList;
			for(int i=0;i<=bbb.GetCircleCount(PlayGameCircleList);i++){
                float tempX=tempCircle->Mcir->getPositionX();
                float tempY=tempCircle->Mcir->getPositionY();
                    
                if(tempX>size2.width  || tempX<0)tempCircle->moveX*=-1;
                if(tempY>size2.height || tempY<0)tempCircle->moveY*=-1;
                    
                tempX=tempX+tempCircle->moveX;
                tempY=tempY+tempCircle->moveY;
                tempCircle->Mcir->setPosition(tempX,tempY);
                tempCircle = tempCircle->next;
			}
		}
        
		if(explosionS==1){
			if(explosionNum==catchC){
				explosionS=0;
				explosionNum=0;
			}
			if((etimer++)==5){
				explosionNum++;
				etimer=0;
				boomParticles(Mcirboom[explosionNum][0],Mcirboom[explosionNum][1]);
				m_Sae->playEffect("sound/BossDDD.wav");
			}
		}

		if((timer++)==60){//카운터
			timer=0;
			second++;
			if(second!=0&&second%20==0&&WScircleMaxtime>0) WScircleMaxtime = WScircleMaxtime-3; //20초가 흐르면 생성속도를 빠르게 해준다.
			
            /*
            if(second==20) BlueS=1;//시간이 되면 파란색 구체가 등장
			if(second==45) RedS=1;//시간이 되면 빨간색 구체 등장
             
			gSecond--;
			if(gSecond<=0){ gameover();//시간이 초과됐을때 게임오버
			}
            */
            
		}

		if(bbb.GetCircleCount(PlayGameCircleList)>=GameoverCircle) gameover();//일정 수가 넘으면 게임오버
        
		sprintf(tempstring, "%d", second);
		pLabel->setString(tempstring);
        
        if((WScircletimer++)==WScircleMaxtime){
            WScircletimer=0;
            for(int w=0; w<=2; w++) FadeCircle();
        }//매 초마다 생성하게 해주는 역활

		/*
		if(BlueS==1){
			//if(RCreateCount < RMaxCreate){ //∆ƒ∂ıªˆ ±∏√ºª˝º∫
				if((BScircletimer++)==BScircleMaxtime){
					BScircletimer=0;
					for(int b=0; b<=2; b++) FadeCircle(Mc, 2);
				}
			//}
		}

		if(RedS==1){
			//if(RCreateCount < RMaxCreate){ //ª°∞£ªˆ ±∏√ºª˝º∫
				if((RScircletimer++)==RScircleMaxtime){
					RScircletimer=0;
					for(int r=0; r<=2; r++) FadeCircle(Mc, 3);
					}
				}
			//}
		}*/

		if(bbb.GetCircleCount(PlayGameCircleList)==0){	//구체를 모두 터트렸을때 9개를 생성한다.
			for(int i=0; i<=9; i++) FadeCircle();
		}
	}

	if(GameoverS==1){ //∞‘¿”ø¿πˆΩ√ «“ «‡¿ßµÈ
		if(bbb.GetCircleCount(PlayGameCircleList)>0){
			if((timer++)==2){
				timer=0;
				//boomParticles(Mcir[Mc]->getPositionX(),Mcir[Mc]->getPositionY());
				m_Sae->playEffect("sound/BossDDD.wav");
				//removeChild(Mcir[Mc],1);
				Mc--;
			}
		}else{
			if((timer++)==120){
				ActionInterval *FadeBy1 = FadeTo::create(1,0);
				overtext->runAction(FadeBy1);
			}
			if(overtext->getOpacity()==0){
				scoresum = 0;
				scorecounter = scorenum;

				sprintf(tempstring, "%d", 0);
				jum->setString(tempstring); //¡°ºˆ
				sprintf(tempstring, "%d", 0);
				jum2->setString(tempstring); //«√∑π¿Ã≈∏¿”
				sprintf(tempstring, "%d", 0);
				jum3->setString(tempstring); //ƒﬁ∫∏

				ActionInterval *FadeBy2 = FadeIn::create(1);
				ActionInterval *FadeBy3 = FadeIn::create(1);
				ActionInterval *FadeBy4 = FadeIn::create(1);
				ActionInterval *FadeBy5 = FadeIn::create(1);
				ActionInterval *FadeBy6 = FadeIn::create(1);
				backpopup->setVisible(true);

				gGameoverMenu->setVisible(true);
				gGameoverMenu->setPosition(size2.width/2,gStopMenu->getPositionY()-170);
				gGameoverMenu->setOpacity(0);
				gGameoverMenu->runAction(FadeBy2);

				backpopup->runAction(FadeBy6);
				jum->runAction(FadeBy3);
				jum2->runAction(FadeBy4);
				jum3->runAction(FadeBy5);
				removeChild(overtext,7);
				GameoverMenu=1;
				GameoverS=2;
				scorecounterc=1;
				scorecounterS=1;
			}
		}
	}else if(GameoverS==2){ //∞·∞˙√¢ ø¨√‚
			if(backpopup->getOpacity()==255){ //¡°ºˆ
				if(scorecounterS==1){
					if((scorecounter%10)!=scorecounttemp){
						if((scoretimer++)==3){
							scoretimer=0;
							scorecounttemp++;
							sprintf(tempstring, "%d", (scorecounttemp*scorecounterc)+scoresum);
							jum->setString(tempstring);
						}
					}else{
						scoresum = scoresum+(scorecounttemp*scorecounterc);
						scorecounter = scorecounter/10;
						scorecounterc = scorecounterc*10;
						scorecounttemp=0;
						if(scorecounter==0){
							sprintf(tempstring, "%d", scoresum); 
							jum->setString(tempstring);//0¿œ∂ß∏¶ ¥Î∫Ò«ÿ «—π¯¥ı √‚∑¬«‘

							scorecounterS=2;
							scoretimer=0;
						}
					}
				}else if(scorecounterS==2){ //«√∑π¿Ã ≈∏¿”
					if(scorecounttemp!=second){
						log("%d",scoretimer);
						if((scoretimer++)==1){
							scoretimer=1;
							scorecounttemp++;
							sprintf(tempstring, "%d", scorecounttemp);
							jum2->setString(tempstring);
						}
					}else{
						scorecounttemp=0;
						scorecounterS=3;
						scoretimer=0;
					}
				}
				if(scorecounterS==3){ //∏∆Ω∫ƒﬁ∫∏
					if(scorecounttemp!=MaxCombo){
						if((scoretimer++)==3){
							scoretimer=0;
							scorecounttemp++;
							sprintf(tempstring, "%d", scorecounttemp);
							jum3->setString(tempstring);
						}
					}else{
						scoretimer=0;
						scorecounterS=0;
						GameoverS=0;
					}
				}
			}
		}

	/*if(MaxCircle<=CountCircle){ //∞‘¿”≈¨∏ÆæÓ ¡∂∞«
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/SHORT_BGM_13.mp3");
		Clayer = GameClearLayer::create();
		addChild(Clayer,5);
		CountCircle=0;
		gamestop=1;
	}*/

	sprintf(tempstring, "%d", bbb.GetCircleCount(PlayGameCircleList)); //현재 구체수 표시
	wincircle->setString(tempstring);

	if(bbb.GetCircleCount(PlayGameCircleList)>40){ //40개 이상이면 경고를 해준다.
		wincircle->setColor(Color3B(255,0,0));
		Danger->setOpacity(255);
	}else{
		wincircle->setColor(Color3B(255,255,255));
		Danger->setOpacity(0);
	}

/*	if(scorecounterS==1){//¡°ºˆø¨√‚
		//if(scorenum==scorecounter)scorecounterS=0;
		if((scoretimer++)==1){
			scoretimer=0;
			if(scorecounter>0){
			scorenum=scorenum+(scorecounter/2);
			sprintf(tempstring, "%d", scorenum);
			score->setString(tempstring);
			}else{
			}
		}
	}*/

}

void Playgame::FadeCircle(){
	Objectcircle nnn;
	Objectcircle::Circle* temp;
	Sprite* Spr_temp;
    
	FadeIn *FadeBy = FadeIn::create(0.5);
	temp = nnn.Createcircle("circle3.png");
	Spr_temp = temp->Mcir;
	Spr_temp->setOpacity(0);
	this->addChild(Spr_temp);
	Spr_temp->runAction(FadeBy);
    log("1");
	nnn.AppendCircle(&PlayGameCircleList, temp);

}

void Playgame::boomParticles(int px, int py){ //∆ƒ∆º≈¨ «•Ω√
	Pc++;
    particles[Pc] = ParticleSystemQuad::create("ExplodingRing.plist");
	particles[Pc]->setPosition(px,py);
	addChild(particles[Pc],4);
}

void Playgame::gameover(){ //게임오버처리
	gamestop=1;
	GameoverS=1;
	timer=0;
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/SHORT_BGM_09.mp3");
    
	backpopup = Sprite::create("Result.png");
	backpopup->setPosition(size2.width/2, size2.height/2);
	backpopup->setVisible(false);
	backpopup->setOpacity(0);
    
	overtext = Sprite::create("gameover.png");
	overtext->setPosition(size2.width/2, size2.height/2);
	overlayer = GameOverLayer::create();
    
	addChild(overlayer,5);
	addChild(overtext,7);
	addChild(backpopup,6);
}

////////////////////////////일시정지//////////////////////////////

void GameStopLayer::onEnter(){
    Layer::onEnter();
	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 100));
	gStopMenu->setVisible(true);
	addChild(layer,5);
}

void GameStopLayer::StopClickCallback(Ref* stopSender){
	MenuItem* item      = (MenuItem *)stopSender;
    Director* director  = Director::getInstance();
	Scene* gMain;
	if(GameoverMenu==1){
		switch(item->getTag()){
			case 1:
				break;
			case 2:
				gMain = TransitionFade::create(0.8, GameMain::scene());
				director->pushScene(gMain);
				break;
		}
	}else{
		switch(item->getTag()){
			case 1:
				stime = 3;
				stimes = 1;
				stimeN = Label::createWithTTF("3", "맑은고딕", 40);
				stimeN->setPosition(size2.width/2,size2.height/2);
				addChild(stimeN,10);
				gStopMenu->setVisible(false);
				removeChild(stoplayer, 5);
				break;
			case 2:
				gamestop=0;
				gMain = TransitionFade::create(0.8, GameMain::scene());
				director->pushScene(gMain);
				break;
		}
	}
}

////////////////////////////게임 클리어//////////////////////////////

void GameClearLayer::onEnter(){
	LayerColor* layer = LayerColor::create(Color4B(255, 255, 255, 100));
	log("gameclear");
	addChild(layer,5);
}	


////////////////////////////게임 오버//////////////////////////////
void GameOverLayer::onEnter(){
    Layer::onEnter();
	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 100));
	/*backpopup = Sprite::create("popup.png");
	backpopup->setScale(0.6);
	backpopup->setOpacity(180);
	backpopup->setPosition(size2.width/2, size2.height/2);
	addChild(backpopup,6);*/
	addChild(layer,5);
}

