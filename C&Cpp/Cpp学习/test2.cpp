#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main ()
{
    int a,b;
    cout <<"请输入a：";
    cin >> a;

    cout <<"请输入b：";
    cin >> b;

    cout <<"交换前：" << endl;
    cout <<"a = " << a << endl;
    cout <<"b = " << b << endl;

    swap(a,b);

    cout <<"交换后：" << endl;
    cout <<"a = " << a << endl;
    cout <<"b = " << b << endl;

    return 0;
}