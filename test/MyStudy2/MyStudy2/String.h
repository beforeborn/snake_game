/*
 * StringTest1.h
 *
 *  Created on: 2014年4月9日
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

	operator const char *();//自动类型转换函数  格式为：operator 类型A （）,用于将类型A转换为该类(String)的类型

	void info();
};


#endif /* STRING_H_ */
