# C++ vector 学生成绩管理实验

本项目使用 C++11 和 `std::vector<Student>`，通过控制台菜单完成学生成绩的添加、显示、查询、修改、删除、统计及升降序排序。不需要数据库或第三方 C++ 库。

## 文件职责

| 文件 | 职责 |
| --- | --- |
| Student.h | 定义学号、姓名、成绩构成的 Student 结构体 |
| StudentManager.h | 声明管理类，私有成员 vector<Student> 保存全部学生 |
| StudentManager.cpp | 实现增删改查、显示、统计和排序 |
| main.cpp | 程序入口、中文菜单、输入校验及功能调度 |
| CMakeLists.txt | 可选的跨平台 CMake 构建配置 |
| build.bat | Windows GCC 编译脚本，优先使用 PATH 中的 g++，其次使用本机 Dev-C++ |
| run.bat | 切换终端到 UTF-8 并运行，必要时先编译 |
| tests/test_cli.py | 可选的 Python 3 黑盒回归测试；程序本身不依赖 Python |
| TEST_REPORT.md | 实际编译和运行测试的结果 |

## 编译与运行

Windows 下双击 `build.bat` 编译，双击 `run.bat` 运行。已附本机编译得到的 `student_grades.exe`。

PowerShell 中也可以执行：

```powershell
.\build.bat
.\run.bat
```

使用已加入 PATH 的 GCC 手动编译：

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic -finput-charset=UTF-8 -fexec-charset=UTF-8 -static main.cpp StudentManager.cpp -o student_grades.exe
chcp 65001
.\student_grades.exe
```

本机 GCC 完整路径为 `E:\Dev-Cpp\TDM-GCC-64\bin\g++.exe`。未配置 PATH 时，在 PowerShell 中用 `& '完整路径'` 替代命令中的 `g++`。

Linux/macOS 下可去掉 `-static` 并将输出名改为 `student_grades`，使用 `./student_grades` 运行。源文件保存为 UTF-8。

可选 CMake 构建（需要已配置 C++ 编译器）：

```text
cmake -S . -B build
cmake --build build --config Release
```

单配置生成器的程序通常在 `build/` 中，Visual Studio 等多配置生成器通常在 `build/Release/` 中。

## vector 操作讲解

- `push_back(student)`：添加一条完整记录，vector 自动管理存储空间。
- `size()`：查询循环边界、显示人数、计算平均分。
- `at(i)`：按索引访问学生，学号查询时先保证索引小于 size()。
- `erase(it)`：根据学号定位后删除记录，立即返回避免使用失效迭代器。
- `empty()`：显示和统计时判断空容器，避免除零及读取第一个无效元素。
- 范围 for：遍历并显示学生、修改成绩、累计总分、寻找极值及显示并列学生。
- `begin()/end()` 配合 `std::stable_sort`：按成绩原地排序完整 Student，同分保持原相对顺序。后续显示沿用排序后的顺序。

查询返回的学生指针只在当前操作中读取；添加、删除或排序后不要继续使用此前取得的指针。

## 输入规则与使用说明

菜单为 1～8，排序方式为 1（升序）或 2（降序）。成绩允许小数，必须在 0～100 之间，拒绝非有限数、溢出、字母以及带多余字符的数字。

采用 `getline` 读取整行，再通过 `istringstream` 验证数字，避免非法字符破坏 cin 的状态。非法输入会提示并重试，输入流结束时安全退出。添加过程中遇到 EOF 不会保存半条记录。

学号和姓名不能为空，自动去除首尾空白，姓名支持中文及内部空格。学号按字符串精确匹配，保留前导零；`001` 与 `1` 是不同学号。重复学号会立即拒绝并回到菜单。

最高分和最低分显示所有并列学生。单人时，该学生同时为最高分和最低分。修改及删除直接操作 vector，下一次统计立即反映新数据。

Windows 程序启动时自动设置控制台输入和输出为 UTF-8，直接从 PowerShell 运行 exe 也能正确显示中文；退出时恢复原控制台编码。该设置通过 `_WIN32` 条件编译，仅影响 Windows 控制台，不改变成绩管理业务。

数据仅保存在本次运行的内存中，退出后清空。

## 执行测试

编译后，在项目目录运行：

```text
python tests/test_cli.py
```

也可以将待测 exe 的路径作为脚本参数。测试会真实启动程序，输入菜单操作并校验输出及正常退出。
