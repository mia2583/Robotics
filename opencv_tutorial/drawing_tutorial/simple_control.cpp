#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int floags, void* userdata) {
    if(event == EVENT_LBUTTONDOWN) {
        circle((*(Mat*)userdata), Point(x, y), 2, CV_RGB(255, 0, 0), 3);
    } else if(event == EVENT_RBUTTONDOWN) {
        //
    } else if(event == EVENT_MBUTTONDOWN) {
        //
    } else if(event == EVENT_MOUSEMOVE) {
        // 
    }
    imshow("Mouse click", (*(Mat*)userdata));
}

void on_trackbar(int, void*) {
    //
}

int main() {
    Mat img = imread("../example.png");

    // 1. 글자 입력
    // char TestStr[100];
    // sprintf(TestStr, "total time: %lf sec", 0.001);
    // // (10, 250) 위치에 1두께로 글자 적기
    // putText(img, TestStr, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 1, 1);
    
    // 2. 컨투어 그리기
    cvtColor(img, img, COLOR_RGB2GRAY); 
    
    // 이진화 (Threshold 적용)
    // THRESH_BINARY_INV는 검은색에서 경계를 찾고 흰색을 배경으로 간주
    threshold(img, img, 128, 255, THRESH_BINARY_INV);

    // 컨투어 검출을 위한 변수
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    // 컨투어 검출
    findContours(img.clone(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 컨투어 그리기
    Mat imgContours = Mat::zeros(img.size(), CV_8UC3);
    drawContours(imgContours, contours, -1, Scalar(0, 255, 0), 2);
    cout << contours.size() << endl;

    // 3. 마우스 이벤트
    namedWindow("Mouse click", 1);

    setMouseCallback("Mouse click", CallBackFunc, &imgContours);

    // 4. Trackbar control
    Mat edges;
    VideoCapture cap = VideoCapture(0);

    if(!cap.isOpened()) return -1;

    int g_slider = 0;
    int g_slider_max = 255;
    namedWindow("edges", 1);

    createTrackbar("TrackbarName", "edges", &g_slider, g_slider_max, on_trackbar);


    // 결과 출력
    imshow("Text", img);
    imshow("Contours", imgContours);
    imshow("Mouse click", imgContours);
    for(;;) {
        Mat frame;
        cap >> frame;
        cvtColor(frame, edges, COLOR_RGB2GRAY);
        GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
        Canny(edges, edges, g_slider, 30, 3);
        imshow("edges", edges);
        if (waitKey(30) >= 0) break;
    }
    

    waitKey(0);
    
    return 0;
}