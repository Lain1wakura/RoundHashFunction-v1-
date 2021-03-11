#pragma once
#include <iostream>
using namespace std;

class Hash
{
private:
	string hash;

	int receivingExistCodes(int x)
	{
		x += 256;
		while (!(((x <= 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97))))
		{
			if (x < 48) { x += 24; }
			else { x -= 47; }
		}
		return x;
	}

	int getControlSum(string str)
	{
		// New control sum
		unsigned int sault = 0, strlen = 0;
		if (str.size() % 2 != 0)
			str += 's';

		for (int i = 0; i < str.size(); i += 2)
		{
			int mult = str[i] * str[i + 1];
			int div = str[i] / str[i + 1];

			sault += mult;
			sault += div;
		}
		// Old control sum
		/*for (; strlen < str.size(); strlen++)
			sault += int(str[strlen]);*/
		return sault;
	}

public:
	string gethash(string userString, int hashlenght)
	{
		if (hashlenght > 3)
		{
			this->hash.clear();
			unsigned int minLen = 2; // Minimum string length, multiple of two, for hashing
			unsigned int realminLen = 0; // The length of the string closest to the desired hash length
			// Getting the salt of the original string
			unsigned int originalSault = this->getControlSum(userString);
			unsigned int originalLenghtStr = (userString.size());
			// Getting the string length, a multiple of a power of two, closest to the specified hash length
			while (minLen <= hashlenght)
				realminLen = (minLen *= 2);
			// Making the hash string length at least 2 times longer than the original string
			while (minLen < originalLenghtStr)
				minLen *= 2;

			if ((minLen - originalLenghtStr) < minLen)
				minLen *= 2;
			int addCount = minLen - originalLenghtStr;
			// Adding
			for (int i = 0; i < addCount; i++)
				userString += this->receivingExistCodes(userString[i] + userString[i + 1]);
			// Get the maximum salt
			int maxSault = this->getControlSum(userString);
			int maxLenghtStr = (userString.size());
			// Determining the compression ratio
			while (userString.size() != realminLen)
			{
				for (int i = 0, center = userString.size() / 2; i < center; i++)
					this->hash += this->receivingExistCodes(userString[center - i] + userString[center + i]);
				userString = this->hash;
				this->hash.clear();
			}
			unsigned int rem = realminLen - hashlenght;

			for (unsigned int i = 0, countCompress = realminLen / rem; this->hash.size() < (hashlenght - 4); i++)
			{
				if (i % countCompress == 0) { this->hash += this->receivingExistCodes(userString[i] + userString[++i]); }
				else { this->hash += userString[i]; }
			}
			// Adding original salts
			this->hash += this->receivingExistCodes(originalSault);
			this->hash += this->receivingExistCodes(originalLenghtStr);
			// Добавление максимальных солей
			this->hash += this->receivingExistCodes(maxSault);
			this->hash += this->receivingExistCodes(maxLenghtStr);
			return this->hash;
		}
		return "";
	}
};
