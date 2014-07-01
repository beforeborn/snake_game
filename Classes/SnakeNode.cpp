#include "cocos2d.h"
#include "SnakeNode.h"
#include "Game.h"
USING_NS_CC;
bool SnakeNode::init(ENUM_TYPE type)
{

	if (!Sprite::init())
	{
		return false;
	}
	this->nodeType = type;
	switch (type)
	{
	case ENUM_TYPE::TYPE_HEAD:
		node = Sprite::create("head.jpg");
		node->setAnchorPoint(Point::ZERO);
		node->setPosition(Point::ZERO);
		m_dir = ENUM_DIR::DIR_RIGHT;

		break;
	case ENUM_TYPE::TYPE_BODY:
		node = Sprite::create("body.jpg");
		m_dir = ENUM_DIR::DIR_STOP;
		break;
	case ENUM_TYPE::TYPE_FOOD:
		node = Sprite::create("food.jpg");
		int row = rand() % 10;
		int col = rand() % 10;

		node->setAnchorPoint(Point::ZERO);
		node->setPosition(row*Game::sepWidth, col*Game::sepHeight);
		m_dir = ENUM_DIR::DIR_STOP;
		break;
	}
	scaleNodeX = Game::sepWidth / node->getContentSize().width;
	scaleNodeY = Game::sepHeight / node->getContentSize().height;
	node->setScaleX(scaleNodeX);
	node->setScaleY(scaleNodeY);

	this->addChild(node);

	this->schedule(schedule_selector(SnakeNode::gameLogic),0.5);

	return true;
}

SnakeNode* SnakeNode::create(ENUM_TYPE type)
{
	SnakeNode * node = new SnakeNode();
	if (node&&node->init(type))
	{
		node->autorelease();
		return node;
	}
	else
	{
		delete node;
		node = NULL;
		return NULL;
	}

}

void SnakeNode::gameLogic(float t)
{
	switch (m_dir)
	{
	case ENUM_DIR::DIR_RIGHT:
		this->runAction(MoveBy::create(0.3, Point(Game::sepWidth, 0)));
		break;
	case ENUM_DIR::DIR_LEFT:
		this->runAction(MoveBy::create(0.3, Point(-Game::sepWidth, 0)));
		break;
	case ENUM_DIR::DIR_UP:
		this->runAction(MoveBy::create(0.3, Point(0, Game::sepHeight)));
		break;
	case ENUM_DIR::DIR_DOWN:
		this->runAction(MoveBy::create(0.3, Point(0, -Game::sepHeight)));
		break;
	case ENUM_DIR::DIR_STOP:
		break;
	default:
		break;
	}

}
