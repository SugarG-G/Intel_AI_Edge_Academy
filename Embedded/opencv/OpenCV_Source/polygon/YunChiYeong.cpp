#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct colorinfoStruct {
        String name;
        Scalar color;
        int count;
};

void setLabel(Mat &img, const vector<Point> &pts, const String &label)
{
    Rect rc = boundingRect(pts);
    // rectangle(img, rc, Scalar(0, 0, 255), 1);
    putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
}

void setColorLabel(Mat &img, const vector<Point> &pts, colorinfoStruct *colorInfo)
{
	Mat mask = Mat::zeros(img.size(), CV_8UC1);
    vector<vector<Point>> maskCnt{ pts };
    drawContours(mask, maskCnt, 0, Scalar(255), FILLED);

    Scalar meanBGR = mean(img, mask);

    int bestIdx = 0;
    double minDist = DBL_MAX;
    for (int i = 0; i < 4; i++) {
        Scalar ref = colorInfo[i].color;
        double db = meanBGR[0] - ref[0];
        double dg = meanBGR[1] - ref[1];
        double dr = meanBGR[2] - ref[2];
        double dist = db*db + dg*dg + dr*dr;
        if (dist < minDist) {
            minDist = dist;
            bestIdx = i;
        }
    }

    colorInfo[bestIdx].count++;

	vector<vector<Point>> drawCnt{ pts };
    drawContours(img, drawCnt, 0, Scalar(128,128,128), 3);

    Moments mu = moments(pts);
    int cx = int(mu.m10 / mu.m00);
    int cy = int(mu.m01 / mu.m00);

    String label = colorInfo[bestIdx].name;
    int baseLine = 0;
    double fontScale = 1.0;
    int thickness = 1;
    Size ts = getTextSize(label, FONT_HERSHEY_PLAIN, fontScale, thickness, &baseLine);

    Scalar col = colorInfo[bestIdx].color;
    Scalar compCol(255 - col[0], 255 - col[1], 255 - col[2]);

    Point boxTl(cx - ts.width/2, cy - ts.height/2 - baseLine);
    Rect box(boxTl.x, boxTl.y, ts.width, ts.height + baseLine);

    rectangle(img, box, compCol, FILLED);

    Point textOrg(boxTl.x, boxTl.y + ts.height);
    // Point textOrg(cx, cy);
    putText(img, label, textOrg, FONT_HERSHEY_PLAIN, fontScale, col, thickness);
}


int main(int argc, char *argv[])
{
    colorinfoStruct colorInfo[4] = {
        {"blue", Scalar(255, 0, 0), 0}, {"green", Scalar(0, 255, 0), 0}, {"red", Scalar(0, 0, 255), 0}, {"none", Scalar(128, 128, 128), 0}};

    Mat img = imread("../../640x480_shape.png", IMREAD_COLOR);

    if (img.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    Mat bin;
    threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (vector<Point> pts : contours) {
        if (contourArea(pts) < 400)
            continue;

        vector<Point> approx;
        approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

        int vtc = (int)approx.size();

        if (vtc == 3)
            setLabel(img, pts, "triangle");
        else if (vtc == 4)
            setLabel(img, pts, "rectangle");
        else if (vtc == 5)
            setLabel(img, pts, "pentagon");
        else if (vtc == 6)
            setLabel(img, pts, "hexagon");
        else {
            double len = arcLength(pts, true);
            double area = contourArea(pts);
            double ratio = 4. * CV_PI * area / (len * len);

            if (ratio > 0.85) {
                setLabel(img, pts, "circle");
            }
        }
        setColorLabel(img, pts, colorInfo);
    }
    putText(img, "YUN CY", Point(10, 40), FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 0), 4);
    for (int i = 0; i < sizeof(colorInfo) / sizeof(colorInfo[0]); i++) {
        String strText = colorInfo[i].name + " " + to_string(colorInfo[i].count);
        putText(img, strText, Point(20, 60 + (15 * i)), FONT_HERSHEY_PLAIN, 1, colorInfo[i].color, 1);
    }
	imwrite("../../chiyeong.png",img);
    imshow("img", img);

    waitKey();
    return 0;
}