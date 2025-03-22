#pragma once
#include "deck.h"
#include <iostream>
#include <Windows.h>

class Game
{
public:
	Game();
	bool init();
	void play();

	int players = 0;
	std::vector<Deck> playersDecks = {};

private:
	Deck mainDeck = {};
	Card topCard = {};
	int currentTurn = 0;
};

Game::Game()
{
}

inline bool Game::init()
{
	// first of all, setup the main deck ofc
	mainDeck.init();

	// ask for the amount of players
	std::cout << "How many players are playing?\n >> ";
	std::cin >> players;

	if (players < 2 || players > 10) {
		std::cout << "Invalid amount of players. Please choose between 2 and 10 players.\n";
		return false;
	}

	playersDecks.resize(players);

	for (int i = 0; i < players; i++) {
		Deck deck;
		playersDecks[i] = mainDeck.drawBulk(7);
		mainDeck.shuffle();
	}

	return true;
}

inline void Game::play()
{
	while (true) {
		system("cls"); // clear the console

		// get the current player's deck
		Deck& currentPlayerDeck = playersDecks[currentTurn];

		// print the current game's deck
		std::cout << "Game's Deck:\n";
		mainDeck.printDeck(true);

		// print the top/last card
		std::cout << "Last Card:\n(";
		topCard.printCard(false);
		std::cout << ")\n\n";

		std::cout << "Player " << currentTurn + 1 << "'s turn...\n"
				  << "Your Deck:\n";
		currentPlayerDeck.printDeck();

		// ask for the card to play
		std::cout << "- Choose a card to play (1-" << currentPlayerDeck.cards.size() << ")\n- Or (0) to draw a card\n";
		// make sure the player chooses a correct index
		Card drawnCard = {};
		while (drawnCard.name.empty()) {
			int cardIndex;
			std::cout << ">> ";
			std::cin >> cardIndex;
			if (cardIndex == 0) {
				drawnCard = mainDeck.drawRandom();
				currentPlayerDeck.cards.push_back(drawnCard);
				continue;
			}
			topCard = drawnCard = currentPlayerDeck.drawIndex(cardIndex - 1);
		}

		// check if the card is valid
		if (drawnCard.color != topCard.color && drawnCard.value != topCard.value && !drawnCard.isWild) {
			std::cout << "Invalid card. Please choose another one.\n";
			Sleep(2000);
			continue;
		}

		// rotate the turn
		currentTurn = (currentTurn + 1) % players;
	}
}