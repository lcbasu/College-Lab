#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input;
	cout << "Enter the input String [ex: 100201 etc ] : ";
	cin >> input;

	char state = 'A';

	int size  = input.size();
	for (int i = 0; i < size; i++)
	{
		cout << state;
		switch(state)
		{
			case 'A':
			{				
				if(input[i]=='0')
				{
					state = 'B';					
				}
				else if(input[i]=='1')
				{
					state = 'A';
				}
				else if(input[i]=='2')
				{
					state = 'B';
				}
				break;				
			}
			case 'B':
			{
				if(input[i]=='0')
				{
					state = 'E';
				}
				else if(input[i]=='1')
				{
					state = 'A';
				}
				else if(input[i]=='2')
				{
					state = 'C';
				}	
				break;			
			}
			case 'C':
			{
				if(input[i]=='0')
				{
					state = 'A';
				}
				else if(input[i]=='1')
				{
					state = 'E';
				}
				else if(input[i]=='2')
				{
					state = 'D';
				}
				break;				
			}
			case 'D':
			{
				if(input[i]=='0')
				{
					state = 'C';
				}
				else if(input[i]=='1')
				{
					state = 'D';
				}
				else if(input[i]=='2')
				{
					state = 'E';
				}
				break;				
			}
			case 'E':
			{
				if(input[i]=='0')
				{
					state = 'E';
				}
				else if(input[i]=='1')
				{
					state = 'D';
				}
				else if(input[i]=='2')
				{
					state = 'A';
				}
				break;				
			}
			default:
				cout << "Wrong state.";
				break;
		}
		cout << " ---> " << state;
		if(state == 'E')
			cout << " --- [ACCEPTING STATE] " << endl;
		else
			cout << " --- [NON-ACCEPTING STATE]" << endl;
	}
	if (state == 'E')
	{
		cout << "\nThe input string is accepted by the given DFA. !!!" << endl;
	}
	else
		cout << "\nThe input string is NOT accepted by the given DFA. !!!" << endl;	
	return 0;
}