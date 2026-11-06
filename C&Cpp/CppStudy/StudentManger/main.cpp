#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <optional>
using namespace std;


struct student
{
    string name;
    string id;
    map <string,double> score;
};

vector<student> students;

class StudentManger
{
    private:
        void studentReader(string& name , string& id)
        {
            string line;
            if (!getline(cin, line))
            {
                return;
            }
            istringstream input(line);
            input >> name >> id;
        }

        void studentAnalyzer(string& message)
        {
            string line;
            if (!getline(cin, line))
            {
                return;
            }
            istringstream input(line);
            input >> message;
        }

        void scoresReader(string& subject,double& score)
        {
            string line;
            if (!getline(cin, line))
            {
                return;
            }
            istringstream input(line);
            input >> subject >> score;
        }

    public:
        void showMenu()
        {
                cout << "请输入序号以选择功能："  << endl
                    << "1.添加学生" << endl
                    << "2.浏览学生" << endl
                    << "3.删除学生" << endl
                    << "4.退出系统" << endl;
        }

        void addstudent(vector<student>& students)
        {
            struct student s;
            string name;
            string id;
            string subject;
            double score;

            cout << "请输入学生姓名学号：";
            studentReader(name,id);
            cout << "请输入科目和对应的成绩：";
            scoresReader(subject,score);

            s.name = name;
            s.id = id;
            s.score[subject] = score;
            students.push_back(s);
        }

        void browseStudent(const vector<student>& students)
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

        void deleteStudent(vector<student> s)
        {
            string message;
            cout << "(退出请输入exit)请输入想要删除学生的姓名或学号：";
            while(!s.empty() && message != "exit")
            {
                cout << "(退出请输入exit)请输入想要删除学生的姓名或学号：";
                studentAnalyzer(message);
                for(auto it = s.begin();it != s.end();it++)
                {
                    if(message == it -> name || message == it -> id)
                    {
                        s.erase(it);
                        return;
                    }
                }
                cout << "没有找到这个学生" << endl;
            }
            return;
        }
};

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

int main()
{
    StudentManger s;
    bool running = true;
    cout <<"=======学生成绩管理系统=======" << endl;
    while(running)
    {
        s.showMenu();
        optional<int> optionInput = readInt("选择> ",1,4);
        if (!optionInput.has_value()) {
            break;
        }

        int option = optionInput.value();

        switch(option)
        {
            case 1:
                s.addstudent(students);
                break;

            case 2:
                s.browseStudent(students);
                break;

            case 3:
                s.deleteStudent(students);
                break;
            case 4:
                running = false;
                cout << "程序已结束" << endl;
                break;
            default:
                cout << "输入错误" << endl;
                break;
        }
    }
    return 0;
}