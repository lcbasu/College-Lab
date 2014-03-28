#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t_states;
	cout << "Enter total no of states : ";
	cin >> t_states;

	int t_symbols;
	cout << "Enter total no of symbols : ";
	cin >> t_symbols;

	int rows = t_states+1;
	int colms = t_symbols+1;

	char matrix[rows][colms];
	cout << "Enter the states of the DFA in left to right fashion : \n";
	for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < colms; j++)
		{
			if(i==0 && j==0)
				continue;
			cin >> matrix[i][j];
		}
	}

	string temp_str;
	char temp_char;

	
	cout << "Enter the initial states as a string : ";
	cin >> temp_str;
	vector<char> ini_states(temp_str.begin(), temp_str.end());
	
	cout << "Enter the accepting states as a string : ";
	cin >> temp_str;
	vector<char> acp_states(temp_str.begin(), temp_str.end());

	cout << "Enter your starting state : ";
	cin >> temp_char;

	char prev_in_str_char = temp_char;
	char curr_in_str_char = prev_in_str_char;

	cout << "Enter the input string : ";
	cin >> temp_str;
	vector<char> input_str(temp_str.begin(), temp_str.end());

	bool accepting_state;

	for (int i = 0; i < input_str.size(); i++)
	{
		prev_in_str_char = curr_in_str_char;
		accepting_state = false;
		int row_index = 0;
		int colm_index = 0;
		for(int j=1; j<rows; j++)
		{
			if(prev_in_str_char == matrix[j][0])
				row_index = j;
		}
		for(int j=1; j<colms; j++)
		{
			if(input_str[i] == matrix[0][j])
				colm_index = j;
		}
		curr_in_str_char = matrix[row_index][colm_index];
		cout << prev_in_str_char << " -----> " << curr_in_str_char;
		for(int k=0; k<acp_states.size(); k++)
		{
			if(acp_states[k] == curr_in_str_char)
				accepting_state = true;
		}
		if(accepting_state)
			cout << "---->ACCEPTING STATE.\n";
		else
			cout << endl;
	}
	if(accepting_state)
		cout << "\nInput String is acceptable.\n";
	else
		cout << "\nInput String is NOT acceptable.\n";

	return 0;
}