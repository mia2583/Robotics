#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat img(500, 500, CV_8UC3);
    img.setTo(255); // 흰 배경

    // 1. line
    cv::Point pt(300, 300);
    line(img, Point(10, 10), pt, CV_RGB(255, 0, 0), 2); // 빨간색, 선 굵기 2
    line(img, Point(300, 10), Point(30, 300), Scalar(255, 0, 0), 3); // 파란색

    // 2. circle
    circle(img, Point(250, 250), 100, CV_RGB(0, 255, 0), 3); // 반지름이 100이고 중심점이 (250, 250)
    cv::Point center(400, 400);
    circle(img, center, 300, Scalar(0, 255, 255), 10);
    circle(img, Point(40, 40), 10, Scalar(255, 0, 255), -1); // 색이 채워진 원

    // 3. rectangle
    rectangle(img, Rect(10, 10, 200, 200), CV_RGB(255, 0, 0), 2); // (10, 10)에서 가로 200, 세로 200 크기의 사각형
    rectangle(img, Rect(Point(40, 40), Point(400, 400)), Scalar(255, 0, 0), 10); // (40, 40)와 (400, 400)를 지나는 사각형

    // 4. Ellipse
    // (100, 100)을 중심으로 장축 100, 단축 50 크기의 타원(기울기 0, 0~360 전체 타원)
    ellipse(img, Point(100, 100), Size(100, 50), 0, 0, 360, CV_RGB(255, 100, 100));
    // 기울어진 사각형 내부의 타원 그리기
    RotatedRect rRect = RotatedRect(Point2f(300, 300), Size2f(300, 100), 30);
    ellipse(img, rRect, CV_RGB(100, 100, 0));


    imshow("draw", img);
    waitKey(0);
    return 0;
}