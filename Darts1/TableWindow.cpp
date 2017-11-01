#include "TableWindow.h"
#include <cmath>

const double M_PI = 3.14159265359;

Point TableWindow::getEdge() {
	cv::waitKey(0);
	std::cout << lastClicked_.x << " " << lastClicked_.y;
	return lastClicked_;
}

Point TableWindow::getCentre() {
	cv::waitKey(0);
	std::cout << lastClicked_.x << " " << lastClicked_.y;
	return lastClicked_;
}

void TableWindow::setParams() {
	Point centre = getCentre();

	tableWidth_ = centre.x;
	tableHeight_ = centre.y;

	Point edge = getEdge();

	int edgeX = edge.x - tableWidth_;
	int edgeY = edge.y - tableHeight_;

	edge_ = sqrt(edgeX*edgeX + edgeY*edgeY);

}

void TableWindow::init() {
	table_ = cv::imread(fileName_, CV_LOAD_IMAGE_COLOR);

	if (table_.empty())
		std::cout << "Could not open the image!" << std::endl;

	cv::namedWindow(windowName_, CV_WINDOW_AUTOSIZE);
}

void TableWindow::show() {
	cv::imshow(windowName_, table_);
}

int TableWindow::getScore() {
	cv::waitKey(0);

	int x = lastClicked_.x;
	int y = lastClicked_.y;
	
	//Transforming the coordinates
	x -= tableWidth_;
	y -= tableHeight_;
	y *= -1;

	//Default params
	const int Sectors[20] = { 6, 13, 4, 18, 1, 20, 5, 12, 9, 14, 11, 8, 16, 7, 19, 3, 17, 2, 15, 10};
	int multip = 1;
	//double edge = 0.7 * (table_.cols / 2);

	//Polar coordinates
	double fi;
	double r = sqrt(x*x + y*y);

	//Checking the simplest cases
	if (r <= 0.03735 * edge_)
		return 50;
	else if (r <= 0.09355 * edge_)
		return 25;
	else if (r > 0.5835 * edge_ && r <= 0.6306 * edge_)
		multip = 3;
	else if (r > 0.9529 * edge_ && r <= edge_)
		multip = 2;
	else if (r > edge_)
		return 0;

	//Calculating the angle
	if (y != 0)
		fi = atan((double)y / x);
	else
		fi = y > 0 ? (M_PI / 2) : 3 * (M_PI / 2);

	//Adjusting the angle
	if (x > 0 && y > 0)
		fi = fi;
	else if (x < 0 && y > 0)
		fi += M_PI;
	else if (x < 0 && y < 0)
		fi += M_PI;
	else if (x > 0 && y < 0)
		fi += 2 * M_PI;

	//Matching the angle with the sector
	int i;
	double tmpFI = (-1 * M_PI) / 20;
	for (i = 0; i < 20; ++i)
	{
		if (tmpFI + M_PI / 10 > fi)
			return multip*Sectors[i];
		else if ((39 * M_PI) / 20 < fi && fi < 2 * M_PI)
			return 6;
		else
			tmpFI += M_PI / 10;
	}

	//Error code
	return -1;
}

void mouseCallBack(int event, int x, int y, int flags, void * userdata) {
	if (event == CV_EVENT_LBUTTONDOWN) {
		static_cast<Point *>(userdata)->x = x;
		static_cast<Point *>(userdata)->y = y;
	}
}