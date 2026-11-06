#include <iostream>

// 将成绩限制在 0~100，按值传参，不修改调用者的变量。
int clampScore(int score)
{
    if (score < 0) return 0;
    if (score > 100) return 100;
    return score;
}

// 重载 1：普通变量优先匹配 int&，可以直接修改原变量。
int correctScore(int& score)
{
    std::cout << "[int&] Update original score\n";
    score = clampScore(score);
    return score;
}

// 重载 2：常量和临时值匹配 const int&，只返回修正结果。
int correctScore(const int& score)
{
    std::cout << "[const int&] Preview corrected score\n";
    return clampScore(score);
}

int main()
{
    int editable = 120;
    const int locked = -10;

    std::cout << "1. Mutable variable: before = " << editable << '\n';
    int result = correctScore(editable);
    std::cout << "result = " << result << ", after = " << editable << "\n\n";

    std::cout << "2. Const variable: before = " << locked << '\n';
    result = correctScore(locked);
    std::cout << "result = " << result << ", after = " << locked << "\n\n";

    std::cout << "3. Temporary value: 150\n";
    result = correctScore(150);
    std::cout << "result = " << result << "\n\n";

    // 同一个普通变量，也可以通过 const 引用以只读方式传入。
    int draft = 110;
    const int& readOnly = draft;
    std::cout << "4. Const reference: before = " << draft << '\n';
    result = correctScore(readOnly);
    std::cout << "result = " << result << ", after = " << draft << '\n';

    return 0;
}
