#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
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
            getline(cin,line);
            istringstream input(line);
            input >> name >> id;
        }

        void scoresReader(string& subject,double& score)
        {
            string line;
            getline(cin,line);
            istringstream input(line);
            input >> subject >> score;
        }

    public:
        void showMenu()
        {
            cout <<"=======学生成绩管理系统=======" << endl
                << "请输入序号以选择功能："  << endl
                << "1.添加学生" << endl
                << "2.浏览学生" << endl
                << "3.删除学生" << endl;
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

        void deleteStudent(const string& name,const string& id,vector<student> s)
        {
            string _name;
            string _id;
            cout << "请输入学生姓名或学号：";
            studentReader(_name,_id);


        }
};

int main()
{
    StudentManger s;
    s.showMenu();
    s.addstudent(students);
    s.browseStudent(students);
    return 0;
}