#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
	string a = "12";
	stringstream ss;
	ss << a;
	int val;
	ss >> val;

	cout << val+3 << endl;

	return 0;
}