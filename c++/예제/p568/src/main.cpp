#include <iostream>
#include <string>

using namespace std;

class Book
{
    string title;
    string press;
    string author;

public:
    Book(string title = "", string press = "", string author = "")
    {
        this->title = title;
        this->author = author;
        this->press = press;
    }
    friend ostream &operator<<(ostream &stream, Book b);
};

ostream &operator<<(ostream &stream, const Book b)
{
    stream << b.title << "," << b.press << "," << b.author;
    return stream;
}

int main()
{
    Book book("소유냐 존재냐", "한국출판사", "에리히프롬");
    cout << book;
}