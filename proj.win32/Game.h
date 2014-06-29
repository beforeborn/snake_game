#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Game : public Layer
{
public:
	Game(void);
	~Game(void);

	CREATE_FUNC(Game);
	static  Scene* createScene();
	virtual bool init();
	virtual void menuCallBack(Ref * obj);

	static int sepWidth;
	static int sepHeight;
	Vector<SnakeNode *> allBody;
};

