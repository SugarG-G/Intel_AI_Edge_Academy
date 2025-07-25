#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "트랙바 이벤트";
Mat image;

void onMouse(int event, int x, int y, int flags, void *param);
void onChange(int value, void *userdata)
{
    int add_value = value - 130;
    cout << "추가 화소값 " << add_value << endl;

    Mat tmp = image + add_value;
    imshow(title, tmp);
}
int main()
{
    int value = 130;
    image = Mat(300, 400, CV_8UC1, Scalar(120));

    namedWindow(title, WINDOW_AUTOSIZE);
    createTrackbar("밝기값", title, &value, 255, onChange);

    imshow(title, image);
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