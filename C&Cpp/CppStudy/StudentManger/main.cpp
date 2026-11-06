#include "StudentManger.h"
#include <iostream>
#include <sstream>
#include <optional>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;




int main()
{
#ifdef _WIN32
    // 控制台输入、输出统一使用 UTF-8，支持中文姓名和科目。
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
    vector<student> students;
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
