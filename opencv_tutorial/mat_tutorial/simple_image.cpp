#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // namedWindow("img", 0); // 2번째 파라미터를 0으로주면 윈도우 창 크기 reseize 불가능

    Mat img = imread("../example.png");
    
    Mat img2 = img.clone();
    flip(img, img2, 1);

    Rect r(img.cols/4, img.rows/4, img.cols/4*2, img.rows/4*2);
    Mat img3 = img(r).clone();

    Mat img4(Size(img.cols*2, img.rows), img.type());
    img4.setTo(255);
    img.copyTo(img4(Range::all(), Range(0, img.cols)));
    img2.copyTo(img4(Range::all(), Range(img2.cols, img2.cols*2)));

    Mat img5;
    img.copyTo(img5);
    Mat roi = img5(r);
    bitwise_not(roi, roi);
    
    imshow("img", img);
    imshow("img2-flip", img2);
    imshow("img3-cut", img3);
    imshow("img4-combine", img4);
    imshow("img5-mix", img5);
    
    waitKey(0);
    destroyAllWindows();
    return 0;
}

