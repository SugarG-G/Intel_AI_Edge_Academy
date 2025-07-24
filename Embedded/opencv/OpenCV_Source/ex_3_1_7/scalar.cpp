#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
    Mat         image(300, 500, CV_8UC3, Scalar(255, 255, 255));
    Point2f     center(250, 150), pts[4];
    Size2f      size(300, 100);
    RotatedRect rot_rect(center, size, 20);

    Rect bound_rect = rot_rect.boundingRect();

    Point2f topLeft(bound_rect.tl());
    Point2f topRight(bound_rect.x + bound_rect.width, bound_rect.y);
    Point2f bottomLeft(bound_rect.x, bound_rect.y + bound_rect.height);
    Point2f bottomRight(bound_rect.br());

    line(image, (topLeft + bottomLeft) / 2, (topRight + bottomRight) / 2, Scalar(150, 150, 0), 2);

    rectangle(image, bound_rect, Scalar(255, 255, 0), 1);
    circle(image, rot_rect.center, 1, Scalar(0), 2);

    rot_rect.points(pts);

    line(image, (pts[0] + pts[1]) / 2, (pts[2] + pts[3]) / 2, Scalar(255, 0, 255), 2);

    for (int i = 0; i < 4; i++) {
        circle(image, pts[i], 4, Scalar(0), 1 + i);
        cout << "pts[i]" << pts[i] << " ";
        line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2);
    }

    imshow("회전사각형", image);
    waitKey(0);
    return 0;
}