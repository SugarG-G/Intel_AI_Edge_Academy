#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

struct userImageData {
        Mat imageMat;
        string title;
        string bar_name;
        userImageData(Mat m, string s1, string s2) : imageMat(m), title(s1), bar_name(s2) {}
};

// string title = "트랙바 이벤트", bar_name = "밝기값";
// Mat image;

void onChange(int value, void *userdata)
{
    userImageData *ud = (userImageData *)userdata;
    int add_value = value - 130;
    cout << "추가 화소값 " << add_value << endl;

    // Mat tmp = image + add_value;
    // imshow(title, tmp);
    Mat tmp = ud->imageMat + add_value;
    imshow(ud->title, tmp);
}

void onMouse(int event, int x, int y, int flags, void *param)
{
    userImageData *ud = (userImageData *)param;
    // if (event == EVENT_RBUTTONDOWN) {
    //     add(image, 10, image);
    //     setTrackbarPos(bar_name, title, image.at<uchar>(0));
    //     imshow(title, image);
    // }
    // else if (event == EVENT_LBUTTONDOWN) {
    //     subtract(image, 10, image);
    //     setTrackbarPos(bar_name, title, image.at<uchar>(0));
    //     imshow(title, image);
    // }
    if (event == EVENT_RBUTTONDOWN) {
        add(ud->imageMat, 10, ud->imageMat);
        setTrackbarPos(ud->bar_name, ud->title, ud->imageMat.at<uchar>(0));
        imshow(ud->title, ud->imageMat);
    }
    else if (event == EVENT_LBUTTONDOWN) {
        subtract(ud->imageMat, 10, ud->imageMat);
        setTrackbarPos(ud->bar_name, ud->title, ud->imageMat.at<uchar>(0));
        imshow(ud->title, ud->imageMat);
    }
}

int main()
{
    string title = "트랙바 이벤트";
    string bar_name = "밝기값";
    Mat image;

    userImageData ud(image, title, bar_name);
    int value = 130;
    image = Mat(300, 400, CV_8UC1, Scalar(130));

    namedWindow(title, WINDOW_AUTOSIZE);
    createTrackbar("밝기값", title, &value, 255, onChange, &ud);
    setMouseCallback(title, onMouse, &ud);

    imshow(title, image);
    waitKey(0);
    return 0;
}