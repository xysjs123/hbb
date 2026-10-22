#include <iostream>
using namespace std;
#define most_speed 260

class rules
{
    public:
        int start_point;
        int end_point;
        int speed;
    
        bool func(int point)
        {
            if(point >= this -> start_point && point <= this -> end_point)
            {
                return true;
            }else return false;
        }
        
        void funcadd(int Start,int End,int speed)
        {
            this -> start_point = Start;
            this -> end_point = End;
            this -> speed = speed;
        }
        
};

int main()
{
    int SpeedTestPoint;
    int rules_num;
    cin >> SpeedTestPoint >> rules_num;

    rules Rules[600];
    int Start,End,speed;
    for(int i = 0;i < rules_num;i++)
    {
        cin >> Start >> End >> speed;
        Rules[i].funcadd(Start,End,speed);
    }

    for(int i = 1;i <= SpeedTestPoint;i++)
    {
        int min_speed = 260;
        for(int j = 0;j < rules_num;j++)
        {
            if(Rules[j].func(i) && min_speed > Rules[j].speed)
            {
                min_speed = Rules[j].speed;
            }
        }

        cout<< min_speed <<' ';
    }

    return 0;
}