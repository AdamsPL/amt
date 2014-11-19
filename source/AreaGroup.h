#ifndef _AREAGROUP_H
#define _AREAGROUP_H 

#include <set>
#include <opencv2/opencv.hpp>

class Area;

class AreaGroup
{
public:
	void add(const Area *area);
	void remove(const Area *area);
	bool contains(const cv::Point &point);

private:
	std::set<const Area*> areas;
};

#endif /* _AREAGROUP_H */
