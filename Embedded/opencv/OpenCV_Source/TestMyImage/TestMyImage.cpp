// TestMyImage.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고
// 종료됩니다.
//

#include "MyImage.h"
#include <iostream>
int main()
{
    CByteImage image1(640, 480);
    image1.SetConstValue(0);

    CByteImage image2(image1);
    CByteImage image3;
    image3 = image1;

    CByteImage image4(image1);
    CByteImage image5(image1);

    int nWidth   = image1.GetWidth();
    int nHeight  = image1.GetHeight();
    int nChannel = image1.GetChannel();

    double incX = 255.0 / nWidth;
    double incY = 255.0 / nHeight;

    int r, c;
    for (r = 0; r < nHeight; r++) {
        for (c = 0; c < nWidth; c++) {
            image2.GetAt(c, r) = (BYTE)(c * incX);
            image3.GetAt(c, r) = (BYTE)(r * incY);
        }
    }

    image1.SaveImage("OpenCV_Source\\TestMyImage\\Black.bmp");
    image2.SaveImage("OpenCV_Source\\TestMyImage\\GradationX.bmp");
    image3.SaveImage("OpenCV_Source\\TestMyImage\\GradationY.bmp");

    for (r = 0; r < nHeight; r++) {
        for (c = 0; c < nWidth; c++) {
            image4.GetAt(c, r) = image2.GetAt(c, r) / 2 + image3.GetAt(c, r) / 2;
            image5.GetAt(c, r) = ~(image2.GetAt(c, r) / 2 + image3.GetAt(c, r) / 2);
        }
    }

    image4.SaveImage("OpenCV_Source\\TestMyImage\\GradationXY.bmp");
    image5.SaveImage("OpenCV_Source\\TestMyImage\\GradationYX.bmp");

    return 0;
}