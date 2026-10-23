#include <iostream>
using namespace std;

class Canbe
{
    public:
        int green;
        int blue;
        int red;

        int Max()
        {
            return this -> blue > this -> red ? this -> blue : red;
        }

        int Min()
        {
            return this -> blue < this -> red ? this -> blue : red;
        }



        bool Can()
        {
            int e = Max() - Min();
            if(e % 3 == 0 &&
            !(this -> green == 0 && (this -> blue == 0 || this -> red == 0) && this -> blue + this -> red > 0))
            {
                return true;
            }else
            {
                return false;
            }
        }
};


int main()
{
    Canbe data[10000];
    int times;
    cin >> times;
    for(int i = 0;i < times;i++)
    {
        cin >> data[i].green >> data[i].blue >> data[i].red;
    }

    for(int i = 0;i<times;i++)
    {
        if(data[i].Can())
        {
            cout << "Yes" <<endl;
        }else cout << "No" <<endl;
    }

    return 0;
}