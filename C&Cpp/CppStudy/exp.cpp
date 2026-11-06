#include <iostream>
using namespace std;

void max(int a,int b)
{
    if(a > b)
    {
        cout << a <<endl;
    }else
    {
        cout << b <<endl;
    }
}

void max(double a,double b)
{
    if(a>b)
    {
        cout << a <<endl;
    }else{
        cout << b <<endl;
    }
}

void max(int a,int b,int c)
{
    if(a>b)
    {
        if(a>c)
        {
            cout << a <<endl;
        }else{
            cout << c <<endl;
        }
    }else
    {
        if(b>c)
        {
            cout << b <<endl;
        }else{
            cout << c <<endl;
        }
    }
}

int main()
{
    max(10,20);
    max(3.14,2.17);
    max(10,30,20);

    return 0;
}