#include "setMouseCallback.h"

void onMouse(int event, int x, int y, int flags, void *param)
{
    cout << "x : " << x << " y : " << y << " flags : " << endl;
    switch (event) // switch문으로 event값에 따라 버튼 종류를 구분
    {
    case EVENT_LBUTTONDOWN:
        cout << "마우스 왼쪽버튼 누르기" << endl;
        break;
    case EVENT_RBUTTONDOWN:
        cout << "마우스 오른쪽버튼 누르기" << endl;
        break;
    case EVENT_RBUTTONUP:
        cout << "마우스 오른쪽버튼 떼기" << endl;
        break;
    case EVENT_LBUTTONDBLCLK:
        cout << "마우스 왼쪽버튼 더블클릭" << endl;
        break;
    case EVENT_MBUTTONDOWN:
        cout << "마우스 중간버튼 누르기" << endl; // 중간 버튼
        break;
    }
}