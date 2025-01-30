#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    /*
    1. mat class declaration and creation
    */

    Mat mtx(3, 3, CV_32F); // make 3x3 floating-point matrix
    Mat cmtx(10, 1, CV_64FC2);

    Mat img(Size(5, 3), CV_8UC3);

    Mat mtx2;
    mtx2 = Mat(3, 3, CV_32F);
    Mat cmtx2;
    cmtx2 = Mat(10, 1, CV_64FC1);

    Mat* mtx3 = new Mat(3, 3, CV_32F);
    delete mtx3;

    cout << "1. Mat declaration and creation" << endl;

    mtx.setTo(10);
    cout << mtx << endl;

    cout << "----------------------------" << endl;

    /*
    2. mat class operation
    */

    Mat m = Mat::ones(3, 3, CV_64F); // 3x3 matrix full with 1
    m = m * 3;

    double dm[3][3] = { {1,2,1}, {0,1,1}, {1,0,0} };
    Mat m2 = Mat(3, 3, CV_64F, dm); 
    // m2의 변화는 dm에 영향을 주지만 dm의 변화는 m2에 영향을 주지 않는다.

    cout << "2. Mat operation" << endl;
    cout << "m:\n" << m << endl;
    cout << "m2:\n" << m2 << endl;
    cout << "m+m2:\n" << m+m2 << endl;
    cout << "m*m2:\n" << m*m2 << endl;
    cout << "m.mul(m2):\n" << m.mul(m2) << endl;
    cout << "inverse of m2:\n"  << m2.inv() << endl;
    cout << "transpose of m2:\n" << m2.t() << endl;
    cout << "----------------------------" << endl;

    return 0;
}