#include "iostream"
#include "winsock.h"
#include "tchar.h"


//#include "X.h"

/*
X* test1(){
	X* x = new X();
	return x;
}
X test2(){
	return X();
}
*/
using namespace std;
struct X {
	int n;
	template<typename T>
	X(T&) { std::cout << "This is ctor." << std::endl; }

	template<typename T>
	X& operator=(T&) { std::cout << "This is ctor." << std::endl; }
};

void test3() {
	int m = 5;
	float n = 10.5;
	X a(m);
	X b(n);
	cout << "***" << endl;
	X c = a;
	cout << "***" << endl;
	c = b;
}

int main(int n,char * args[]){
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpFlag);

	typedef struct X *x;
	x xx;
	xx->n = 3;

	SC_HANDLE sc;
	test3();
	auto s2=_T("i");
	printf("s=%s", s2);
	char * s = "hello";
	wchar_t arr[] = _T("Hello");

	int m=~0;
	cout << m << endl;
	m = ~-1;
	cout << m << endl;
	m = ~1;
	cout << m << endl;
	getchar();

}