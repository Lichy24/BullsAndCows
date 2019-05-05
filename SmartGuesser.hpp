#pragma once
#include "Guesser.hpp"
#include "calculate.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <map>
namespace bullpgia {
	class SmartGuesser : public Guesser
	{
		/*
		this is the smart guesser algorthim which suppose to guess any number given in 7 turns
			the maximum number of steps go thorught is 7 their for there are 7 turns in max it need to guess for the correct anwser
			blacklist contains all the incorrect digits of the code
			pgia will contains the correct numbers
			Bull will contain the correct digits by their postions
			A,B to sets of two group digits enable us to fixate on the correct digits
			if in any of step you get 4,0 you dont need to continue the steps any further. 
			step 1:
			no reply, guess random numbers
			step 2:
			if 0,0 add to blacklist all the 4 digits go to step 1 and repeat the steps
			if 1,0 split to two groups A and B swap digits of one the two groups, if reply is still 1,0 then the current group
			conatins wrong digits and second group contains the 'Bull' ,else (0,1) current group contain the 'Bull' and second group
			contains wrong digits.
			if 2,0 split to two groups A and B swap digits of one the two groups, if reply is still 2,0 then the current group
			conatins wrong digits and second group contains both 'Bull' ,if 0,2 current group contains both 'Bull' and second group
			contains wrong digits, if 1,1 current group contains 1 'Bull' and second group conatins 1 'Bull' then contiue to step 3
			step 3:
			if you got 2 'bulls' in both groups pick 1 group replace one of its digit with new digit if the number of 'Bulls'
			decrease then a 'Bull' was remove else (3 bulls , 2 bulls and 1 pgia, 2 bulls) the incorrect digit was remove and second digit is 'Bull'
			and the new digit can be mark as incorret , pgia , bull by given reply.
			(if new number incorrect replace in next guess,'Bull' stay as is,pgia replace to new postion)
			step 4:
			if you had 2 groups contain in each one, one 'bull' and determent where in one of the groups the is 'bull'
			then check second group same as you did in step 3. 
			step 5:
			if you have 2 know 'bulls' and less then 3 digits guess the 2 'Bulls' with 2 new valid digits
			if was added 1 'pgia or 1 bull continue to step 6,else (2 'pgia') swap two new digits and guess soltuion.
			step 6:
			if you have 2 know 'bulls' and group contains 1 'pgia' and have 1 digit left  then pick the group and replace
			one of his digits with the last digit left  if 1 'bull' the other digit which was replace is the 'pgia'
			replace the incorrect digit with the pgia and guess
			else (2 'pgia') swap two new digits and guess soltuion
			step 7:
			done guess solution
		*/
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
