#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include "QFileDialog"
#include "QStandardPaths"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

QImage Mat2Qimage(cv::Mat const& src);

#endif // MATTOQIMAGE_H
