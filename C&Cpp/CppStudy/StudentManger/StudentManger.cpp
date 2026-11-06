#include "StudentManger.h"

#include <iostream>
#include <sstream>

using namespace std;

// 成功读到姓名、学号时返回 true；输入结束时返回 false。
bool StudentManger::studentReader(string& name, string& id)
{
    while (true)
    {
        string line;
        if (!getline(cin, line))
        {
            return false;
        }

        istringstream input(line);
        string extra;
        if ((input >> name >> id) && !(input >> extra))
        {
            return true;
        }
        cout << "请按“姓名 学号”格式重新输入：";
    }
}

bool StudentManger::studentAnalyzer(string& message)
{
    while (true)
    {
        string line;
        if (!getline(cin, line))
        {
            return false;
        }

        istringstream input(line);
        string extra;
        if ((input >> message) && !(input >> extra))
        {
            return true;
        }
        cout << "请输入一个姓名、学号或exit：";
    }
}

// 只有科目和数字成绩都解析成功，才允许保存学生。
bool StudentManger::scoresReader(string& subject, double& score)
{
    while (true)
    {
        string line;
        if (!getline(cin, line))
        {
            return false;
        }

        istringstream input(line);
        string extra;
        if ((input >> subject >> score) && !(input >> extra))
        {
            return true;
        }
        cout << "请按“科目 数字成绩”格式重新输入：";
    }
}

void StudentManger::showMenu()
        {
            cout << "请输入序号以选择功能："  << endl
                << "1.添加学生" << endl
                << "2.浏览学生" << endl
                << "3.删除学生" << endl
                << "4.退出系统" << endl;
        }

void StudentManger::addstudent(vector<student>& students)
{
    struct student s;
    string name;
    string id;
    string subject;
    double score = 0;

    cout << "请输入学生姓名学号：";
    if (!studentReader(name, id))
    {
        return;
    }
    cout << "请输入科目和对应的成绩：";
    if (!scoresReader(subject, score))
    {
        return;
    }

    s.name = name;
    s.id = id;
    s.score[subject] = score;
    students.push_back(s);
}

void StudentManger::browseStudent(const vector<student>& students)
{
    for(auto it = students.begin();it != students.end();it++)
    {
        cout << "姓名：" << it -> name << endl 
            << "学号：" << it -> id << endl;
            for(auto that = it -> score.begin();that != it -> score.end();that++)
            {
                cout << "科目：" << that -> first << " 成绩：" << that -> second << endl;
            }
    }
}

void StudentManger::deleteStudent(vector<student>& students)
{
    if (students.empty())
    {
        cout << "学生表为空" << endl;
        return;
    }

    while (true)
    {
        string message;
        cout << "(退出请输入exit)请输入想要删除学生的姓名或学号：";
        if (!studentAnalyzer(message))
        {
            return;
        }

        // 先判断退出，避免把 exit 当成姓名继续查找。
        if (message == "exit")
        {
            return;
        }

        for (auto it = students.begin(); it != students.end(); ++it)
        {
            if (message == it->name || message == it->id)
            {
                students.erase(it);
                cout << "删除成功" << endl;
                return;
            }
        }

        cout << "没有找到这个学生" << endl;
    }
}

optional<int> readInt(const string& prompt, int low, int high) {
    while (true) {
        cout << prompt;

        string line;
        if (!std::getline(std::cin, line)) {
            return std::nullopt;
        }

        std::istringstream input(line);
        int number = 0;
        char extra;
        bool valid = true;

        if (!(input >> number)) {
            // 没有读到合法整数，或整数超过 int 能表示的范围。
            valid = false;
        } else if (input >> extra) {
            // 读到整数后还能读出非空白字符，说明输入含多余内容。
            valid = false;
        } else if (number < low || number > high) {
            valid = false;
        }

        if (valid) {
            return number;
        }

        cout << "请输入 " << low << " 到 " << high << " 之间的整数。\n";
    }
}