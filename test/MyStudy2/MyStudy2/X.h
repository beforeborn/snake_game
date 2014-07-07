#ifndef X_H_
#define X_H_
/*class X{
	public:
		void func();

};*/
#include "Y.h"
class X {
public:
	int n;
	//string s;

	/** const类型和引用类型必须在构造函数初始化列表中初始化**/
	const int m;
	int & m2;

	X(int=0);
	virtual ~X();

	//X(const X&);

	X& operator=(const X&);

	operator Y() const;

	void func();
};


#endif