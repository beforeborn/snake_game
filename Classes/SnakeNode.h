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
	ENUM_TYPE nodeType;//1��ʾ��ͷ��2��ʾ���壬3��ʾʳ��
	static SnakeNode* create(ENUM_TYPE type);
	bool init(ENUM_TYPE type);
	void gameLogic(float t);
private:
	float scaleNodeX;
	float scaleNodeY;
};

#endif