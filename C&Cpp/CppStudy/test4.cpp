#include <iostream>
#include <cstring>
using namespace std;

class Student
{
    public:
        char name[20];
        int age;
        double score;

        void print()
        {
            cout << "学生姓名：" << name << endl;
            cout << "学生年龄：" << age << endl;
            cout << "学生成绩：" << score << endl;
        }
};

int main()
{
    Student s;
    strcpy(s.name,"Tom");
    s.age = 20;
    s.score = 100;
    s.print();

    return 0;
}