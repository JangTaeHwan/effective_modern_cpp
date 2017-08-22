#include <iostream>
#include <cstdio>
#include <string>


template<typename T>
void f(T& param) {

	T temp = param;
	temp  = 1;
}


template<typename T>
void g(T&& param) {

	T temp = param;
	temp  = 1;
}

int main(){

	int data = 5;
	int& i = data;

//	f(&i);
	f(data);

	std::cout<< data <<std::endl;
	std::cout<< i <<std::endl;

/*
	const char* ptr = "Fun with pointers";
	ptr = "hello";
	f(in);
	std::cout<< ptr <<std::endl;
*/

	return 0;
}
