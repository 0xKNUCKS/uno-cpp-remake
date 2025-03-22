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

		// print the current game's deck
		std::cout << "Game's Deck:\n";
		mainDeck.printDeck(true);

		std::cout << "Player " << currentTurn + 1 << "'s turn...\n"
				  << "Your Deck:\n";
		playersDecks[currentTurn].printDeck();

		// rotate the turn
		currentTurn = (currentTurn + 1) % players;

		std::system("pause>0"); // wait for user input
	}
}