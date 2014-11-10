#ifndef _AREA_H
#define _AREA_H 

#include <opencv2/opencv.hpp>
#include <vector>

class Area
{
public:
	bool contains(const cv::Point &p);
	void addPoint(const cv::Point &p);

private:
	std::vector<cv::Point> points;
	std::vector<cv::Point> polygon;
};

#endif /* _AREA_H */
