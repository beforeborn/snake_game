/*
 * StringTest1.cpp
 *
 *  Created on: 2014年4月9日
 *      Author: h3c
 */

#include "String.h"
#include <cstdio>
#include <cstring>
#include <exception>
#include <iostream>

using namespace std;

String::String() {
	length = 0;
	buf = NULL;
	cout << "String()" << endl;
}
String::String(const char * s) {
	if (s == NULL) {
		length = 0;
		buf = NULL;
	} else {
		this->length = strlen(s);
		buf = new char[length + 1];
		strcpy(buf, s);
	}
	cout << "String(char *)" << endl;
}

String::String(String & s) {
	this->length = s.length;
	this->buf = new char[length + 1];
	strcpy(this->buf, s.buf);

	cout << "String(String &)" << endl;
}

String & String::operator =(String & s) {

	cout << "String & operator =(String &)" << endl;
	if (this == &s) { //指针比较
		return *this;
	} else {

		this->length = s.length;
		delete buf;
		this->buf = new char[length + 1];
		strcpy(this->buf, s.buf);

		return *this;
	}
}

String & String::operator =(const char * s) {
	cout << "String & operator =(const char *)" << endl;
	this->length = strlen(s);
	delete buf;
	this->buf = new char[length + 1];
	strcpy(this->buf, s);

	return *this;
}

ostream& operator <<(ostream& out,const String & s) {
	out << s.buf;
	return out;
}

String::~String() {
	if (length != 0) {
		delete buf;
	}
	buf = NULL;
	cout << "~String()" << endl;
}

String::operator const char *() {
	return this->buf;
}


int String::find_first(const String & s) {

	char * pDes = s.buf;
	char * pSrc = this->buf;

	bool isNew = true;
	bool isMatch = false;
	int position = 0;
	int index = 0;
	try {
		while (*pSrc != '\0') {
			pDes = s.buf; //每次外层循环豆浆要查找的字符串的指针定位到开始处
			while (*pDes != '\0' && *pSrc != '\0') {
				if (*pDes == *pSrc) {
					if (isNew) {
						isNew = false;
						position = index;
					}
					pSrc++;
					pDes++;
					index++;
					isMatch = true;
				} else {
					if (isMatch) {
						pSrc--;
						index--;
					}
					isMatch = false;
					isNew = true;
					break;
				}
			}
			if (isMatch && (this->length - position) >= s.length) {
				return position;
			}
			pSrc++;
			index++;
		}
	} catch (int & e1) {
		cout << "error code=" << e1 << endl;
	} catch (...) {
		cout << "出现异常" << endl;
	}
	return -1;

}

int String::find_first(const String &s, int begin, int length) {

	int srcLength = strlen(this->buf);
	int desLength = strlen(s.buf);

	char *pSrc = this->buf;
	char *pDes = s.buf;

	if (begin >= srcLength) { //如果开始位置就在字符串末尾，返回-1
		return -1;
	}

	if (length < desLength) { //如果在源字符串中查找的长度小于目的字符串的长度，则不可能成功，返回-1
		return -1;
	}
	int maxIndex = begin + length;
	int index = 0;

	for (int i = begin; i < maxIndex; i++) {
		while (*pDes != *pSrc) { //首字符不相同的就指针向后移
			pSrc++;
			i++;
		}
		index = i;
		if (i + desLength <= maxIndex) {
			int j = 0;
			for (; j < desLength && (*pDes == *pSrc); j++, i++, pSrc++, pDes++)
				; //逐步位移判断字节是否相等
			if (j == desLength) {
				return index;
			} else { //如果不相等，则证明相同的字段比要查找的字段的长度小，则需要将pSrc指针向前偏移一位,pDes重新初始化
//				pSrc--;
				i--;
				pDes = s.buf;
			}
		} else {
			return -1;
		}
	}

	return -1;

}


void String::info() {
	cout << "In Info  buf=" << buf << endl;
	printf("*******info buf=%p\n", buf);
}

