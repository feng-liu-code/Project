#include <iostream>
using namespace std;

const int START = 10;

int main()
{
	cout << "This program counts backwards from the value START to zero" << endl;
	for(int i = START; i >= 0; i--)
	{
		cout << i << endl;
	}
	return 0;
}