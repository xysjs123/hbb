#include "StudentManager.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ostream>

bool StudentManager::isValidScore(double score) {
    return std::isfinite(score) && score >= 0.0 && score <= 100.0;
}

bool StudentManager::addStudent(const Student& student) {
    if (student.id.empty() || student.name.empty() ||
        !isValidScore(student.score) || findStudent(student.id)) {
        return false;
    }
    students_.push_back(student); // vector 动态追加完整学生记录
    return true;
}

const Student* StudentManager::findStudent(const std::string& id) const {
    for (std::size_t i = 0; i < students_.size(); ++i) {
        if (students_.at(i).id == id) { // size() 控制边界，at() 安全访问
            return &students_.at(i);
        }
    }
    return nullptr;
}

bool StudentManager::updateScore(const std::string& id, double score) {
    if (!isValidScore(score)) {
        return false;
    }
    for (Student& student : students_) {
        if (student.id == id) {
            student.score = score;
            return true;
        }
    }
    return false;
}

bool StudentManager::removeStudent(const std::string& id) {
    for (auto it = students_.begin(); it != students_.end(); ++it) {
        if (it->id == id) {
            students_.erase(it); // 删除后迭代器可能失效，因此立即返回
            return true;
        }
    }
    return false;
}

void StudentManager::displayStudent(const Student& student, std::ostream& out) {
    out << "学号：" << student.id << " | 姓名：" << student.name
        << " | 成绩：" << std::fixed << std::setprecision(2) << student.score << '\n';
}

void StudentManager::displayAll(std::ostream& out) const {
    if (students_.empty()) {
        out << "暂无学生记录。\n";
        return;
    }
    out << "学生人数：" << students_.size() << '\n';
    for (const Student& student : students_) {
        displayStudent(student, out);
    }
}

void StudentManager::displayStatistics(std::ostream& out) const {
    if (students_.empty()) {
        out << "暂无学生记录，无法统计。\n";
        return;
    }
    double total = 0.0;
    double highest = students_.at(0).score;
    double lowest = highest;
    for (const Student& student : students_) {
        total += student.score;
        highest = std::max(highest, student.score);
        lowest = std::min(lowest, student.score);
    }
    out << "学生人数：" << students_.size() << '\n'
        << std::fixed << std::setprecision(2)
        << "平均分：" << total / students_.size() << '\n'
        << "最高分：" << highest << "，对应学生：\n";
    for (const Student& student : students_) {
        if (student.score == highest) displayStudent(student, out);
    }
    out << "最低分：" << lowest << "，对应学生：\n";
    for (const Student& student : students_) {
        if (student.score == lowest) displayStudent(student, out);
    }
}

void StudentManager::sortByScore(bool ascending) {
    // 排序整个 Student，保证学号、姓名、成绩对应；同分保持原相对顺序。
    std::stable_sort(students_.begin(), students_.end(),
        [ascending](const Student& a, const Student& b) {
            return ascending ? a.score < b.score : a.score > b.score;
        });
}
