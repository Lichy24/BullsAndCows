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
	if ((turn-1) <= 10) {
		if (bull > 0) {
			bull_count[myguess[0]-'0'] = bull;
		}
	}
	else {
		//if did not reach end of guess or did not finsh find all the current digit bulls
		if (track < length && !pick) {
			//didn't have an old bull;
			if (oldbull > -1) {
				//if oldbull is bigger meaning we lost a bull so current digit was a bull
				if (oldbull > bull)
				{
					finalguess[track] = currentdigit;//save digit in final guess in the correct postion
					bull_count[currentdigit]--;
				}
				// if oldbull is smaller meaning we have gained a bull from the replace digit
				else if (oldbull < bull)
				{
					finalguess[track] = swap_digit;//save digit in final guess in the correct postion
					bull_count[swap_digit]--;
				}
				//check if still more bulls to find in current digit
				if (bull_count[currentdigit] > 0)
				{
					track++;
					myguess[track] = '0' + swap_digit;
				}
				//else no more bulls left in current digit and should pick an new digit to check
				else pick = !pick;
			}
			else {
				//without checking the current guess swap digit should occur only once
				myguess[track] = '0' + swap_digit;
			}
			oldbull = bull;//update oldbull
		}
		//pick new number to know its bull
		if (pick){
			grpcheck = GroupsLeft(bull_count);
			if (grpcheck <= 1) {//if less then 1 setup final guess
				myguess = setFinalGuess(finalguess, lastdigit);
			}
			else {
				//pick number to fill on.
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
				//pick number which replace the old one.
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
	//first fill bulls
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


