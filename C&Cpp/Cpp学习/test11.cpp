#include <iostream>
#include <cstring>
using namespace std;

class Student
{
    public:
        Student()
        {
            cout << "对象被创建了" << endl;
        }

        ~Student()
        {
            cout << "对象被销毁了" << endl;
        }
};

int main()
{
    Student s;
    cout << "对象使用中" << endl;

    return 0;
}