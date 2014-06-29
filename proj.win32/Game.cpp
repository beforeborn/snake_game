#include "Game.h"


enum class ENUM_DIR
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_STOP
};

enum class ENUM_TYPE
{
	TYPE_HEAD=1,
	TYPE_BODY,
	TYPE_FOOD
};
class SnakeNode:public Sprite
{
public:
	ENUM_DIR m_dir;
	ENUM_TYPE nodeType;//1表示舌头，2表示身体，3表示食物
	static SnakeNode* create(ENUM_TYPE type);
	bool init(ENUM_TYPE type);
	void gameLogic(float t);
private:
	float scaleNodeX;
	float scaleNodeY;
};
bool SnakeNode::init(ENUM_TYPE type)
{
	if(!Sprite::init())
	{
		return false;
	}
	Sprite* node=NULL;
	this->nodeType=type;
	switch(type)
	{
	case ENUM_TYPE::TYPE_HEAD:
		node=Sprite::create("head.jpg");
		node->setAnchorPoint(Point::ZERO);
		node->setPosition(Point::ZERO);
		m_dir=ENUM_DIR::DIR_RIGHT;

		break;
	case ENUM_TYPE::TYPE_BODY:
		node=Sprite::create("body.jpg");
		m_dir=ENUM_DIR::DIR_STOP;
		break;
	case ENUM_TYPE::TYPE_FOOD:
		node=Sprite::create("food.jpg");
		int row=rand()%10;
		int col=rand()%10;

		node->setAnchorPoint(Point::ZERO);
		node->setPosition(row*Game::sepWidth,col*Game::sepHeight);
		m_dir=ENUM_DIR::DIR_STOP;
		break;
	}
	scaleNodeX=Game::sepWidth/node->getContentSize().width;
	scaleNodeY=Game::sepHeight/node->getContentSize().height;
	node->setScaleX(scaleNodeX);
	node->setScaleY(scaleNodeY);

	this->addChild(node);

	this->schedule(schedule_selector(SnakeNode::gameLogic),0.5);

	return true;
}

SnakeNode* SnakeNode::create(ENUM_TYPE type)
{
	SnakeNode * node=new SnakeNode();
	if(node&&node->init(type))
	{
		node->autorelease();
		return node;
	}else
	{
		delete node;
		node=NULL;
		return NULL;
	}

}

void SnakeNode::gameLogic(float t)
{
	switch(m_dir)
	{
	case ENUM_DIR::DIR_RIGHT:
		this->runAction(MoveBy::create(0.3,Point(Game::sepWidth,0)));
		break;
	case ENUM_DIR::DIR_LEFT:
		this->runAction(MoveBy::create(0.3,Point(-Game::sepWidth,0)));
		break;
	case ENUM_DIR::DIR_UP:
		this->runAction(MoveBy::create(0.3,Point(0,Game::sepHeight)));
		break;
	case ENUM_DIR::DIR_DOWN:
		this->runAction(MoveBy::create(0.3,Point(0,-Game::sepHeight)));
		break;
	case ENUM_DIR::DIR_STOP:
		break;
	default:
		break;
	}

}
void setDir(SnakeNode *node,int touchX,int touchY,int nodeX,int nodeY);

Game::Game(void)
{
}


Game::~Game(void)
{
}

int Game::sepHeight=0;
int Game::sepWidth=0;
SnakeNode* head=NULL;
Scene* Game::createScene()
{
	Scene* scene=Scene::create();
	Layer* layer=Game::create();
	scene->addChild(layer);
	return scene;
}
bool Game::init()
{
	if(!Layer::init())
	{

		return false;
	}
	//添加背景
	auto size=Director::getInstance()->getWinSize();
	auto gameBG=Sprite::create("game_bg.jpg");
	gameBG->setAnchorPoint(Point::ZERO);
	gameBG->setPosition(0,0);
	gameBG->setOpacity(75);
	int bgWidth=gameBG->getContentSize().width;
	int bgHeight=gameBG->getContentSize().height;

	float scaleX=size.width/bgWidth;
	float scaleY=size.height/bgHeight; 

	gameBG->setScaleX(scaleX);
	gameBG->setScaleY(scaleY);

	this->addChild(gameBG);

	//分数显示
	auto scoreLabel=Label::create("Hello World","Arial",24);
	scoreLabel->setPosition(Vec2(size.width-80,size.height-50));
	this->addChild(scoreLabel);

	////添加菜单
	auto menuItemBack=MenuItemFont::create("Back",CC_CALLBACK_1(Game::menuCallBack,this));
	auto menu=Menu::create(menuItemBack,NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width-80,menuItemBack->getContentSize().height+30));
	menuItemBack->setColor(Color3B::GREEN);
	this->addChild(menu);

	//添加地图
	auto draw=DrawNode::create();
	draw->setAnchorPoint(Point::ZERO);
	draw->setPosition(Point::ZERO);
	this->addChild(draw);

	int mapWidth=(int)size.width*0.8-(int)(size.width*0.8)%10;
	int mapHeight=(int)size.height*0.9-(int)(size.height*0.9)%10;
	sepWidth=(int)mapWidth/10;
	sepHeight=(int)mapHeight/10;


	//添加蛇头,食物

	head=SnakeNode::create(ENUM_TYPE::TYPE_HEAD);
	auto body=SnakeNode::create(ENUM_TYPE::TYPE_BODY);
	auto food=SnakeNode::create(ENUM_TYPE::TYPE_FOOD);

	for(int i=0;i<=10;i++)
	{
		draw->drawSegment(Point(0,sepHeight*i),Point(mapWidth,sepHeight*i),1,Color4F(1,1,1,1));
		draw->drawSegment(Point(sepWidth*i,0),Point(sepWidth*i,mapHeight),1,Color4F(1,1,1,1));

	}

	this->addChild(head);
	this->addChild(food);

	//添加触摸事件
	auto litener=EventListenerTouchOneByOne::create();
	litener->setSwallowTouches(true);//继续向下传递事件
	litener->onTouchBegan=[&](Touch * touch,Event * event)
	{
		//改变移动方向
		int touchX=touch->getLocation().x;
		int touchY=touch->getLocation().y;
		SnakeNode * node=head;
		int headX=head->getPositionX();
		int headY=head->getPositionY();

		setDir(head,touchX,touchY,headX,headY);

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(litener,this);

	return true;
}
void Game::menuCallBack(Ref * obj)
{
	Director::getInstance()->popScene();
}

void setDir(SnakeNode * node,int touchX,int touchY,int nodeX,int nodeY)
{
	if(node->m_dir==ENUM_DIR::DIR_RIGHT||node->m_dir==ENUM_DIR::DIR_LEFT)
	{
		if((touchY-nodeY)>=60)
		{
			node->m_dir=ENUM_DIR::DIR_UP;
		}else if((nodeY-touchY)>=60)
		{
			node->m_dir=ENUM_DIR::DIR_DOWN;
		}else{
			if(touchX>nodeX)
			{
				node->m_dir=ENUM_DIR::DIR_RIGHT;
			}else
			{
				node->m_dir=ENUM_DIR::DIR_LEFT;
			}
		}
	}else
	{
		if((touchX-nodeX)>=60)
		{
			node->m_dir=ENUM_DIR::DIR_RIGHT;
		}
		else if((nodeX-touchX)>=60)
		{
			node->m_dir=ENUM_DIR::DIR_LEFT;
		}else
		{
			if(touchY>nodeY)
			{
				node->m_dir=ENUM_DIR::DIR_UP;
			}else
			{
				node->m_dir=ENUM_DIR::DIR_DOWN;
			}
		}
	}
}