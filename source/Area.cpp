#include "Area.h"

bool Area::contains(const cv::Point &p) const
{
	if (polygon.size() == 0)
		return false;

	if (polygon.size() == 1)
		return (polygon[0] == p);

	return (pointPolygonTest(polygon, p, false) >= 0);
}

void Area::addPoint(const cv::Point &p)
{
	points.push_back(p);
	polygon.clear();
	convexHull(points, polygon);
}

void Area::clear()
{
	points.clear();
	polygon.clear();
}
