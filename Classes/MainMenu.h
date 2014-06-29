#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MainMenu:public Layer
{
public:
	MainMenu(void);
	virtual ~MainMenu(void);

	static Scene * createScene();
	CREATE_FUNC(MainMenu);

	virtual bool init() override;
	virtual void menuCallBack(Ref * obj);

};

