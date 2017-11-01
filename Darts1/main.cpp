#include <opencv2\imgproc.hpp>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <string>

#include "TableWindow.h"
#include "Game.h"

int main(int argc, char** argv) {
	
	TableWindow table{"table3.jpg", "tableWindow"};
	
	Game game{table};

	game.play();

	system("pause");

	
	return 0;
}