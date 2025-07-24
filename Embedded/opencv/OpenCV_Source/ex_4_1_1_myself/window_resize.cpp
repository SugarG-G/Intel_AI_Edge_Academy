#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat image(300, 400, CV_8UC3, Scalar(128, 128, 128)); // 배경색상을 그레이색상으로
    string titile1 = "창 크기변경1 - AUTOSIZE";
    string titile2 = "창 크기변경2 - NORMAL";

    namedWindow(titile1, WINDOW_AUTOSIZE); // 윈도우 크기 변경 불가능함
    namedWindow(titile2, WINDOW_NORMAL);   // 윈도우 크기 변경 가능

    resizeWindow(titile1, 500, 200);
    resizeWindow(titile2, 500, 200);

    // 창의 위치를 이동
    moveWindow(titile1, 100, 200);
    moveWindow(titile2, 300, 200);

    imshow(titile1, image);
    imshow(titile2, image);

    waitKey();

    return 0;
}