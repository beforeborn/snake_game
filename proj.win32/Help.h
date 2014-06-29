#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Help :
	public Layer
{
public:
	Help(void);
	~Help(void);
	CREATE_FUNC(Help);
	static Scene* createScene();

	virtual bool init();
	virtual void menuCallBack(Ref * ref);

};

