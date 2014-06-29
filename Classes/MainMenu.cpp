#include "MainMenu.h"


MainMenu::MainMenu(void)
{
}


MainMenu::~MainMenu(void)
{
}

Scene * MainMenu::createScene()
{
	auto scene=Scene::create();
	auto layer=MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//��ӱ���
	auto size=Director::getInstance()->getWinSize();
	auto spriteBK=Sprite::create("");
	spriteBK->setPosition(Point(size.width/2,size.height/2));
	this->addChild(spriteBK);
	//���2���˵���Ŀ

	auto menuItemStart=MenuItemFont::create("Start",CC_CALLBACK_1(MainMenu::menuCallBack,this));
	auto menuItemHelp=MenuItemFont::create("Help",CC_CALLBACK_1(MainMenu::menuCallBack,this));

	auto menu=Menu::create(menuItemStart,menuItemHelp,NULL);
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point(size.width-menuItemStart->getContentSize().width-10,size.height-menuItemStart->getContentSize().height-70));
	menu->setPosition(Point(size.width-menuItemHelp->getContentSize().width-10,size.height-menuItemHelp->getContentSize().height-30));

	return true;
}
void menuCallBack(Ref * obj)
{

}
