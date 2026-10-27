#include <iostream>
#include <string>
using namespace std;

class Animal
{
    public:
        string name;

        void eat()
        {
            cout << name <<"正在吃东西" << endl;
        }

        virtual void speak()
        {
            cout << "动物发出声音" << endl;
        }
};

class Dog : public Animal
{
    public:
        void bark()
        {
            cout <<"狗正在汪汪叫" << endl;
        }

        void speak() override
        {
            cout << "汪汪" << endl;
        }
};

class Cat : public Animal
{
    public:
        void speak() override
        {
            cout << "喵喵" << endl;
        }
};

int main()
{
    Animal* p;
    Dog dog;
    Cat cat;

    p = &dog;
    p -> speak();

    p = &cat;
    p -> speak();
    return 0;

}