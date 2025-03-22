#pragma once
#include <vector>
#include <string>
#include <format>
#include <random>
#include "card.h"

class Deck
{
public:
	Deck() {};
	void init();
	void shuffle();
	Card drawRandom();
	Deck drawBulk(int amount);
	void printDeck(bool hidden = false);

	std::vector<Card> cards = {};

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

inline void Deck::init()
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
    if (this->cards.empty()) {
        return Card(); // Return an empty card if the deck is empty
    }

    std::uniform_int_distribution<int> distr(0, static_cast<int>(cards.size()) - 1);
    int randomIndex = distr(gen);

    // get the card
    Card resultCard = this->cards[randomIndex];

    // remove it from the deck
    this->cards.erase(this->cards.begin() + randomIndex);

	this->cards.shrink_to_fit();

    return resultCard;
}

inline Deck Deck::drawBulk(int amount)
{
	Deck newDeck;

	// before anything, check if the deck is empty
	if (this->cards.size() == 0) {
		return newDeck;
	}

	// then, make sure the amount is in the correct boundaries
	amount = std::min(amount, (int)this->cards.size());

	// identify locations of the cards to be drawn
	auto it = this->cards.begin();
	auto end = this->cards.begin() + amount;

	// copy the cards to the new deck
	std::copy(it, end, std::back_inserter(newDeck.cards));
	// delete them from the current deck
	this->cards.erase(it, end);

	this->cards.shrink_to_fit();

	// ez
	return newDeck;
}

inline void Deck::printDeck(bool hidden)
{
	for (int i = 0; i <= this->cards.size() - 1; i++) {
		Card card = this->cards[i];

		// print the cards in a hidden format ([x, x, x, x, x...])
		if (hidden) {
			// print the first
			if (i == 0) {
				std::cout << "[";
			}

			std::cout << "x" << ((i == this->cards.size() - 1) ? "" : ", ");

			// ... and last bracket
			if (i == this->cards.size() - 1) {
				std::cout << "]\n";
			}
			continue;
		}
		else {
			// print their index with the card name AND color (colored)
			std::cout << std::format("{}: ", i + 1);
			if (card.isWild) {
				std::cout << std::format("\033[1;35m{}\033[0m\n", card.name); // wild cards in magenta
			}
			else if (card.color == "Red") {
				std::cout << std::format("\033[1;31m{}\033[0m\n", card.name);
			}
			else if (card.color == "Yellow") {
				std::cout << std::format("\033[1;33m{}\033[0m\n", card.name);
			}
			else if (card.color == "Green") {
				std::cout << std::format("\033[1;32m{}\033[0m\n", card.name);
			}
			else if (card.color == "Blue") {
				std::cout << std::format("\033[1;34m{}\033[0m\n", card.name);
			}
		}
	}

	std::cout << "\n";
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
