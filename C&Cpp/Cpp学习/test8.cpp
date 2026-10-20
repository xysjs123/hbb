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

        Student(char name[],int age,double score)
            : age(age),score(score)
        {
            strcpy(this -> name,name);
        }

        Student()
        {
            this -> name[0] = '\0';
            this -> age = 0;
            this -> score = 0;
        }
};

int main()
{
    Student s1("Tom",20,100);
    Student s2;

    s1.print();
    s2.print();

    return 0;
}