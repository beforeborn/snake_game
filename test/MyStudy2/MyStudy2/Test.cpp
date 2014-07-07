/*****
本例函数A& fun()返回的是局部变量的引用，从输出上看，局部变量确实是析构了，但是在
main函数中得到的n的值是正确的。



******/

#include <iostream>
using namespace std;

class A
{
public:
	int n;
    A()
    {
        cout<<"本体="<<this<<endl;
    }
    A(const A& CA)
    {
        cout<<"分身="<<this<<endl;
    }
    ~A()
    {
		cout<<"析构="<<this<<endl;
    }
	void f(){
		cout<<"f()="<<this<<endl;
		cout<<"f()  n="<<n<<endl;
	}
};

A& fun();

A fun1();

A* fun2();


A& fun()
{
    A a;
	a.n=10;
	cout<<"a.n="<<a.n<<endl;
	a.f();
    return a;
}

A fun1(){

	 A a;
	a.n=10;
	cout<<"a.n="<<a.n<<endl;
	a.f();
    return a;
}

A* fun2(){
	A a;
	a.n=10;
	cout<<"a.n="<<a.n<<endl;
	a.f();

	return &a;

}

int main3()
{
    A& a=fun();
    cout<<"a.n="<<a.n<<endl;
	a.f();
    cout<<"***************"<<endl;
	//A a1=fun1();
 //   cout<<"a1.n="<<a1.n<<endl;
	//a1.f();
	//cout<<"***************"<<endl;
	//A* a2=fun2();
	//cout<<"a.n="<<a2->n<<endl;
	//a2->f();
  
    getchar();
    return 0;
}
