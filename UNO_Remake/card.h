#pragma once
#include <string>
#include <format>

class Card
{
public:
	Card(std::string color, std::string value);
	Card(std::string name, bool isWild);
	Card() {};
	void printCard(bool newLine = true);
	
	// Card properties
	std::string name;
	std::string color;
	std::string value;
	bool isWild = false;
};

Card::Card(std::string color, std::string value)
{
	this->name = std::format("{} {}", value, color);
	this->color = color;
	this->value = value;
}

Card::Card(std::string name, bool isWild)
{
	this->name = name;
	this->isWild = isWild;
}

inline void Card::printCard(bool newLine)
{
	if (this->isWild) {
		std::cout << std::format("\033[1;35m{}\033[0m", this->name); // wild cards in magenta
	}
	else if (this->color == "Red") {
		std::cout << std::format("\033[1;31m{}\033[0m", this->name);
	}
	else if (this->color == "Yellow") {
		std::cout << std::format("\033[1;33m{}\033[0m", this->name);
	}
	else if (this->color == "Green") {
		std::cout << std::format("\033[1;32m{}\033[0m", this->name);
	}
	else if (this->color == "Blue") {
		std::cout << std::format("\033[1;34m{}\033[0m", this->name);
	}

	if (newLine) {
		std::cout << "\n";
	}
}
