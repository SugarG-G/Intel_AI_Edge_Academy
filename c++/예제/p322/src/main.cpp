#include <iostream>

using namespace std;

class Rect;
bool equals(Rect r, Rect s);

// 예제 7-2
class RectManager
{
public:
    bool equals(Rect r, Rect s);
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
    friend bool RectManager::equals(Rect r, Rect s); // 예제 7-2
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

int main()
{
    Rect a(3, 4), b(4, 5);
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
    if (man.equals(a, b))
    {
        cout << "equal" << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }
}