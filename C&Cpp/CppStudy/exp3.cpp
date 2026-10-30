#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> nums;

    for(int i = 10;i <= 50;i+10)
    {
        nums.push_back(i);
    }
    auto it = nums.begin();
    nums.insert(it + 2,25);
    it = nums.begin();
    nums.erase(it + 4);
    for(int num : nums)
    {
        cout << num << endl;
    }

    return 0;
}