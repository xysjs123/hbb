#include "StudentManager.h"
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace {
// 直接启动 exe 时也使用 UTF-8；退出前恢复原控制台编码。
class ConsoleEncoding {
public:
    ConsoleEncoding() {
#ifdef _WIN32
        inputCodePage_ = GetConsoleCP();
        outputCodePage_ = GetConsoleOutputCP();
        if (inputCodePage_ != 0) SetConsoleCP(CP_UTF8);
        if (outputCodePage_ != 0) SetConsoleOutputCP(CP_UTF8);
#endif
    }
    ~ConsoleEncoding() {
        std::cout.flush();
#ifdef _WIN32
        if (inputCodePage_ != 0) SetConsoleCP(inputCodePage_);
        if (outputCodePage_ != 0) SetConsoleOutputCP(outputCodePage_);
#endif
    }

private:
#ifdef _WIN32
    UINT inputCodePage_ = 0;
    UINT outputCodePage_ = 0;
#endif
};

bool readText(const std::string& prompt, std::string& value) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return false;
        const std::size_t first = line.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            const std::size_t last = line.find_last_not_of(" \t\r\n");
            value = line.substr(first, last - first + 1);
            return true;
        }
        std::cout << "输入不能为空，请重新输入。\n";
    }
}

template <typename T>
bool readNumber(const std::string& prompt, T& value, T minimum, T maximum) {
    std::string line;
    while (readText(prompt, line)) {
        std::istringstream input(line);
        T parsed;
        // 整行解析，拒绝 90abc、1.5（菜单）等带尾部垃圾的输入。
        if (input >> parsed) {
            input >> std::ws;
            if (input.eof() && parsed >= minimum && parsed <= maximum) {
                value = parsed;
                return true;
            }
        }
        std::cout << "输入无效，请输入 " << minimum << "～" << maximum
                  << " 范围内的有效数字。\n";
    }
    return false;
}

void showMenu() {
    std::cout << "\n========== 学生成绩管理（vector 实验） ==========\n"
              << "1. 添加学生\n2. 显示全部学生\n3. 按学号查询学生\n"
              << "4. 修改学生成绩\n5. 删除学生\n6. 成绩统计\n"
              << "7. 成绩排序\n8. 退出程序\n";
}
}

int main() {
    ConsoleEncoding consoleEncoding;
    StudentManager manager;
    while (true) {
        showMenu();
        int choice;
        if (!readNumber<int>("请选择（1～8）：", choice, 1, 8)) break;
        if (choice == 8) {
            std::cout << "程序已退出。\n";
            return 0;
        }
        std::string id;
        double score;
        if (choice == 1) {
            Student student;
            if (!readText("请输入学号：", student.id)) break;
            if (manager.findStudent(student.id)) {
                std::cout << "添加失败：学号已存在。\n";
                continue;
            }
            if (!readText("请输入姓名：", student.name) ||
                !readNumber<double>("请输入成绩（0～100）：", student.score, 0.0, 100.0)) break;
            std::cout << (manager.addStudent(student) ? "添加成功。\n" : "添加失败。\n");
        } else if (choice == 2) {
            manager.displayAll(std::cout);
        } else if (choice == 3) {
            if (!readText("请输入要查询的学号：", id)) break;
            const Student* student = manager.findStudent(id);
            if (student) StudentManager::displayStudent(*student, std::cout);
            else std::cout << "未找到该学号的学生。\n";
        } else if (choice == 4) {
            if (!readText("请输入要修改的学号：", id)) break;
            if (!manager.findStudent(id)) {
                std::cout << "未找到该学号的学生。\n";
                continue;
            }
            if (!readNumber<double>("请输入新成绩（0～100）：", score, 0.0, 100.0)) break;
            std::cout << (manager.updateScore(id, score) ? "修改成功。\n" : "修改失败。\n");
        } else if (choice == 5) {
            if (!readText("请输入要删除的学号：", id)) break;
            std::cout << (manager.removeStudent(id) ? "删除成功。\n" : "未找到该学号的学生。\n");
        } else if (choice == 6) {
            manager.displayStatistics(std::cout);
        } else if (choice == 7) {
            int order;
            if (!readNumber<int>("请选择排序方式（1 升序，2 降序）：", order, 1, 2)) break;
            manager.sortByScore(order == 1);
            std::cout << (order == 1 ? "成绩升序列表：\n" : "成绩降序列表：\n");
            manager.displayAll(std::cout);
        }
    }
    // EOF 可在任意输入阶段安全退出，不提交未输入完整的学生记录。
    std::cout << "\n输入已结束，程序退出。\n";
    return 0;
}
