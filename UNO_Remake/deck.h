#pragma once
#include <vector>
#include <string>
#include <format>
#include <random>
#include "card.h"

class Deck
{
public:
	Deck();
	void shuffle();
	Card drawRandom();
	Deck drawBulk(int amount);

	std::vector<Card> cards = {};
	
	// temp function
	void printDeck() {
		Deck urDeck = *this;
		std::cout << "[";
		for (Card card : urDeck.cards) {
			std::cout << card.name << ", ";
		}

		std::cout << "]\n\n";
	}

private:
	// Cards Identification
	std::vector<std::string> colors = { "Red", "Yellow", "Green", "Blue" };
	std::vector<std::string> values = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "Skip", "Reverse", "Draw-Two" };
	std::vector<std::string> wildCards = { "Wild-Color", "Draw-Four" };

	// Randoms generator Engine (Mersenne Twister engine)
	std::mt19937 gen{ std::random_device{}() };

	// Deck Setup
	void generate();
};

Deck::Deck()
{
	this->generate();
	this->shuffle();
}

inline void Deck::shuffle()
{
	std::shuffle(this->cards.begin(), this->cards.end(),
		gen);
}

inline Card Deck::drawRandom()
{
	std::uniform_int_distribution<> distr(0, cards.size() - 1);
	int randomIndex = distr(gen);

	// get the card
	Card resultCard = this->cards[randomIndex];

	// remove it from the deck
	this->cards.erase(this->cards.begin() + randomIndex);
	
	return resultCard;
}

inline Deck Deck::drawBulk(int amount)
{
	Deck newDeck;
	// first, copy the cards to the new deck
	std::copy(this->cards.begin(), this->cards.begin() + amount - 1, newDeck.cards.begin());
	printf("Old Deck: ");
	this->printDeck();

	printf("\nNew Deck: ");
	newDeck.printDeck();

	return Deck();
}

void Deck::generate() {
	this->cards.clear();

	// Generate all colored cards
	for (std::string color : this->colors) {
		for (std::string value : this->values) {
			// twice because each card has two per color
			this->cards.push_back(Card(color, value));

			// except for number 0, it only has 1 per color
			if (value != "0")
				this->cards.push_back(Card(color, value));
		}
	}

	// Also add the wild cards
	for (std::string wildCard : this->wildCards) {
		// each wild card has 4 in the deck
		for (int i = 0; i <= 3; ++i) {
			this->cards.push_back(Card(wildCard, true));
		}
	}
}
