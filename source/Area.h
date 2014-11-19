#ifndef _AREA_H
#define _AREA_H 

#include <QString>
#include <opencv2/opencv.hpp>
#include <vector>

class Area
{
public:
	bool contains(const cv::Point &p) const;
	void add(const cv::Point &p);
	void clear();

	inline const QString &getGroup() const { return group; }
	inline void setGroup(const QString &val) { group = val; }

private:
	QString group;
	std::vector<cv::Point> points;
	std::vector<cv::Point> polygon;
};

#endif /* _AREA_H */
