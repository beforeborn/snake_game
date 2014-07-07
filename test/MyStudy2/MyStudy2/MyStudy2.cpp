// MyStudy2.cpp : 定义控制台应用程序的入口点。
//


#include "iostream"
#include "string"
#include "MyException.h"
#include "String.h"
#include "fstream"
#include "Util.h"
#include "X.h"

//#define printf(x) printfln(x)


using namespace std;
void test1();
void test2(X x);
X& test3();
int& test4(int a,int b);

char * getString();

void TestMemory();

//void * operator new(size_t sz);
//
//void * operator new(size_t sz){
//	printf("***重载 new\n");
//	return malloc(sz);
//}

void test6(int a,int b=0,char *s="s"){
	
}

//void operator delete(void *p){
//	printf("***重载 delete\n");
//	free(p);
//}

void _main(){
	cout<<"int _main(void)"<<endl;
	
}
int main_Mystudy(int argc, char* argv[])
{

	//test1();

	//X x1;
	//test2(x1);	
	
	//X& x=test3();
	//printf("x.m=%d\n",x.n);

	//int& sum=test4(1,2);

	//printf("sum=%d",sum);

	/*char * temp=new char[sizeof(X)];
	X * xptr=(X*)temp;
	int n=xptr->n;
	xptr->n=2;
	n=xptr->n;
	cout<<n<<endl;*/

	//Y y;  //由于Y的析构函数为private的，所以不能再栈上创建y的对象


	int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( tmpFlag );

	/*char * buf=(char *)malloc(1024);
	char * buf2=new char[1024];
	cout<<"this file="<<__FILE__<<endl;
	cout<<"line="<<__LINE__<<endl;*/

	//char s[]="hello";
	//string str="hello";
	//char c=s[100]='i';
	//str[100]='a';
	//char c=str[100];


	//cout<<c<<endl;

	//int *p1=new int(10);

    //delete p1;

	//cout<<"sizeof(p1)="<<sizeof(p1)<<endl;

	//char *p="hello";
	//char arr[]="hello";

	//cout<<"sizeof(p)="<<sizeof(p)<<endl;
	//cout << "sizeof(arr)=" << sizeof(arr) << endl;

	//arr[0]='i';
//	p[4]='i'; // 运行时出错，编译可通过

	//enum string { x1,x2,x3=10,x4,x5,}x;
	//char * temp = getString();
	//cout<<temp<<endl;
	//free(temp);
	
	//TestMemory();

//	char * a=new char[2];
//	char (*a2)[3]=new char[2][3];
//	char a3[2][3];
//	char (*ptr)[3]=a2;
//	*((ptr+1)[1])=1;
//cout<<"11"<<endl;
//	delete a;
//cout<<"22"<<endl;
//	delete []ptr;
//cout<<"end"<<endl;

	//String s = "hello";

	getchar();

	return 0;
}
void test1(){
	X x;
	x.n=2;
	x.func();

	X x2=x;
	x2.n=222;

	x.func();
	x2.func();

	x2=x;

	X x3=(X)x2;

}
void test2(X x){
	x.func();
}

X& test3(){
	
	X x;
	X& ref=x;
	return ref;

}

int& test4(int a,int b){

	int sum=a+b;

	int& ref=sum;
	return ref;
	
}

char* getString(){
	char *p=(char *)malloc(15);
	strcpy
		(p,"hello world");
	return p;
}

void TestMemory(void)
{
char *str = (char *) malloc(100);
strcpy(str,"hello");
free(str);  
str=NULL;//不加此行则可能报错
if(str != NULL)
{
strcpy(str,"world");
printf(str);
}
}