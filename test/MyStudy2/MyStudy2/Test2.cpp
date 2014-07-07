#include "iostream"
#include "string"
#include "MyException.h"
#include "String.h"
#include "fstream"
#include "Util.h"
#include "X.h"

using namespace std;

void test1(MyException & r) {
}

void test2(string &s) {
	cout << "s=" << s << endl;
}

string getString() {

	string s = "hello";

	return s;

}

void test3(const String &s) {
	cout << "test3 s=" << s << endl;
}

void test4(char * str) {
	cout << "******test4************" << str << endl;
}

void testString();

int func(int);

int getValue() {
	int n = 3;
	return n;
}

int getValue2() {
	int n = 3;
	int *p = &n;
	return *p;
}

char* getValue3() {
//	char * p="hello";
	char p[] = "hello";
	return p;
}

X testX(X x){
	printf("n=%d",x.n);
	return x;
}

int main_Test2(int arg1, char *argv[]) {

	/**
	 * 开启内存泄露检测
	 */
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpFlag);

//	testString();
//
//	int n = 1;
//	int m = 2;
//	int &x = n;
//	int &y = m;
//	//swap(x, y);
//	printf("x=%d,y=%d,n=%d,m=%d\n", x, y, n, m);
//
//	int i, j;
//	int *a[5] = { &i, &j };
//	a[0]; // point to i
//	a[1]; // point to j
//
//	int array[10];
//
//	int b[5] = { x, y }; //b是长度为5的数组，数组元素为int型，虽然这里使用了引用初始化，但是合法。
////	int &b[5]={x,y}; 引用数组是非法的  ，  b是长度为5的数组，数组元素为int型的引用，非法。因为引用是不分配内存的
//	int (&rArr)[10] = array; //rArr是引用，指向int[10] 数组
//
//	string s1;
//
//	test2(s1);
//	test2("hello");
//	test2(getString());
//	getchar();

//int n1=getValue();
//cout<<n1<<endl;
//int n2=getValue2();
//cout<<n2<<endl;
//char *p=getValue3();
//cout<<p<<endl;

	//String s;

	//string s1 = "abc";
	//bool b= (s1 == "abc");
	//cout <<b<< endl;

	X x1;
	X *x2 = new X();
	X x3=testX(x1);

	delete x2;
	getchar();

	return 0;

}

/**
 * 测试自定义的String类的基本功能
 */
void testString() {

	String s1 = String();
	String s2 = "world";
	s1 = s2;
	String &s3 = String(s2);
	//s2.info();
	//s3.info();

	s1 = "s1";
	s2 = "s2";
	s3 = "s3";

	cout << "s1=" << s1 << endl;
	cout << "s2=" << s2 << endl;
	cout << "s3=" << s3 << endl;

//	s1 = s1;
	cout << "s1=" << s1 << endl;
	//s1 = *new String(s2);
	//cout<<"s1="<<s1<<endl;
	s1 = String(s3);
	cout << "s1=" << s1 << endl;

	String *p = new String(s2);
	delete p;

	String src = "aabchello worldxyz";
	String des = "abc";
	char * arr = "abc";

	int position = src.find_first("abc");
	position = src.find_first(arr);
	cout << "abc ,position=" << position << endl;

	position = src.find_first("abc", 0, strlen(src));
	cout << "abc ,position=" << position << endl;

	des = "xyz";
	position = src.find_first(des);
	cout << "xyz ,position=" << position << endl;
	position = src.find_first(des, 0, strlen(src));
	cout << "xyz ,position=" << position << endl;

	des = "hello";
	position = src.find_first(des);
	cout << "hello ,position=" << position << endl;
	position = src.find_first(des, 0, strlen(src));
	cout << "hello ,position=" << position << endl;

	des = "world";
	position = src.find_first(des);
	cout << "world ,position=" << position << endl;
	position = src.find_first(des), 0, strlen(src);
	cout << "world ,position=" << position << endl;

	des = "axy";
	position = src.find_first(des);
	cout << "axy ,position=" << position << endl;
	position = src.find_first(des, 0, strlen(src));
	cout << "axy ,position=" << position << endl;

	des = "abcx";
	position = src.find_first(des);
	cout << "abcx ,position=" << position << endl;
	position = src.find_first(des, 0, strlen(src));
	cout << "abcx ,position=" << position << endl;

	des = "hello world";
	position = src.find_first(des);
	cout << "hello world ,position=" << position << endl;
	position = src.find_first(des, 0, strlen(src));
	cout << "hello world ,position=" << position << endl;

}

int func(int x) {
	int countx = 0;
	while (x) {
		countx++;
		x = x & (x - 1);
	}
	return countx;
}
