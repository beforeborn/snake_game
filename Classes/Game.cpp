#include "Game.h"
#include "SnakeNode.h"




void setDir(SnakeNode *node, int touchX, int touchY, int nodeX, int nodeY);
bool nodeImpact(Node * node, Rect * edage);
void setNodeLocation(SnakeNode * newNode, SnakeNode * preNode);

Game::Game(void)
{
}


Game::~Game(void)
{
}

int Game::sepHeight = 0;
int Game::sepWidth = 0;
SnakeNode* head = NULL;
SnakeNode* food = NULL;
Vector<SnakeNode *> allBody;
Rect * edgeRect = NULL;

Scene* Game::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = Game::create();
	scene->addChild(layer);
	return scene;
}
bool Game::init()
{
	if (!Layer::init())
	{

		return false;
	}
	//��ӱ���
	auto size = Director::getInstance()->getWinSize();
	auto gameBG = Sprite::create("game_bg.jpg");
	gameBG->setAnchorPoint(Point::ZERO);
	gameBG->setPosition(0, 0);
	gameBG->setOpacity(75);
	int bgWidth = gameBG->getContentSize().width;
	int bgHeight = gameBG->getContentSize().height;

	float scaleX = size.width / bgWidth;
	float scaleY = size.height / bgHeight;

	gameBG->setScaleX(scaleX);
	gameBG->setScaleY(scaleY);

	this->addChild(gameBG);

	//������ʾ
	auto scoreLabel = Label::create("Hello World", "Arial", 24);
	scoreLabel->setPosition(Vec2(size.width - 80, size.height - 50));
	this->addChild(scoreLabel);

	////��Ӳ˵�
	auto menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(Game::menuCallBack, this));
	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width - 80, menuItemBack->getContentSize().height + 30));
	menuItemBack->setColor(Color3B::GREEN);
	this->addChild(menu);

	//��ӵ�ͼ
	auto draw = DrawNode::create();
	draw->setAnchorPoint(Point::ZERO);
	draw->setPosition(Point::ZERO);
	this->addChild(draw);

	int mapWidth = (int)size.width*0.8 - (int)(size.width*0.8) % 10;
	int mapHeight = (int)size.height*0.9 - (int)(size.height*0.9) % 10;
	sepWidth = (int)mapWidth / 10;
	sepHeight = (int)mapHeight / 10;

	edgeRect = new Rect(-20, -20, mapWidth + 20, mapHeight + 20);

	//�����ͷ,ʳ��

	head = SnakeNode::create(ENUM_TYPE::TYPE_HEAD);
	food = SnakeNode::create(ENUM_TYPE::TYPE_FOOD);

	allBody.pushBack(head);
	for (int i = 0; i <= 10; i++)
	{
		draw->drawSegment(Point(0, sepHeight*i), Point(mapWidth, sepHeight*i), 1, Color4F(1, 1, 1, 1));
		draw->drawSegment(Point(sepWidth*i, 0), Point(sepWidth*i, mapHeight), 1, Color4F(1, 1, 1, 1));

	}

	this->addChild(head);
	this->addChild(food);

	//��Ӵ����¼�
	auto litener = EventListenerTouchOneByOne::create();
	litener->setSwallowTouches(true);//�������´����¼�
	litener->onTouchBegan = [&](Touch * touch, Event * event)
	{
		//�ı��ƶ�����
		int touchX = touch->getLocation().x;
		int touchY = touch->getLocation().y;
		SnakeNode * node = head;
		int headX = head->getPositionX();
		int headY = head->getPositionY();

		setDir(head, touchX, touchY, headX, headY);

		return true;
	};

	this->schedule(schedule_selector(Game::updateFrame), 0.2);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(litener, this);

	return true;
}
void Game::menuCallBack(Ref * obj)
{
	Director::getInstance()->popScene();
}

void setDir(SnakeNode * node, int touchX, int touchY, int nodeX, int nodeY)
{
	if (node->m_dir == ENUM_DIR::DIR_RIGHT || node->m_dir == ENUM_DIR::DIR_LEFT)
	{
		if ((touchY - nodeY) >= 60)
		{
			node->m_dir = ENUM_DIR::DIR_UP;
		}
		else if ((nodeY - touchY) >= 60)
		{
			node->m_dir = ENUM_DIR::DIR_DOWN;
		}
		else if (allBody.size() == 1){
			if (touchX > nodeX)
			{
				node->m_dir = ENUM_DIR::DIR_RIGHT;
			}
			else
			{
				node->m_dir = ENUM_DIR::DIR_LEFT;
			}
		}
	}
	else
	{
		if ((touchX - nodeX) >= 60)
		{
			node->m_dir = ENUM_DIR::DIR_RIGHT;
		}
		else if ((nodeX - touchX) >= 60)
		{
			node->m_dir = ENUM_DIR::DIR_LEFT;
		}
		else if (allBody.size() == 1)
		{
			if (touchY > nodeY)
			{
				node->m_dir = ENUM_DIR::DIR_UP;
			}
			else
			{
				node->m_dir = ENUM_DIR::DIR_DOWN;
			}
		}
	}
}

void Game::updateFrame(float t)
{
	

	//���ʳ����ײ
	if (head->boundingBox().intersectsRect(food->node->boundingBox()))
	{
		log("crushed");
		//����½ڵ㣬��������λ�úͷ���
		int index = allBody.size() - 1;
		SnakeNode* preNode = allBody.at(index);
		setNodeLocation(food, preNode);

		this->addBody(food);
		food = SnakeNode::create(ENUM_TYPE::TYPE_FOOD);
		this->addChild(food);
	}
	//����Ե��ײ
	if (nodeImpact(head, edgeRect))
	{
		this->menuCallBack(this);
	}
	//�ƶ�bodys
	moveBodys();

}

void Game::moveBodys()
{

}
void Game::addBody(SnakeNode* body)
{

}

bool nodeImpact(Node *node, Rect * edage)
{
	Vec2 x = node->getPosition().ANCHOR_BOTTOM_LEFT;
	int x1 = node->getPositionX();
	int y1 = node->getPositionY();


	if (node->getPositionX() <= (edage->getMinX()))//���Ե��ײ
	{
		return true;
	}
	if (node->getPositionX() >= (edage->getMaxX()))//�ұ�Ե��ײ
	{
		return true;
	}
	if (node->getPositionY() <= (edage->getMinY()))//�±�Ե��ײ
	{
		return true;
	}
	if (node->getPositionY() >= (edage->getMaxY()))//�ϱ�Ե��ײ
	{
		return true;
	}

	return false;
}

void setNodeLocation(SnakeNode * newNode, SnakeNode * preNode)
{
	switch (preNode->m_dir)
	{
	case ENUM_DIR::DIR_LEFT:
		newNode->setPositionX(preNode->getPositionX() + Game::sepWidth);
		newNode->setPositionY(preNode->getPositionY());
		break;
	case ENUM_DIR::DIR_RIGHT:
		log("head.x=%f", head->getPositionX());
		log("head.y=%f", head->getPositionY());
		log("food.x=%f", food->getPositionX());
		log("food.y=%f", food->getPositionY());
		log("head.box.x=%f", head->boundingBox().getMaxX());
		log("head.box.y=%f", head->boundingBox().getMaxY());
		log("food.box.x=%f", food->node->boundingBox().getMaxX());
		log("food.box.y=%f", food->node->boundingBox().getMaxY());
		log("**********");
		newNode->setPositionX(preNode->getPositionX() - Game::sepWidth);
		newNode->setPositionY(preNode->getPositionY());
		break;
	case ENUM_DIR::DIR_UP:
		newNode->setPositionX(preNode->getPositionX());
		newNode->setPositionY(preNode->getPositionY()-Game::sepHeight);
		break;
	case ENUM_DIR::DIR_DOWN:
		newNode->setPositionX(preNode->getPositionX());
		newNode->setPositionY(preNode->getPositionY() + Game::sepHeight);
		break;
	}
}

