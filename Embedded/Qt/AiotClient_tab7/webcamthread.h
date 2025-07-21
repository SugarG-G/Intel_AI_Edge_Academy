#ifndef WEBCAMTHREAD_H
#define WEBCAMTHREAD_H

#include <QThread>
#include <QLabel>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class WebCamThread : public QThread
{
    Q_OBJECT
    void run();
    int cnt;
    string fname;
    Mat frame;
    void put_string(Mat &frame, string text, Point pt, int value);

    QImage qImage;
    Mat frameQt;

public:
    WebCamThread(QObject *parent = nullptr);
    bool camViewFlag;
    QLabel *pCamView;
    void snapShot();
};

#endif // WEBCAMTHREAD_H
