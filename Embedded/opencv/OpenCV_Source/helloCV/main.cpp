#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "Hello OpenCV " << CV_VERSION << endl;

    Mat img;
    img = imread("C:\\Users\\STC\\Desktop\\chi\\Intel_AI_Edge\\Embedded\\opencv\\OpenCV_Source\\helloCV\\lenna.bmp");

    if (img.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    namedWindow("image");
    imshow("image", img);
    vector<int> params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(95);
    imwrite("C:\\Users\\STC\\Desktop\\chi\\Intel_AI_Edge\\Embedded\\opencv\\OpenCV_Source\\helloCV\\lenna1.jpg", img, params);

    waitKey();
    destroyWindow("image");

    return 0;
}
