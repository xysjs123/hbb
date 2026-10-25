#include <iostream>
using namespace std;

class Student
{
    public:
        Student()
        {
            cout << "Student created." << endl;
        }

        ~Student()
        {
            cout << "Student destroyed." << endl;
        }
};

int main()
{
    Student* p = new Student();
    delete p;
    p = NULL;
    return 0;
}