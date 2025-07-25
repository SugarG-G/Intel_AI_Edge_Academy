#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "이벤트 그리기";
Mat image;

void onMouse(int event, int x, int y, int flags, void *param)
{
    static Point pt(-1, -1);

    if (event == EVENT_LBUTTONDOWN) {
        if (pt.x < 0) {
            pt = Point(x, y);
        }
        else {
            rectangle(image, pt, Point(x, y), Scalar(255, 0, 0), 2);
            imshow(title, image);
            pt = Point(-1, -1);
        }
    }
    else if (event == EVENT_RBUTTONDOWN) {
        if (pt.x < 0) {
            pt = Point(x, y);
        }
        else {
            Point2d pt2 = pt - Point(x, y);
            int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y); // 두 좌표간 거리
            circle(image, pt, radius, Scalar(128, 128, 128), 2);

            imshow(title, image);
            pt = Point(-1, -1);
        }
    }
    else if (event == EVENT_MBUTTONDOWN) {
        if (pt.x < 0) {
            pt = Point(x, y);
        }
        else {
            Point2d pt2 = pt - Point(x, y);
            int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y); // 두 좌표간 거리
            circle(image, pt, radius, Scalar(128, 128, 128), 2);

            imshow(title, image);
            pt = Point(-1, -1);
        }
    }
}
int main()
{
    image = Mat(300, 500, CV_8UC3, Scalar(255, 255, 255));
    imshow(title, image);
    setMouseCallback(title, onMouse, 0);
    waitKey(0);
    vector<int> params_jpg, params_png, params_bmp;
    params_jpg.push_back(IMWRITE_JPEG_QUALITY);
    params_jpg.push_back(50);
    params_png.push_back(IMWRITE_PNG_COMPRESSION);
    params_png.push_back(9);
    params_bmp.push_back(IMWRITE_PXM_BINARY);
    params_bmp.push_back(0);
    imwrite("OpenCV_Source\\ex_4.3.5\\event_draw.cppevent_draw.jpg", image);
    imwrite("OpenCV_Source\\ex_4.3.5\\event_draw.cppevent_draw2.jpg", image, params_jpg);
    imwrite("OpenCV_Source\\ex_4.3.5\\event_draw.cppevent_darw.png", image);
    imwrite("OpenCV_Source\\ex_4.3.5\\event_draw.cppevent_draw2.png", image, params_png);
    imwrite("OpenCV_Source\\ex_4.3.5\\event_draw.cppevent_draw.bmp", image);
    imwrite("OpenCV_Source\\ex_4.3.5\\event_draw.cppevent_draw2.bmp", image, params_bmp);
    return 0;
}