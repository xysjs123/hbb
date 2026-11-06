#ifndef STUDENT_H
#define STUDENT_H

#include <map>
#include <string>

struct student
{
    std::string name;
    std::string id;
    std::map<std::string, double> score;
};

#endif