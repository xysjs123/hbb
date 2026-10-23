"""黑盒测试：启动真实菜单程序，校验输出、统计值和排序对应关系。"""
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
EXE = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else ROOT / "student_grades.exe"


def run(lines):
    result = subprocess.run([str(EXE)], input="\n".join(lines).encode("utf-8"),
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5)
    assert result.returncode == 0, result.stderr.decode("utf-8", errors="replace")
    return result.stdout.decode("utf-8")


def row(id_, name, score):
    return f"学号：{id_} | 姓名：{name} | 成绩：{score:.2f}"


def check_add_display():
    out = run(["1", "001", "张三", "80", "1", "002", "李 四", "90.5", "2", "8", ""])
    assert out.count("添加成功。") == 2
    assert "学生人数：2" in out
    assert row("001", "张三", 80) in out and row("002", "李 四", 90.5) in out


def check_duplicate():
    out = run(["1", "001", "张三", "80", "1", "001", "2", "8", ""])
    assert "学号已存在" in out and "学生人数：1" in out
    assert out.count("添加成功。") == 1


def check_scores():
    out = run(["1", "001", "张三", "-1", "101", "abc", "90abc", "nan", "inf", "1e309", "0",
               "1", "002", "李四", "100", "6", "8", ""])
    assert out.count("输入无效") == 7
    assert "平均分：50.00" in out and "最高分：100.00" in out and "最低分：0.00" in out


def check_query():
    out = run(["1", "001", "张三", "80", "3", "001", "3", "999", "8", ""])
    assert row("001", "张三", 80) in out and "未找到该学号的学生" in out


def check_update():
    out = run(["1", "001", "张三", "80", "1", "002", "李四", "60", "4", "001", "101", "100",
               "6", "4", "999", "8", ""])
    assert "修改成功" in out and "输入无效" in out and "未找到该学号的学生" in out
    assert "学生人数：2" in out and "平均分：80.00" in out
    assert "最高分：100.00" in out and "最低分：60.00" in out
    assert row("001", "张三", 100) in out


def check_delete():
    out = run(["1", "001", "张三", "80", "1", "002", "李四", "60", "5", "001", "6",
               "5", "001", "5", "002", "6", "8", ""])
    assert out.count("删除成功") == 2 and "未找到该学号的学生" in out
    assert "学生人数：1" in out and "平均分：60.00" in out
    assert "最高分：60.00" in out and "最低分：60.00" in out and "无法统计" in out


def check_sort():
    out = run(["1", "001", "张三", "80", "1", "002", "李四", "60", "1", "003", "王五", "100",
               "1", "004", "赵六", "80", "7", "1", "7", "2", "8", ""])
    asc = out.split("成绩升序列表：")[1].split("==========")[0]
    desc = out.split("成绩降序列表：")[1].split("==========")[0]
    expected = [row("002", "李四", 60), row("001", "张三", 80),
                row("004", "赵六", 80), row("003", "王五", 100)]
    assert [asc.index(r) for r in expected] == sorted(asc.index(r) for r in expected)
    expected = [expected[3], expected[1], expected[2], expected[0]]
    assert [desc.index(r) for r in expected] == sorted(desc.index(r) for r in expected)


def check_empty():
    out = run(["2", "3", "001", "4", "001", "5", "001", "6", "7", "1", "7", "2", "8", ""])
    assert out.count("未找到该学号的学生") == 3
    assert "无法统计" in out and out.count("暂无学生记录") == 4


def check_recovery():
    out = run(["abc", "1.5", "2junk", "0", "9", "", "1", " ", "001", " ", "张三", "80",
               "7", "x", "3", "1", "2", "8", ""])
    assert out.count("输入无效") == 7 and out.count("输入不能为空") == 3
    assert "添加成功" in out and row("001", "张三", 80) in out and "程序已退出" in out


def check_ties_and_eof():
    out = run(["1", "001", "张三", "90", "1", "002", "李四", "90", "6", "8", ""])
    assert out.count(row("001", "张三", 90)) == 2
    assert out.count(row("002", "李四", 90)) == 2
    for lines in ([], ["1", ""], ["1", "001", ""], ["1", "001", "张三", ""],
                  ["3", ""], ["4", ""], ["5", ""], ["7", ""],
                  ["1", "001", "张三", "80", "4", "001", ""]):
        out = run(lines)
        assert "输入已结束，程序退出" in out


if __name__ == "__main__":
    cases = [check_add_display, check_duplicate, check_scores, check_query,
             check_update, check_delete, check_sort, check_empty, check_recovery,
             check_ties_and_eof]
    for case in cases:
        case()
        print("PASS", case.__name__)
    print(f"All {len(cases)} test groups passed.")
