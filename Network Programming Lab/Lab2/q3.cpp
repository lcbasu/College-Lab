#include <iostream>
#include <string>
#include <list>


using namespace std;

struct Fragments
{
	string data;
	int serialNo;	//set this  -1 for the original data and 1,2,3... for the fragmented data
	int frame[3];
};

Fragments *newFragment(string data, int serialNo, int frame_0, int frame_1, int frame_2)
{
	Fragments *tmp = new Fragments();
	tmp->data = data;
	tmp->serialNo = serialNo;
	tmp->frame[0] = frame_0;
	tmp->frame[1] = frame_1;
	tmp->frame[2] = frame_2;
	return tmp;
}

list<Fragments* > fragmentationModel(Fragments *original, int mtu)
{
	list<Fragments* > buffer;
	int i;
	int sn = 1;
	for (i = 0; i < original->data.size()-mtu; i = i + mtu)	// include all fragment but not the last one as that 
	{														// one should have frame_2 = 0
		Fragments *tmp = newFragment(original->data.substr(i,mtu), sn, 0, 1, 1);
		buffer.push_back(tmp);
		sn++;
	}
	Fragments *tmp = newFragment(original->data.substr(i), sn, 0, 1, 0);
	buffer.push_back(tmp);
	return buffer;
}

void display(list<Fragments* > buffer)
{
	list<Fragments* >::iterator it;
	for(it = buffer.begin(); it != buffer.end(); it++)
	{
		cout << "S. No:\t" << (*it)->serialNo << endl;
		cout << "Data:\t" << (*it)->data << endl;
		cout << "Flag:\t";
		for(int i = 0; i < 3; i++)
		{
			cout << (*it)->frame[i] << " ";
		}
		cout << endl;
	}
}

string reassemblyModel(list<Fragments *> buffer)
{
	cout << "--- Information about all the fragments of the original data ---\n" << endl;
	display(buffer);
	cout << endl;
	cout << "Reassembling all the fragments based on the serial number of all the fragments..." << endl;
	sleep(2);
	string reassembledData = "";
	while(!buffer.empty())
	{
		Fragments *tmp;
		tmp = buffer.front();
		reassembledData.append(tmp->data);
		buffer.pop_front();
	}
	return reassembledData;
}


int main()
{
	string data;
	int mtu;
	cout << "Enter the data :\t";
	cin >> data;
	cout << "Enter the MTU :\t";
	cin >> mtu;
	Fragments *original = newFragment(data, -1, 0, 0, 0);
	if(data.size() <= mtu)
		cout << "No fragmentation model to be applied.\n";
	else
	{
		list<Fragments* > buffer = fragmentationModel(original, mtu);
		string reassembledData = reassemblyModel(buffer);
		cout << "Reassembled data : " << reassembledData << endl;
	}
	return 0;
}
