#ifndef _FRAME_H
#define _FRAME_H 

#include <opencv2/opencv.hpp>
#include <QImage>

class Frame
{
public:
	Frame(const cv::Mat &other);
	Frame(const QString filename);
	~Frame();

	const cv::Mat &getData() const;
	const QImage &getImg() const;
	bool equals(const Frame &other) const;

	bool operator==(const Frame &other) const;

	static QImage::Format getImageFormat();

private:
	void importMat(const cv::Mat &other);

	cv::Mat mat;
	QImage img;
};

#endif /* _FRAME_H */
