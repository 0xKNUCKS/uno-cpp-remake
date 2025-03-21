#pragma once
#include <string>
#include <format>

class Card
{
public:
	Card(std::string color, std::string value);
	Card(std::string name, bool isWild);
	Card() {};
	
	// Card full name
	std::string name;

private:
	// Card properties
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
