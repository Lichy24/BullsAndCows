#include <vector>
#include "calculate.hpp"
std::string calculateBullAndPgia(std::string choose, std::string guess) {
	int bull = 0, pgia = 0,maxdup;
	std::string reply;
	if (choose.empty() || guess.empty())
		throw "invalid input";
	if (choose.length() != guess.length())
		throw "inequal length";
	int i = 0,j = 0;
	//Check for bulls
	//Check for pgia
	reply = std::to_string(bull).append(",").append(std::to_string(pgia));
	return reply;
};