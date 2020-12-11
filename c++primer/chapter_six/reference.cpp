#include<iostream>

using namespace std;

void reset(int *ip){
	*ip = 0;
	ip = 0;
}

int main(int argc, char const *argv[])
{
	int i = 42;
	cout << &i << endl;

	reset(&i);

	cout << i << endl;
	cout << &i << endl;


	return 0;
}