#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("../example.png"); // Mat은 사실 1차원 데이터
    namedWindow("img", 0);

    // 1. using at
    for (int i=img.rows/10*3; i<img.rows/10*4; ++i) {
        for (int j=0; j<img.cols; ++j) {
            unsigned char b = img.at<cv::Vec3b>(i, j)[0];
            unsigned char g = img.at<cv::Vec3b>(i, j)[1];
            unsigned char r = img.at<cv::Vec3b>(i, j)[2];

            img.at<cv::Vec3b>(i, j)[0] = 255-b;
            img.at<cv::Vec3b>(i, j)[1] = 255-g;
            img.at<cv::Vec3b>(i, j)[2] = 255-r;
        }
    }

    // 2. using ptr
    for (int i=img.rows/10*6; i<img.rows/10*7; i++) {
        cv::Vec3b* ptr = img.ptr<cv::Vec3b>(i);
        for (int j=0; j <img.cols; j++) {
            cv::Vec3b bgr = ptr[j];
            unsigned char b = (bgr[0]);
            unsigned char g = (ptr[j][1]);
            unsigned char r = (bgr[2]);

            ptr[j] = cv::Vec3b(255-b, 255-g, 255-r);
        }
    }

    // using data
    for (int i=img.rows/10*8; i<img.rows/10*9; i++) {
        for(int j=0; j<img.cols; j++) {
            unsigned char r, g, b;
            b = img.data[i*img.step + j*img.elemSize() + 0];
            g = img.data[i*img.step + j*img.elemSize() + 1];
            r = img.data[i*img.step + j*img.elemSize() + 2];

            img.data[i*img.step + j*img.elemSize() + 0] = 255-b;
            img.data[i*img.step + j*img.elemSize() + 1] = 255-g;
            img.data[i*img.step + j*img.elemSize() + 2] = 255-r;
        }
    }

    // using iteration
    cv::MatIterator_<cv::Vec3b> itd = img.begin<cv::Vec3b>(), itd_end = img.end<cv::Vec3b>();
    for (int i=0; itd!=itd_end; ++itd, ++i) {
        cv::Vec3b bgr = (*itd);

        (*itd)[0] = 255 - bgr[0];
        (*itd)[1] = 255 - bgr[1];
        (*itd)[2] = 255 - bgr[2];
    }

    imshow("img", img);
    waitKey(0);
}