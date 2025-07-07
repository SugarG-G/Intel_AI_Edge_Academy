#include <iostream>

using namespace std;

class Rect;
// bool equals(Rect r, Rect s); //예제 7-1

// 예제 7-2
class RectManager
{
public:
    bool equals(Rect r, Rect s);
    void copy(Rect &dest, Rect &src); // 예제 7-3
};

class Rect
{
private:
    int width, height;

public:
    Rect(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
    // friend bool equals(Rect r, Rect s); // 예제 7-1
    // bool equals(Rect r, Rect s); // 테스트
    // friend bool RectManager::equals(Rect r, Rect s); // 예제 7-2
    friend RectManager; // 예제 7-3
};

// 예제 7-1
//  bool equals(Rect r, Rect s)
//  {
//      if (r.width == s.width && r.height == s.height)
//      {
//          return true;
//      }
//      else
//      {
//          return false;
//      }
//  }

// 예제 7-2
bool RectManager::equals(Rect r, Rect s)
{
    if (r.width == s.width && r.height == s.height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 예제 7-3
void RectManager::copy(Rect &dest, Rect &src)
{
    dest.width = src.width;
    dest.height = src.height;
}

int main()
{
    Rect a(3, 4), b(4, 5);
    // 예제 7-1
    // if (equals(a, b))
    // {
    //     cout << "equal" << endl;
    // }
    // else
    // {
    //     cout << "not equal" << endl;
    // }

    // 예제 7-2
    RectManager man;
    // if (man.equals(a, b))
    // {
    //     cout << "equal" << endl;
    // }
    // else
    // {
    //     cout << "not equal" << endl;
    // }

    // 예제 7-3
    man.copy(b, a);
    if (man.equals(a, b))
    {
        cout << "equal" << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }
}