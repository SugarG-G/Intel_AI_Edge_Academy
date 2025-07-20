#include "webcamthread.h"

WebCamThread::WebCamThread(QObject *parent)
    : QThread(parent)
{
    cnt = 0;
    camViewFlag = false;
}

void WebCamThread::run()
{
    VideoCapture  capture(0);
    if (!capture.isOpened())
    {
        cout << "카메라가 연결되지 않았습니다." << endl;
        exit(1);
    }
    while(camViewFlag) {

        capture.read(frame);

        put_string(frame, "Count: ", Point(10, 40), cnt);
        fname = "cam_" + to_string(cnt++);
        fname += ".jpg";
//        imshow("카메라 영상보기", frame);
        QImage qImage(frame.data, frame.cols, frame.rows, QImage::Format_BGR888);
        pCamView->setPixmap(QPixmap::fromImage(qImage));
/*        int key = waitKey(33);
        if(key == 's') //115
            imwrite(fname,frame);
        else if(key == 'b')  //98
        {
            cout << "key : " << key << endl;
            break;
        }
*/
    }
    capture.release();
//    QPixmap pix("initDisplay.png");
//    QPixmap->setPixmap(pix)
    pCamView->setPixmap(QPixmap(":Images/Images/initDisplay.png"));
}

// 문자열 출력 함수 - 그림자 효과
void WebCamThread::put_string(Mat &frame, string text, Point pt, int value)
{
    text += to_string(value);
    Point shade = pt + Point(2, 2);
    int font = FONT_HERSHEY_SIMPLEX;
    putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);     // 그림자 효
    putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);// 작성 문자
}
void WebCamThread::snapShot()
{
    imwrite(fname,frame);
}
