#pragma once

#include <vector>

#include "Player.h"
#include "TableWindow.h"

enum GameState { INIT, GOING, END };

class Game {

	GameState state_;
	TableWindow table_;
	std::vector<Player> players_;
	int round_;
	int currPlayer;

	int nextPlayer();
	void won();

	public:
		Game(TableWindow table);

		void play(int playerNum = 2);
		void init(int playerNum = 2);
		void setFirstPlayer(int playerNum);
		void addPlayer(Player p);
		void loop(int playerNum = 2);
		void playTurn();
		~Game();
};

