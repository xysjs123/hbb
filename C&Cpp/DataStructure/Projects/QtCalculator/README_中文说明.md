# Qt Widgets 计算器接入说明

本文件夹提供的 `widget.h`、`widget.cpp` 和 `main.cpp` 对应 Qt Designer 中的
`widget.ui`。请把你已经做好的 `widget.ui` 复制到本文件夹，或在 Qt Creator
项目中把这三个文件添加到已有的项目。

## 需要的 objectName

数字：`btn0` 至 `btn9`；小数点：`btnDot`；四则运算：`btnAdd`、`btnSub`、
`btnMul`、`btnDiv`；其余按钮：`btnEqual`、`btnCE`、`btnC`、`btnBack`、
`btnNeg`、`btnPercent`、`btnSqrt`、`btnLParen`、`btnRParen`；显示标签：
`label_display`。

截图里的左括号按钮曾显示为 `btnLParen_2`。最推荐在 Designer 右侧的属性编辑器
中把它改为 `btnLParen`；本代码也会自动兼容旧名称，所以不改也能使用。

`verticalLayout` 仅负责界面排版，代码不需要单独连接它。

## 在 Qt Creator 中添加

1. 打开已有项目，右键项目选择“添加新文件”或“添加现有文件”。
2. 添加 `widget.h`、`widget.cpp`、`main.cpp`，并保留原有 `widget.ui`。
3. qmake 项目：将 `Calculator.pro` 的 `SOURCES`、`HEADERS`、`FORMS` 三段合并
   到你的 `.pro` 文件后，执行“运行 qmake”。
4. CMake 项目：将 `CMakeLists.txt` 中 `add_executable` 的文件列表合并到现有
   CMake 配置，然后重新配置项目。

不要创建或添加 `ui_widget.h`：Qt 会从 `widget.ui` 自动生成它。

## 功能与容错

- 支持多位整数、小数、四则运算和任意层小括号。
- `+ - * /` 不会连续输入；再次按运算符会替换上一个。
- 会显示：空表达式、括号不匹配、运算符后缺少值、数字格式错误、除零、负数开方、
  结果溢出等错误。
- `CE` 删除当前正在输入的数字；`C` 清空表达式；退格删除一个字符。
- `+/-` 改变当前数字符号，`%` 把当前数字转为该数字除以 100，`√x` 包裹当前数字。

表达式解析没有使用第三方库。实现采用递归下降：`表达式` 处理加减，`项` 处理乘除，
`一元表达式` 处理正负号，`基本项` 处理数值、括号和 `sqrt(...)`。
