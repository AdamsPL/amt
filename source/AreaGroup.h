#ifndef _AREAGROUP_H
#define _AREAGROUP_H 

#include <opencv2/opencv.hpp>
#include <set>

class Area;

class AreaGroup
{
public:
	void addArea(const Area *area);
	bool contains(const cv::Point &point);

private:
	std::set<const Area*> areas;
};

#endif /* _AREAGROUP_H */
