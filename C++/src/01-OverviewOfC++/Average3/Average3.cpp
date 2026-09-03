#include <iostream>
using namespace std;

int main()
{
	double n1,n2,n3;
	cout << "This program Average three integers" << endl;
	cout << "1st number: " ;
	cin >> n1;
	cout << "2st number: ";
	cin >> n2;
	cout << "3st number: ";
	cin >> n3;
	double average = (n1 + n2 + n3)/3.0;
	cout << "This average is " << average << endl;
  	return 0;
}