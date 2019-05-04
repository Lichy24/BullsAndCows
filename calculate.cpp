#include <vector>
#include "calculate.hpp"
std::string calculateBullAndPgia(std::string choose, std::string guess) {
	int bull = 0, pgia = 0,maxdup;
	std::string reply;
	int i = 0,j = 0;
	for (size_t i = 0; i < choose.length(); i++)
	{
		if (guess[i] == choose[i]) {
			bull++;
			guess[i] = '*';
			choose[i] = '*';
		}
	}
	for (size_t i = 0; i < choose.length(); i++)
	{
		if (choose[i] != '*') {
			for (size_t j = 0; j < guess.length(); j++)
			{
				if (choose[i] == guess[j]) {
					pgia++;
					guess[j] = '*';
					break;
				}
			}
		}
	}
	reply = std::to_string(bull).append(",").append(std::to_string(pgia));
	return reply;
};