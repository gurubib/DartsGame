#include "Player.h"



Player::Player()
{
}

void Player::setScore(int score) {
	score_ = score;
}

std::ostream & operator<<(std::ostream & os, Player const & p) {
	os << p.getName() << ": " << p.getScore() << " score" << std::endl;
	
	return os;
}
std::istream & operator>>(std::istream & is, Player & p) {
	std::string name;
	
	std::cout << "Player's name: ";
	is >> name;

	p = Player{ name };
	
	return is;
}

Player::~Player()
{
}
