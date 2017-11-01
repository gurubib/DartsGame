#pragma once

#include <opencv2\opencv.hpp>
#include <string>

struct Point {
	int x;
	int y;
};

class TableWindow {

	cv::Mat table_;
	std::string fileName_;
	std::string windowName_;
	Point lastClicked_;
	int edge_;
	int tableWidth_;
	int tableHeight_;
	
	

public:

	TableWindow() {}
	TableWindow(std::string fileName, std::string windowName) : fileName_{ fileName }, windowName_{ windowName } {}

	cv::Mat getTable() const { return table_; }
	std::string getFileName() const { return fileName_; }
	std::string getWindowName() const { return windowName_; }
	Point * getLastClicked() { return &lastClicked_; }
	int getScore();

	Point getEdge();
	Point getCentre();
	void setParams();
	void init();
	void show();
};

void mouseCallBack(int event, int x, int y, int flags, void * userdata);

