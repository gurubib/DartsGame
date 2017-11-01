#pragma once

#include <iostream>
#include <string>

class Player {
	
	std::string name_;
	int score_;

	public:
		Player();
		Player(std::string name) : name_{ name }, score_{ 301 } {}

		std::string getName() const { return name_; }
		int getScore() const { return score_; }
		void setScore(int score);

		~Player();
};

std::ostream & operator<<(std::ostream & os, Player const & p);
std::istream & operator>>(std::istream & is, Player & p);