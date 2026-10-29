#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> nums;
    for(int i = 10;i <= 50;i +=10)
    {
        nums.push_back(i);
    }
    cout << "nums' quality:" << nums.size() << endl;
    nums.pop_back();
    cout << "nums' quality:" << nums.size() << endl;
    cout << "last num:" << nums.back() << endl;
    if(nums.empty())
    {
        cout <<"empty" << endl;
    }else
    {
        cout << "Not empty" << endl;
    }
    return 0;
}