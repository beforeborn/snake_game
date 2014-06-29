#include "Help.h"



Help::Help(void)
{
}


Help::~Help(void)
{
}

Scene* Help::createScene()
{
	auto scene=Scene::create();
	auto layer=Help::create();
	scene->addChild(layer);
	return scene;
}

bool Help::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto size=Director::getInstance()->getVisibleSize();

	Rect rect(0,0,size.width,size.height);
	
	auto spriteBG=Sprite::create("menu_bg.jpg",rect);
	spriteBG->setAnchorPoint(Point::ZERO);
	spriteBG->setPosition(0,0);

	this->addChild(spriteBG);

	Label* label=Label::create("Help","¿¬Ìå",30,size,TextHAlignment::CENTER,TextVAlignment::CENTER);
	label->setPosition(size.width/2,size.height/2+60);
	this->addChild(label);

	////Ìí¼Ó²Ëµ¥
	auto menuItemBack=MenuItemFont::create("Back",CC_CALLBACK_1(Help::menuCallBack,this));
	auto menu=Menu::create(menuItemBack,NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width-80,menuItemBack->getContentSize().height+30));
	menuItemBack->setColor(Color3B::GREEN);
	this->addChild(menu);
	

	return true;
}
void Help::menuCallBack(Ref * ref)
{
	Director::getInstance()->popScene();
}