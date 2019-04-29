#include "DummyGuessers.hpp"
#include <stdlib.h>
#include <string>

std::string RandomGuesser::guess() {
	std::string r = "";
	for (uint i = 0; i < this->length; ++i) {
		char c = '0' + (rand() % 10);
		r += c;
	}
	return r;
}