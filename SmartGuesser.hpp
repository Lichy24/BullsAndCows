#pragma once
#include "Guesser.hpp"
#include "calculate.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
namespace bullpgia {
	class SmartGuesser : public Guesser
	{
	private:
		std::string myguess;
		std::vector<char> blacklist;
		int bull_count[10];
		std::vector<int> finalguess;
		int bull, pgia,currentdigit,swap_digit,grpcheck,lastdigit,track,turn;
		int oldpgia=0,oldbull = -1;
		bool pick;
		uint length;
		std::string fillCode(char digit);
		std::string Respones(uint bull,uint pgia);
		int GroupsLeft(int arr[]);
		std::string setFinalGuess(std::vector<int> vec);
		std::string setFinalGuess(std::vector<int> vec,int lastdigit);
	public:
		void learn(std::string reply);
		std::string guess();
		void startNewGame(uint length);
	};
}
