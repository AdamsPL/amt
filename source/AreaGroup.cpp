#include "AreaGroup.h"

#include "Area.h"
#include <opencv2/opencv.hpp>

using namespace std;

void AreaGroup::add(const Area *area)
{
	areas.insert(area);
}

void AreaGroup::remove(const Area *area)
{
	areas.erase(area);
}

bool AreaGroup::contains(const cv::Point &point)
{
	for (set<const Area *>::const_iterator iter = areas.begin(); iter != areas.end(); iter++) {
		if ((*iter)->contains(point))
			return true;
	}
	return false;
}
