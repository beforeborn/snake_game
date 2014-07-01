#pragma once
#include "cocos2d.h"
#include "SnakeNode.h"

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
	virtual void moveBodys();
	virtual void addBody(SnakeNode* body);
   //定期执行更新
	virtual void updateFrame(float t);

	static float sepTime;
	static int sepWidth;
	static int sepHeight;
	//Rect * edgeRect;
	Vector<SnakeNode *> allBody;
	SnakeNode* head;
	SnakeNode* food;

};

