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
	this->setAnchorPoint(Point::ZERO);
	switch (type)
	{
	case ENUM_TYPE::TYPE_HEAD:
		node = Sprite::create("head.jpg");
		node->setAnchorPoint(Point::ZERO);
		node->setPosition(Point::ZERO);
		m_last_dir=m_dir = ENUM_DIR::DIR_RIGHT;
		
		break;
	case ENUM_TYPE::TYPE_BODY:
		node = Sprite::create("body.jpg");
		node->setAnchorPoint(Point::ZERO);
		m_last_dir=m_dir = ENUM_DIR::DIR_STOP;
		break;
	case ENUM_TYPE::TYPE_FOOD:
		node = Sprite::create("food.jpg");
		int row = rand() % 10;
		int col = rand() % 10;

		node->setAnchorPoint(Point::ZERO);
		node->setPosition(row*Game::sepWidth, col*Game::sepHeight);
		m_last_dir=m_dir = ENUM_DIR::DIR_STOP;
		break;
	}

	scaleNodeX = Game::sepWidth / node->getContentSize().width;
	scaleNodeY = Game::sepHeight / node->getContentSize().height;
	node->setScaleX(scaleNodeX);
	node->setScaleY(scaleNodeY);

	this->addChild(node);

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

void SnakeNode::gameLogic()
{
	switch (m_dir)
	{
	case ENUM_DIR::DIR_RIGHT:
		this->node->runAction(MoveBy::create(Game::sepTime*0.8, Point(Game::sepWidth, 0)));
		
		break;
	case ENUM_DIR::DIR_LEFT:
		this->node->runAction(MoveBy::create(Game::sepTime*0.8, Point(-Game::sepWidth, 0)));
		
		break;
	case ENUM_DIR::DIR_UP:
		this->node->runAction(MoveBy::create(Game::sepTime*0.8, Point(0, Game::sepHeight)));
		
		break;
	case ENUM_DIR::DIR_DOWN:
		this->node->runAction(MoveBy::create(Game::sepTime*0.8, Point(0, -Game::sepHeight)));
		
		break;
	case ENUM_DIR::DIR_STOP:
		break;
	default:
		break;
	}

}
void SnakeNode::setPosition(float x,float y)
{
	//Sprite::setPosition(x,y);
	this->node->setPosition(x,y);
}
void SnakeNode::setPositionX(float x)
{
	//this->setPosition(x,this->getPositionY());
	this->node->setPosition(x,this->node->getPositionY());
}

void SnakeNode::setPositionY(float y)
{
	//this->setPosition(this->getPositionX(),y);
	this->node->setPosition(this->node->getPositionX(),y);
}

//float SnakeNode::getPositionX() const 
//{
//	return node->getPositionX();
//}
//
//float SnakeNode::getPositionY() const 
//{
//	return node->getPositionY();
//}
