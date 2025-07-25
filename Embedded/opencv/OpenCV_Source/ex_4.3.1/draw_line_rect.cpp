#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void onMouse(int, int, int, int, void *); // 마우스 콜백 함수

int main()
{
    Scalar white(255, 255, 255), yellow(0, 255, 255), blue(255, 0, 0);
    Scalar red = Scalar(0, 0, 255);
    Scalar green = Scalar(0, 255, 0);

    Mat image(400, 600, CV_8UC3, white);
    Point pt1(50, 130), pt2(200, 300), pt3(300, 150), pt4(400, 50);
    Rect rect(pt3, Size(200, 150));

    line(image, pt1, pt2, red);
    line(image, pt3, pt4, green, 2, LINE_AA);
    line(image, pt3, pt4, green, 3, LINE_8, 1);

    rectangle(image, rect, blue, 2);
    rectangle(image, rect, blue, FILLED, LINE_4, 1);
    rectangle(image, pt1, pt2, red, 3);

    imshow("직선 & 사각형", image);

    setMouseCallback("직선 & 사각형", onMouse, 0);

    waitKey(0);
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{
    cout << "x : " << x << " y : " << y << " flags : " << flags << endl; // 값 출력
    switch (event) // switch문으로 event값에 따라 버튼 종류를 구분
    {
    case EVENT_LBUTTONDOWN:
        cout << "마우스 왼쪽버튼 누르기" << endl;
        break;
    case EVENT_RBUTTONDOWN:
        cout << "마우스 오른쪽버튼 누르기" << endl;
        break;
    case EVENT_RBUTTONUP:
        cout << "마우스 오른쪽버튼 떼기" << endl;
        break;
    case EVENT_LBUTTONDBLCLK:
        cout << "마우스 왼쪽버튼 더블클릭" << endl;
        break;
    case EVENT_MBUTTONDOWN:
        cout << "마우스 중간버튼 누르기" << endl; // 중간 버튼
        break;
    }
}