#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <iosfwd>
#include <vector>

class StudentManager {
public:
    static bool isValidScore(double score);
    bool addStudent(const Student& student);
    const Student* findStudent(const std::string& id) const;
    bool updateScore(const std::string& id, double score);
    bool removeStudent(const std::string& id);
    void displayAll(std::ostream& out) const;
    void displayStatistics(std::ostream& out) const;
    void sortByScore(bool ascending);
    static void displayStudent(const Student& student, std::ostream& out);

private:
    std::vector<Student> students_;
};

#endif
