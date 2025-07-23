#ifndef WEBCAMTHREAD_H
#define WEBCAMTHREAD_H

#include <QThread>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QTimer>

using namespace cv;
using namespace std;
class WebCamThread : public QThread
{
    Q_OBJECT
    void run();
    int cnt;
    string fname;
    Mat frame;
    void put_string(Mat &frame, string text, Point pt, int value = -1);

    QImage qImage;
    Mat frameQt;

    QTimer *pQTimer;

    bool rgbClassifyFlag;

    QString strColor;
    QString strColorPre;

signals :
    void socketSendDataSig(QString);

public:
    WebCamThread(QObject *parent = nullptr);
    bool camViewFlag;
    QLabel *pCamView;
    void snapShot();
    void rgbTimerStart();
    void rgbTimerStop();

private slots:
    void rgbClassifySlot();
};

#endif // WEBCAMTHREAD_H
