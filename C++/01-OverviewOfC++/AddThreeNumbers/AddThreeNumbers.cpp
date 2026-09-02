#include <iostream>
using namespace std;

int main()
{
	double n1,n2,n3;
	cout << "This program adds three numbers" << endl;
	cout << "1st number: " ;
	cin >> n1;
	cout << "2st number: ";
	cin >> n2;
	cout << "3st number: ";
	cin >> n3;
	double sum = n1 + n2 + n3;
	cout << "This sum is " << sum << endl;
  	return 0;
}