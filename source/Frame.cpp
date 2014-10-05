#include "Frame.h"

using namespace cv;

const QImage::Format imgFormat = QImage::Format_ARGB32;

void Frame::importMat(const cv::Mat &other)
{
	const int channels = 4;

	cvtColor(other, mat, CV_BGR2RGBA, channels);
	img = QImage((uchar*)mat.data, mat.cols, mat.rows, imgFormat);
}

Frame::Frame(const cv::Mat &copy)
{
	importMat(copy);
}

Frame::Frame(const QString filename)
{
	importMat(imread(filename.toStdString()));
}

Frame::~Frame()
{
}

const cv::Mat &Frame::getData() const
{
	return mat;
}

const QImage &Frame::getImg() const
{
	return img;
}

bool Frame::equals(const Frame &other) const
{
	if (img.byteCount() != other.img.byteCount())
		return false;
	return (memcmp(img.constBits(), other.img.constBits(), img.byteCount()) == 0);
}

bool Frame::operator==(const Frame &other) const
{
	return equals(other);
}
