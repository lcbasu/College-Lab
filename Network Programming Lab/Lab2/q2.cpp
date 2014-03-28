#include <iostream>
#include <string>

using namespace std;

void applyBitStuffing(char *result, string in)
{
	int newPtr = 0;
	int count = 0;
	for (int i = 0; i < in.size(); ++i)
	{
		if(in[i] == '1')
		{
			while(count != 5 && in[i] == '1' && i < in.size())
			{
				result[newPtr] = in[i];
				i++;
				newPtr++;
				count++;
			}
			if(count == 5)
			{
				count = 0;
				result[newPtr] = '0';
				cout << "Stuffing 0 at position :\t" << newPtr << endl;
				sleep(1);
				newPtr++;
				i--;
			}
			else
				count = 0;
		}
		if(in[i] == '0' && i < in.size())
		{
			result[newPtr] = in[i];
			newPtr++;
		}
	}
	//finally newPtr stores the total number of elements in the result array
	cout << "New Stuffed Bit Stream :\t";
	for (int i = 0; i < newPtr; ++i)
	{
		cout << result[i];
	}
	cout << endl;
}

int main()
{
	string in;
	cout << "Enter the Bit Stream to be stuffed :\t";
	cin >> in;
	int oldBSLen = in.size();
	int newBSLen = oldBSLen + (oldBSLen/5);	//maximum size that can be of the stuffed Bit Stream
	char *result = new char[newBSLen];
	applyBitStuffing(result, in);
	return 0;
}