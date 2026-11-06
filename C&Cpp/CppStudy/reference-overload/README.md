# 引用参数与函数重载：迷你成绩修正器

只有一个 `main.cpp`，无需第三方库，适合刚学引用和重载时阅读。将成绩修正到 0～100：可写成绩直接更新，只读成绩只预览结果。程序内置四组数据，运行即可观察，不需要输入。

## 核心设计

```cpp
int correctScore(int& score);        // 修改原变量，并返回修正结果
int correctScore(const int& score);  // 不修改原变量，只返回修正结果
```

两个函数名字相同，但参数类型不同，构成函数重载。这里 `const` 修饰的是引用所指向的对象，因此 `int&` 和 `const int&` 是不同的参数类型。编译器根据调用处实参的类型和可绑定性选择函数。

| 调用 | 选中的重载 | 返回值 | 原变量最终值 |
| --- | --- | --- | --- |
| `correctScore(editable)`，普通变量初值 120 | `int&` | 100 | 100 |
| `correctScore(locked)`，常量初值 -10 | `const int&` | 0 | -10 |
| `correctScore(150)`，临时值 | `const int&` | 100 | 无原变量 |
| `correctScore(readOnly)`，引用指向初值 110 的 draft | `const int&` | 100 | draft 仍为 110 |

普通 `int` 左值能绑定到这两种引用，但这里优先选择 `int&`。常量和整数临时值不能绑定到 `int&`，因此选择 `const int&`。最后一例说明：即使底层对象可修改，通过 `const int&` 表达式传入时也选择只读重载。

`const int&` 禁止通过这个参数修改对象，并不代表底层对象永远不能改变。本例采用“可写就更新、只读就预览”的约定，是为了直观看到两种重载的效果；实际项目也可以把更新和预览命名为不同函数。

## 编译运行（PowerShell）

```powershell
Set-Location -LiteralPath 'E:\Documents\GitHub\hbb\C&Cpp\CppStudy\reference-overload'
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o reference_overload.exe
.\reference_overload.exe
```

源文件为 UTF-8，注释使用中文，控制台输出使用英文，避免终端编码影响阅读。每次调用都会输出命中的重载，以及结果和原变量的值。

## 阅读顺序

1. 看 `clampScore`：小于 0 返回 0，大于 100 返回 100，其余保持原值。
2. 对比两个 `correctScore`：只有 `int&` 版本向 `score` 赋值。
3. 看 `main` 的四次调用，对照上表判断重载和原变量是否变化。

## 容易混淆的规则

- `int&` 是原变量的别名，赋值会改变原变量，不是传入一份拷贝。
- 只改返回类型不能构成重载。
- `void f(int)` 与 `void f(const int)` 不是两个重载，按值参数的顶层 `const` 不区分函数签名。
- `void f(int)` 与 `void f(int&)` 可以声明为重载，但传入普通 `int` 变量时会产生歧义，不建议用它们练习重载选择。
- 本项目暂不引入 `int&&`（右值引用），先掌握普通引用与常量引用。

## 两个小练习

1. 将 `editable` 改为 85、0、100，确认合法成绩和边界值保持不变。
2. 将 `locked` 的 `const` 去掉，预测命中的重载和调用后的变量值，再运行验证。
