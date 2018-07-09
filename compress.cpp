#include "compress.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

compress::compress()
{
	jpegCompressor = tjInitCompress();
}


compress::~compress()
{
}

/* This method compresses 3-channel RGB matrices to JPEG*/
long unsigned int compress::compressRGBJpeg(uchar* frame, uchar **compressed, int width, int height, int quality) {

	long unsigned int jpegSize = 0;
	tjCompress2(jpegCompressor, frame, width, 0, height, TJPF_RGB, compressed, &jpegSize,
		TJSAMP_444, quality, TJFLAG_FASTDCT);
	return jpegSize;

}

/* This method compresses 1-channel images */
long unsigned int compress::compressBandJpeg(uchar* frame, uchar **compressed, int width, int height, int quality) {
	long unsigned int jpegSize = 0;
	tjCompress2(jpegCompressor, frame, width, 0, height, TJPF_GRAY, compressed, &jpegSize,
		TJSAMP_GRAY, quality, TJFLAG_FASTDCT);
	return jpegSize;
}

/* This method takes a 3-D matrix (image) with band bands and returns a cv::Mat ptr */
cv::Mat* compress::getMatFromArray(uchar*** ar, int rows, int cols, int bands) {
	int sizes[] = { rows, cols, bands };
	Mat* ret = new Mat(3, sizes, CV_8U);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			for (int b = 0; b < bands; ++b) {
				ret->at<uchar>(i, j, b) = ar[i][j][b];
			}
		}
	}
	return ret;
}

uchar* compress::getArrayFromMat(cv::Mat frame) {
	uchar* ar = new uchar[frame.cols * frame.rows * frame.channels()];

	for (int row = 0; row < frame.rows; ++row) {
		for (int col = 0; col < frame.cols; ++col) {
			Vec3b pixel = frame.at<Vec3b>(row, col);
			for (int band = 0; band < frame.channels(); ++band) {
				ar[row*frame.cols*frame.channels() + col * frame.channels() + band] = pixel[frame.channels() - 1 - band];
			}
		}
	}
	return ar;
}
