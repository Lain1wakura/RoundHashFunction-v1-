#include <iostream>
#include "HeaderHash.h"
using namespace std;

int main()
{
	Hash hash;
	string str, finalhash;
	int len, quan;
	cout << "Enter input text, hash lenght and quantity of rounds: ";
	cin >> str >> len >> quan;

	if (quan == 0)
	{
		finalhash += hash.gethash(str, len);
		cout << finalhash << endl;
	}
	else
	{
		for (int i = 0; i < quan; i++)
		{
			finalhash += hash.gethash(str, len);
			//cout << finalhash << endl;	//To debug
			finalhash = hash.gethash(finalhash, len);
			//cout << finalhash << endl;	//To debug
		}
		cout << finalhash << endl;
	}

	return 0;
}

//Old control sum
//Enter input text, hash lenght and quantity of rounds: string10 10 0
//TMNXhTLLwd
//New control sum
//Enter input text, hash lenght and quantity of rounds: string10 10 0
//TMNXhTdLfd
//Not big different though :|
