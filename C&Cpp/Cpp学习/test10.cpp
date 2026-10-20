#include <iostream>
using namespace std;

class Point
{
public:
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    Point operator+(const Point &p) const
    {
        return Point(this -> x + p.x,this -> y + p.y);
    }
};

int main()
{
    Point p1(1, 2);
    Point p2(3, 4);

    Point p3 = p1 + p2;

    cout << p3.x << ", " << p3.y << endl;

    return 0;
}