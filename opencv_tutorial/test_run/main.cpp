#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 웹캠 열기
    cv::VideoCapture cap(0); // 기본 웹캠
    if (!cap.isOpened()) {
        std::cout << "웹캠 열기 실패" << std::endl;
        return -1;
    }

    cv::Mat frame, gray, edges;
    while (true) {
        cap >> frame; // 웹캠에서 프레임 받아오기
        if (frame.empty()) {
            std::cout << "웹캠에서 프레임 받아오기 실패" << std::endl;
            break;
        }

        // 프레임을 그레이스케일로 변환
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 엣지 추출 (Canny Edge Detection)
        cv::Canny(gray, edges, 100, 200);

        // 엣지 이미지를 화면에 표시
        cv::imshow("Edge Detection", edges);

        // 'q'를 눌러서 종료
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
