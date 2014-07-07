
#include "iostream"
#include "X.h"
#include "Y.h"
using namespace std;

X::X(int num):m(1),m2(num){
	this->n=1;
	cout<<"construct X  n="<<this->n<<endl;
};

X::~X(){
	cout<<"deconstruct X"<<endl;
}

//X::X(const X&){
//	cout<<"copy construct X"<<endl;
//	this->n=10;
//}
X& X::operator =(const X &){
	cout<<"X::operator ="<<endl;
	n=3;
	return *this;
}

X::operator Y() const{
	cout<<"自动类型转换"<<endl;
	return Y();
}

void X::func(){
	cout<<"func  n="<<this->n<<endl;
}


