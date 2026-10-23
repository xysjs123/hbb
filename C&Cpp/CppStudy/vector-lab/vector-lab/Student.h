#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student {
    std::string id;    // 字符串保留学号中的前导零
    std::string name;
    double score;
};

#endif
