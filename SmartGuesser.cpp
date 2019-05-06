#include "SmartGuesser.hpp"





std::string bullpgia::SmartGuesser::fillCode(char digit)
{
	std::string res = "";
	for (size_t i = 0; i < length; i++)
	{
		res += digit;
	}
	return res;
}


std::string bullpgia::SmartGuesser::Respones(uint bull, uint pgia)
{
	std::string res = "" +std::to_string(bull) + "," + std::to_string(pgia);
	return res;
}

int bullpgia::SmartGuesser::GroupsLeft(int arr[])
{
	int count = 0;
	for (size_t i = 0; i < 10; i++)
	{
		if (arr[i] > 0)
		{
			lastdigit = i;
			count++;
		}
	}
	return count;
}

std::string bullpgia::SmartGuesser::setFinalGuess(std::vector<int> vec)
{
	std::string result;
	std::stringstream ss;
	for (size_t i = 0; i < length; i++)
	{
		ss << vec[i];
	}
	result = ss.str();
	std::cout << turn << std::endl;
	std::cout << result << std::endl;
	return result;
}

std::string bullpgia::SmartGuesser::setFinalGuess(std::vector<int> vec, int lastdigit)
{
	for (size_t i = 0; i < length; i++)
	{
		if (vec[i] == -1)
			vec[i] = lastdigit;
	}
	return setFinalGuess(vec);
}


void bullpgia::SmartGuesser::learn(std::string reply)
{
	//done
	if (reply == Respones(length, 0))
		return;
	std::istringstream(reply.substr(0, reply.find(","))) >> bull;
	std::istringstream(reply.substr(1 + reply.find(","), reply.length() - 1)) >> pgia;
	if ((turn-1) <= 10) {
		if (bull > 0) {
			bull_count[myguess[0]-'0'] = bull;
		}
	}
	else {
		if (track < length && !pick) {
			if (oldbull > -1) {
				if (oldbull > bull)
				{
					finalguess[track] = currentdigit;
					bull_count[currentdigit]--;
				}
				else if (oldbull < bull)
				{
					finalguess[track] = swap_digit;
					bull_count[swap_digit]--;
				}
				if (bull_count[currentdigit] > 0)
				{
					track++;
					myguess[track] = '0' + swap_digit;
				}
				else pick = !pick;
			}
			else {
				myguess[track] = '0' + swap_digit;
			}
			oldbull = bull;
		}
		if (pick){
			grpcheck = GroupsLeft(bull_count);
			if (grpcheck <= 1) {
				myguess = setFinalGuess(finalguess, lastdigit);
			}
			else {
				for (size_t i = 0; i < 10; i++)
				{
					if (bull_count[i] > 0)
					{
						myguess = fillCode('0' + i);
						track = 0;
						currentdigit = i;
						oldbull = -1;
						pick = false;
						break;
					}
				}
				for (size_t j = 0; j < 10; j++)
				{
					if (bull_count[j] > 0 && j != currentdigit)
						swap_digit = j;
				}
			}
		}
	}
}

std::string bullpgia::SmartGuesser::guess()
{
	switch (turn)
	{
	case 1:
		myguess = fillCode('1');
		break;
	case 2:
		myguess = fillCode('2');
		break;
	case 3:
		myguess = fillCode('3');
		break;
	case 4:
		myguess = fillCode('4');
		break;
	case 5:
		myguess = fillCode('5');
		break;
	case 6:
		myguess = fillCode('6');
		break;
	case 7:
		myguess = fillCode('7');
		break;
	case 8:
		myguess = fillCode('8');
		break;
	case 9:
		myguess = fillCode('9');
		break;
	case 10:
		myguess = fillCode('0');
		break;
	default:
		break;
	}
	turn++;
	return myguess;
}

void bullpgia::SmartGuesser::startNewGame(uint length)
{
	std::cout << "start new game" << std::endl;
	this->length = length;
	turn = 1;
	track = 0;
	currentdigit = 0;
	lastdigit = 0;
	pick = true;
	
	for (size_t i = 0; i < 10; i++)
	{
		bullpgia::SmartGuesser::bull_count[i] = 0;
	}
	finalguess.clear();
	for (size_t i = 0; i < length; i++)
	{
		finalguess.push_back(-1);
	}
}

/*
std::vector<int> bullpgia::SmartGuesser::getNextGuess(std::vector<std::vector<int>> nextGuesses)
{
	std::vector<int> nextGuess;

	for (int i = 0; i < nextGuesses.size(); ++i) {
		if (std::find(bullpgia::SmartGuesser::candidateSolutions.begin(), bullpgia::SmartGuesser::candidateSolutions.end(), nextGuesses[i]) != bullpgia::SmartGuesser::candidateSolutions.end()) {
			return nextGuesses[i];
		}
	}
	for (int j = 0; j < nextGuesses.size(); ++j) {
		if (std::find(bullpgia::SmartGuesser::combinations.begin(), bullpgia::SmartGuesser::combinations.end(), nextGuesses[j]) != bullpgia::SmartGuesser::combinations.end()) {
			return nextGuesses[j];
		}
	}

	return nextGuess;
}

std::vector<int> bullpgia::SmartGuesser::getRandomCode()
{
	std::vector<int> code;
	int max = 9;
	int min = 0;
	int random;

	for (int i = 0; i < length; ++i) {

		random = min + (rand() % (max - min + 1));
		code.push_back(random);
	}

	return code;
}

void bullpgia::SmartGuesser::createSet()
{
	std::vector<int> current(length, 0);
	std::vector<int> elements;

	for (int i = 0; i <= 9; ++i) {
		elements.push_back(i);
	}

	combinationRecursive(length, 0, current, elements);
}

void bullpgia::SmartGuesser::combinationRecursive(int combinationLength, int position, std::vector<int>& current, std::vector<int>& elements)
{
	if (position >= combinationLength) {
		combinations.push_back(current);
		return;
	}

	for (int j = 0; j < elements.size(); ++j) {
		current[position] = elements[j];
		combinationRecursive(combinationLength, position + 1, current, elements);
	}
	return;
}

void bullpgia::SmartGuesser::removeCode(std::vector<std::vector<int>>& set, std::vector<int> currentCode)
{
	int index;
	for (auto it = set.begin(); it != set.end(); it++) {
		index = distance(set.begin(), it);

		if (set[index] == currentCode) {
			set.erase(set.begin() + index);
			break;
		}
	}
}

void bullpgia::SmartGuesser::pruneCodes(std::vector<std::vector<int>>& set, std::vector<int> currentCode, std::string currentResponse)
{
	int index;
	std::vector<std::vector<int>>::iterator it = set.begin();

	while (it != set.end()) {
		index = distance(set.begin(), it);

		if (currentResponse != calculateBullAndPgia(vector_to_string(currentCode), vector_to_string(set[index]))) {
			it = set.erase(set.begin() + index);
		}
		else {
			it++;
		}
	}
}

std::vector<std::vector<int>> bullpgia::SmartGuesser::minmax()
{
	std::map<std::string, int> scoreCount;
	std::map<std::vector<int>, int> score;
	std::vector<std::vector<int>> nextGuesses;
	int max, min;

	for (int i = 0; i < combinations.size(); ++i) {

		for (int j = 0; j < candidateSolutions.size(); ++j) {

			std::string pegScore = calculateBullAndPgia(vector_to_string(combinations[i]), vector_to_string(candidateSolutions[j]));
			if (scoreCount.count(pegScore) > 0) {
				scoreCount.at(pegScore)++;
			}
			else {
				scoreCount.emplace(pegScore, 1);
			}
		}

		max = getMaxScore(scoreCount);
		score.emplace(combinations[i], max);
		scoreCount.clear();
	}

	min = getMinScore(score);

	for (auto elem : score) {
		if (elem.second == min) {
			nextGuesses.push_back(elem.first);
		}
	}

	return nextGuesses;
}

int bullpgia::SmartGuesser::getMaxScore(std::map<std::string, int> inputMap)
{
	int max = 0;
	for (auto elem : inputMap) {
		if (elem.second > max) {
			max = elem.second;
		}
	}

	return max;
}

int bullpgia::SmartGuesser::getMinScore(std::map<std::vector<int>, int> inputMap)
{
	int min = std::numeric_limits<int>::max();
	for (auto elem : inputMap) {
		if (elem.second < min) {
			min = elem.second;
		}
	}

	return min;
}

std::string bullpgia::SmartGuesser::vector_to_string(std::vector<int> vec)
{
	std::string result = "";
	for (size_t i = 0; i < vec.size(); i++)
	{
		result += vec[i];
	}
	return result;
}

void bullpgia::SmartGuesser::learn(std::string reply)
{
	if (first_try) {
		createSet();
		bullpgia::SmartGuesser::candidateSolutions.insert(bullpgia::SmartGuesser::candidateSolutions.end(), bullpgia::SmartGuesser::combinations.begin(), bullpgia::SmartGuesser::combinations.end());
		first_try = false;
	}
	removeCode(bullpgia::SmartGuesser::combinations, bullpgia::SmartGuesser::currentGuess);
	removeCode(bullpgia::SmartGuesser::candidateSolutions, currentGuess);

	//Remove from candidateSolutions,
	//any code that would not give the same response if it were the code
	pruneCodes(bullpgia::SmartGuesser::candidateSolutions, bullpgia::SmartGuesser::currentGuess, reply);

	//Calculate Minmax scores
	bullpgia::SmartGuesser::nextGuesses = minmax();

	//Select next guess
	bullpgia::SmartGuesser::currentGuess = getNextGuess(bullpgia::SmartGuesser::nextGuesses);
}
std::string bullpgia::SmartGuesser::guess()
{
	if (first_try)
		bullpgia::SmartGuesser::currentGuess = getRandomCode();
	return vector_to_string(bullpgia::SmartGuesser::currentGuess);
}
*/

