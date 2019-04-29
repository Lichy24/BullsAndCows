#pragma once
#include <string>
namespace bullpgia {
	class Guesser
	{
	public:
		Guesser() {};
		virtual ~Guesser() {};
		uint length;
		virtual std::string guess() {
			return "";
		};
		virtual void startNewGame(uint length) {
			this->length = length;
		};
		virtual void learn(std::string reply) {
			
		};
	};
}
