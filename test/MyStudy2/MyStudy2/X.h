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

	/** const���ͺ��������ͱ����ڹ��캯����ʼ���б��г�ʼ��**/
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