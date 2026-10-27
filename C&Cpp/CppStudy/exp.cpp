#include <iostream>
using namespace std;

class Student
{
    public:

        int* score;

        Student(int s) : score(new int(s)) {}

        ~Student()
        {
            delete score;
            score = nullptr;
        }

        Student(const Student& other) : score(new int(*other.score)) {}

        Student& operator=(const Student& other)
        {
            if(this == &other)
            {
                return *this;
            }
            
            delete this -> score;
            this -> score = new int(*other.score);
            return *this;
        }     
};

int main()
{
    Student s1(90);
    Student s2(80);
    Student s3(70);
    s3 = s2 = s1;


    cout << *s1.score << endl;
    cout << *s2.score << endl;
    cout << *s3.score << endl;
    return 0;
}