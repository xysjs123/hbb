#include <iostream>
using namespace std;
#define MAXSIZE 255

class land
{
    public:
        long land[MAXSIZE][MAXSIZE]{};

        void give_height(int row,int col,long e)
        {
            this -> land[row][col] = e;
        }

        bool Home(int row,int col)
        {
            long height = this -> land[row][col];
            if(height < this -> land[row-1][col] && 
                height < this -> land[row-1][col+1] &&
                height < this -> land[row][col+1] &&
                height < this -> land[row+1][col+1] &&
                height < this -> land[row+1][col] &&
                height < this -> land[row+1][col-1] &&
                height < this -> land[row][col-1] &&
                height < this -> land[row-1][col-1])
                {
                    return true;   
                }else return false;
        }
};

int main()
{
    land Land;
    int count = 0;
    int row,col;
    cin >> row >> col;
    long height;
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j < col;j++)
        {
            cin >> height;
            Land.give_height(i,j,height);
        }
    }

    for(int i = 1;i < row-1;i++)
    {
        for(int j = 1;j < col-1;j++)
        {
            if(Land.Home(i,j))
            {
                count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}