#include <iostream>
using namespace std;

int main()
{
    char name[10];
    double score_cpp;
    double score_shujujiegou;
    double score_math;
    double average;

    cout << "请输入学生姓名：";
    cin >> name;

    cout << "请输入C++成绩：";
    cin >> score_cpp;

    cout << "请输入数据结构成绩：";
    cin >> score_shujujiegou;

    cout << "请输入数学成绩：";
    cin >> score_math;

    average = (score_cpp + score_math + score_shujujiegou)/3;

    cout << name <<"的平均成绩是：" << average << endl;

    return 0;
}