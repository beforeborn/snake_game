/*****
��������A& fun()���ص��Ǿֲ����������ã�������Ͽ����ֲ�����ȷʵ�������ˣ�������
main�����еõ���n��ֵ����ȷ�ġ�



******/

#include <iostream>
using namespace std;

class A
{
public:
	int n;
    A()
    {
        cout<<"����="<<this<<endl;
    }
    A(const A& CA)
    {
        cout<<"����="<<this<<endl;
    }
    ~A()
    {
		cout<<"����="<<this<<endl;
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
