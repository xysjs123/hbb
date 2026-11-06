#ifndef STUDENTMANGER_H
#define STUDENTMANGER_H

#include "Student.h"
#include <string>
#include <vector>
#include <optional>

class StudentManger
{
    private:
        bool studentReader(std::string& name , std::string& id);

        bool studentAnalyzer(std::string& message);

        bool scoresReader(std::string& subject,double& score);

    public:
        void showMenu();

        void addstudent(std::vector<student>& students);

        void browseStudent(const std::vector<student>& students);

        void deleteStudent(std::vector<student>& students);

};

std::optional<int> readInt(const std::string& prompt, int low, int high);

#endif