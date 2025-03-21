#pragma once
#include "deck.h"
#include <iostream>

class Game
{
public:
	Game();
	void init();
	void play();

	int players;
	std::vector<Deck> decks;

private:

};

Game::Game()
{
}

inline void Game::init()
{
	std::cout << "How many players are playing?\n >> ";
	std::cin >> players;

	
}

inline void Game::play()
{
}

Game::~Game()
{
}