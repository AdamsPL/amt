#include "Frame.h"

using namespace cv;

#include <QDebug>

const QImage::Format inputFormat = QImage::Format_RGB888;
const QImage::Format outputFormat = QImage::Format_ARGB32;

void Frame::importMat(const cv::Mat &other)
{
	const int channels = 3;
	mat = other;

	if (other.elemSize() == 1)
		cvtColor(mat, mat, CV_GRAY2BGR, channels);

	QImage rgbImg((uchar*)mat.data, mat.cols, mat.rows, inputFormat);
	img = rgbImg.convertToFormat(outputFormat);
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

QImage::Format Frame::getImageFormat()
{
	return outputFormat;
}
