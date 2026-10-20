
#include <iostream>
using namespace std;

class Point
{
public:
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    Point add(const Point &p) const
    {
        Point answer(0,0);
        answer.x = this -> x + p.x;
        answer.y = this -> y + p.y;
        return answer;
    }
};

int main()
{
    Point p1(1, 2);
    Point p2(3, 4);

    Point p3 = p1.add(p2);

    cout << p3.x << ", " << p3.y << endl;

    return 0;
}
