#ifndef __SNAKENODE_H__
#define __SNAKENODE_H__
#include "cocos2d.h"
USING_NS_CC;
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
	TYPE_HEAD = 1,
	TYPE_BODY,
	TYPE_FOOD
};

class SnakeNode :public Sprite
{
public:
	Sprite * node;
	ENUM_DIR m_dir;
	ENUM_DIR m_last_dir;
	ENUM_TYPE nodeType;//1表示舌头，2表示身体，3表示食物
	static SnakeNode* create(ENUM_TYPE type);
	bool init(ENUM_TYPE type);
	void gameLogic();

	void setPosition(float x,float y) override;
	void setPositionX(float x) override;
	void setPositionY(float y) override;
	//float getPositionX() const override;
	//float getPositionY() const override;
private:
	float scaleNodeX;
	float scaleNodeY;
};

#endif