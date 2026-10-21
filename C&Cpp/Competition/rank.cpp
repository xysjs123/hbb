//f1fjt5f 嘲笑 Gusare 不会出题。 现在请你来写写这道 Gusare 出的简单题。

// enjoy competitive programming 是 Gusare 的美好梦想。 她希望能有更多人能体会到 CP 的魅力，并且乐在其中，不论男女。

// ACM 赛制下的排行规则如下：

// 通过题目数量多的排在前面
// 过题数同样多的情况下，罚时小的排在前面
// 除此之外，Gusare 还规定：

// 所以对于过题数和罚时都相同的学生，按照学号的数字大小从小到大进行排序。
// 现在，给你一份有 n个学生的列表，第 i 位学生对应学号 idi ，过题数量 numi ，以及罚时 penaltyi 请你按照上面的 3 条规则对列表进行排名并输出。

// 输入数据 共 n+1 行
// 第一行为一个正整数 n(1≤n≤100)

// 第二行到 n+1 行，每行有 3 个用空格隔开的非负整数，第 i−1 行的 3 个数字分别是 idi,numi,penaltyi

// 0≤idi≤100 且 保证每个学生的学号互不相同
// 0≤numi≤6
// 0≤penaltyi≤1000
// 输出数据 共 n 行
// 每行是 3 个用空格隔开的数字
// 分别表示按规则排序后，排在第 i 位的同学的学号 id ，过题数 num 以及罚时 penalty

#include <iostream>
#define MAXSIZE 101
using namespace std;

class Student
{
public:
    int id;
    int num;
    int penalty;
};


void rankStudent(Student S[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int best = i;

        for (int j = i + 1; j < n; j++)
        {
            if (S[j].num > S[best].num ||
                (S[j].num == S[best].num &&
                 S[j].penalty < S[best].penalty) ||
                (S[j].num == S[best].num &&
                 S[j].penalty == S[best].penalty &&
                 S[j].id < S[best].id))
            {
                best = j;
            }
        }

        Student temp = S[i];
        S[i] = S[best];
        S[best] = temp;
    }
}


int main()
{
    int num;
    cin >> num;

    if (num < 0 || num > MAXSIZE)
        return 1;

    Student S[MAXSIZE];

    for (int i = 0; i < num; i++)
    {
        cin >> S[i].id >> S[i].num >> S[i].penalty;
    }

    rankStudent(S, num);

    for (int i = 0; i < num; i++)
    {
        cout << S[i].id << ' '
             << S[i].num << ' '
             << S[i].penalty << endl;
    }

    return 0;
}
