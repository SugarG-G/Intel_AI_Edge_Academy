#include <iostream>
#include <vector>

using namespace std;

void vector_print(vector<int> &v);

int main(int argc, char *argv[])
{
    vector<int> v = {1,2,3};
    vector<int>::iterator it;
    cout << "Hello World!" << endl;

    v.push_back(4);
    v.push_back(5);

    vector_print(v);

    // for(int i = 0; i < v.size(); i++)
    // {
    //     cout <<"v : " << v[i] << " i: " << i << "\n";
    // }
    // cout << "v.size() : " << v.size() << endl;

    for(int i = v.size() - 1; i >= 0; i--)
    {
        v.erase(v.end() - 1);
    }
    cout << "erase\n";

    // for(int i = 0; i < v.size(); i++)
    // {
    //     cout << v[i];
    // }
    cout << "print";
    vector_print(v);
    cout << "exit";
    return 0;
}
void vector_print(vector<int> &v)
{
    vector<int>::iterator it;
    for(it = v.begin(); it != v.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
