#include "MainMenu.h"
#include "Game.h"
#include "Help.h"

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
	//添加背景
	auto size=Director::getInstance()->getWinSize();
	auto spriteBK=Sprite::create("menu_bg.jpg");
	spriteBK->setPosition(Point(size.width/2,size.height/2));
	this->addChild(spriteBK);
	//添加2个菜单条目

	auto menuItemStart=MenuItemFont::create("Start",CC_CALLBACK_1(MainMenu::menuCallBack,this));
	auto menuItemHelp=MenuItemFont::create("Help",CC_CALLBACK_1(MainMenu::menuCallBack,this));
	menuItemStart->setTag(1);
	menuItemHelp->setTag(2);


	auto menu=Menu::create(menuItemStart,menuItemHelp,NULL);
	menu->setPosition(Point::ZERO);
	menuItemStart->setPosition(Point(size.width-menuItemStart->getContentSize().width-12,menuItemStart->getContentSize().height+70));
	menuItemHelp->setPosition(Point(size.width-menuItemHelp->getContentSize().width-25,menuItemHelp->getContentSize().height+30));

	menuItemStart->setColor(Color3B::BLACK);
	menuItemHelp->setColor(Color3B::BLACK);

	//menuItemStart->setFontSize(40);

	this->addChild(menu);
	return true;
}
void MainMenu::menuCallBack(Ref * obj)
{
	Node* node=(Node*)obj;
	Scene * scene=NULL;
	switch (node->getTag())
	{
	case 1:
		scene=Game::createScene();
		break;
	case 2:
		scene=Help::createScene();
		break;
	default:
		break;
	}
	Director::getInstance()->pushScene(scene);

}
