#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    VideoCapture capture(0); // default camera
    Mat frame;

    if (!capture.isOpened()) return 0;

    namedWindow("video");

    while(1) {
        capture >> frame;

        Sobel(frame, frame, frame.depth(), 1, 0);

        imshow("video", frame);
        if (waitKey(10) > 0) break;
    }
    
    return 0;
}

