// 当初在小D学习整除的性质时，老师布置了这样一个问题，只有做出了这道题的人才能下课，问题的描述如下：

// 设 f(x) 为满足 ab|x 的 (a,b) 个数，输入 n ，求 ∑ni=1f(x)。

// 大家认为这题很简单，但是没有注意到 n 的范围，陷入了僵局。这个时候，聪明的小D，决定先人一步，提早把问题解决了好准备下课去吃饭。

// 输入数据
// 第一行一个数 T(1≤T≤5)
//  表示数据组数。
// 接下来 T
//  行，每行一个数 n(1≤n≤1011)
// ，表示问题中的变量 n
//  。

// 输出数据
// 共 T
//  行，每行一个数，为答案对 998244353
//  取模后的结果。

#include <iostream>
using namespace std;

int func(long x)
{
    int a;
    long count = 0;
    for(int i = 1;i <= x;i++)
    {
        if(x%i == 0)
        {
            for(int j = 1;j <= x;j++)
            {
                if(x%(i*j) == 0)
                {
                    count++;
                }
            }
        }
    }
    return count%998244353;
}

int fun(int num)
{
    int count = 0;
    for(int i = 1;i <= num;i++)
    {
        count +=func(i);
    }
    return count;
}

int main()
{
    int times;
    cin >> times;
    long num[5];
    for(int i = 0;i < times;i++)
    {
        cin >> num[i];
    }
    for(int i = 0;i < times;i++)
    {
        cout << fun(num[i]) <<endl;
    }
    return 0;
}