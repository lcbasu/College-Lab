#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name = "Lokesh";
	char c = 'x';
	size_t p = name.find(c);
	if(p)
		cout << "LLLL\n";
	return 0;
}