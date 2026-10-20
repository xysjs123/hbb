#include <iostream>
#include <cstring>
using namespace std;

class Student
{
    private:
        char name[20];
        int age;
        double score;

    public:
        void print()
        {
            cout << "学生姓名：" << this -> name << endl;
            cout << "学生年龄：" << this -> age << endl;
            cout << "学生成绩：" << this -> score << endl;
        }

        void setStudent(char name[],int age,double score)
        {
            strcpy(this -> name,name);
            this -> age = age;
            this -> score = score;
        }

};

int main()
{
    Student s;
    s.setStudent("Tom",20,100);
    s.print();

    return 0;
}