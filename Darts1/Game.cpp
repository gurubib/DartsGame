#include "Game.h"

Game::Game(TableWindow table) : round_{ 0 }, state_{ GameState::INIT } {
	table_ = TableWindow{ table.getFileName(), table.getWindowName() };
}

int Game::nextPlayer() {
	int nextPlayer = currPlayer + 1;
	if (nextPlayer > players_.size())
		nextPlayer = 1;

	return nextPlayer;
}

void Game::won() {
	std::cout << "*****************" << std::endl;
	std::cout << "The Winner is: " << players_[currPlayer - 1] << std::endl;
	std::cout << "*****************" << std::endl;
}

void Game::play(int playerNum) {
	init(playerNum);
	loop(playerNum);

	//cv::waitKey();
}

void Game::init(int playerNum) {
	table_.init();
	table_.show();
	cv::waitKey(1);

	for (int i = 0; i < playerNum; ++i) {
		Player temp;
		std::cin >> temp;
		addPlayer(temp);
	}

	int firstpNum;
	std::cout << "The first player is (Player number): ";
	std::cin >> firstpNum;

	setFirstPlayer(firstpNum);

	cvSetMouseCallback(table_.getWindowName().c_str(), mouseCallBack, table_.getLastClicked());
	
	std::cout << "First click the centre of the playing area!" << std::endl;
	std::cout << "Then click the edge of the playing area!" << std::endl;
	table_.setParams();

	state_ = GameState::GOING;
}

void Game::setFirstPlayer(int playerNum) {
	currPlayer = playerNum;
}

void Game::addPlayer(Player p) {
	players_.push_back(p);
}

void Game::loop(int playerNum) {
	int i = 0;
	bool quit = false;
	while (!quit) {

		switch (state_) {
			case GameState::INIT : break;

			case GameState::GOING :
				if((i++) % 2 == 0)
					round_++;
				
				playTurn();

				if (players_[currPlayer - 1].getScore() == 0)
					state_ = GameState::END;

				currPlayer = nextPlayer();

				break;
			
			case GameState::END :
				won();
				
				quit = true;
				break;
		}

	}
}

void Game::playTurn() {
	Player currentP = players_[currPlayer - 1];

	std::cout << std::endl << std::endl << "=========================================" << std::endl;
	std::cout << round_ << ". Round : " << currentP.getName() << " - score: " << currentP.getScore() << std::endl;

	int invScore;
	int fullScore = 0;
	//int originalScore = currentP.getScore();

	for (int i = 0; i < 3; ++i) {
		int score = table_.getScore();
		fullScore += score;

		std::cout << "\t \t Thrown: " << score << std::endl;

		if (fullScore > currentP.getScore()) {
			players_[currPlayer - 1].setScore(currentP.getScore());
			break;
		}
		else {
			players_[currPlayer - 1].setScore(currentP.getScore() - fullScore);
		}
	}


	std::cout << std::endl << "\t Full Thrown: " << fullScore << std::endl;
	std::cout << "New score: " << players_[currPlayer - 1].getScore() << std::endl << std::endl;
	system("pause");
}

Game::~Game()
{
}
