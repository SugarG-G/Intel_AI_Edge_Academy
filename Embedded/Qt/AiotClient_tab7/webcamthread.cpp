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

        cvtColor(frame, frameQt, COLOR_BGRA2RGB); //원본 이미지 수정을 하지 않기 위해 복사 및 전처리

        // imshow("카메라 영상보기", frame); // opencv클래스를 활용한 이미지 화면 띄우기

        qImage = QImage(frameQt.data, frameQt.cols, frameQt.rows, QImage::Format_RGB888); //qt에 이미지를 띄우기 위한 전처리

        //중심점 좌표 구하기
        int x = frameQt.cols / 2;
        int y = frameQt.rows / 2;
        //중심점 좌표 구하기

        //십자가 그리기
        // line(frameQt, Point((x-32),y), Point((x+32), y), Scalar(255,0,0), 2);
        // line(frameQt, Point(x,(y-32)), Point(x, (y+32)), Scalar(255,0,0), 2);
        //십자가 그리기

        //사각형 그리기
        rectangle(frameQt, Point((x-32),(y-32)), Point((x+32), (y+32)), Scalar(0,255,0), 2); //사각형을 그릴때는 좌즉 상단의 좌표와, 우측 하단의 좌표가 필요
        //사각형 그리기

        pCamView->setPixmap(QPixmap::fromImage(qImage));//qt를 활용한 gui 환경에서 이미지 띄우기

        Scalar meanRGB, meanHSV;
        Mat frameROI, hsvImage;

        frameROI = frame(Rect((x-32),(y-32), 64, 64)); // 사각형 영역의 이미지를 자름
        // meanRGB = mean(frameROI);

        cvtColor(frameROI, hsvImage, COLOR_BGR2HSV);
        meanHSV = mean(hsvImage); //hsv의 색상 평균 계산

        qDebug() << "meanHSV H : " << meanHSV[0] << " meanHSV S : " << meanHSV[1] << " meanHSV V : " << meanHSV[2];

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
    putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);     // 그림자 효과
    putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);// 작성 문자
}
void WebCamThread::snapShot()
{
    // imwrite(fname,frame);
    qImage.save(QString::fromStdString(fname), "JPG", 80);
}
