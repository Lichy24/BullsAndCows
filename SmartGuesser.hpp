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
		/*
		bool first_try = true;
		static std::vector<std::vector<int>> combinations; //Master set of combinations 1111 to 6666
		static std::vector<std::vector<int>> candidateSolutions;
		static std::vector<std::vector<int>> nextGuesses;
		static std::vector<int> currentGuess;
		std::string myguess;
		std::vector<int> getNextGuess(std::vector<std::vector<int>> nextGuesses);
		std::vector<int> getRandomCode();
		void createSet();
		void combinationRecursive(int combinationLength, int position, std::vector<int> &current, std::vector<int> &elements);
		void removeCode(std::vector<std::vector<int>> &set, std::vector<int> currentCode);
		void pruneCodes(std::vector<std::vector<int>> &set, std::vector<int> currentCode, std::string currentResponse);
		std::vector<std::vector<int>> minmax();
		int getMaxScore(std::map<std::string, int> inputMap);
		int getMinScore(std::map<std::vector<int>, int> inputMap);
		std::string vector_to_string(std::vector<int> vec);
	*/
		std::string myguess;
		std::vector<char> blacklist;
		int bull_count[10];
		std::vector<int> finalguess;
		int bull, pgia,currentdigit,swap_digit,grpcheck,lastdigit;
		int oldpgia=0,oldbull = -1,track;
		int turn;
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
