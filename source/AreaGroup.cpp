#include "AreaGroup.h"

#include "Area.h"

using namespace std;

void AreaGroup::addArea(const Area *area)
{
	areas.insert(area);
}

bool AreaGroup::contains(const cv::Point &point)
{
	for (set<const Area *>::const_iterator iter = areas.begin(); iter != areas.end(); iter++) {
		if ((*iter)->contains(point))
			return true;
	}
	return false;
}
