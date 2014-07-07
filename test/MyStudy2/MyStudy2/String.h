/*
 * StringTest1.h
 *
 *  Created on: 2014��4��9��
 *      Author: h3c
 */

#ifndef STRING_H_
#define STRING_H_

#include "fstream"
using namespace std;

class String {
private:
	char * buf;

public:
	
	int length;
	String();
	String(String&);
	String(const char *);
	String& operator = (String &);
	String& operator = (const char *);
	virtual ~String();

	friend ostream& operator<<(ostream& out,const String &);

	int find_first(const String &s);
	int find_first(const String &s,int begin,int length);
	int getFirstChar(const String & s);

	operator const char *();//�Զ�����ת������  ��ʽΪ��operator ����A ����,���ڽ�����Aת��Ϊ����(String)������

	void info();
};


#endif /* STRING_H_ */
