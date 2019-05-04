#include "SmartGuesser.hpp"






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
	//Returns the number of seconds since the UNIX epoch for a seed
	srand(time(0));

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
		bullpgia::SmartGuesser::currentGuess = { 1,1,2,2 };
	return vector_to_string(bullpgia::SmartGuesser::currentGuess);
}
