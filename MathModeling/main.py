
import numpy as np
import matplotlib.pyplot as plt

# 模拟时间：0 到 10
time = np.linspace(0, 10, 100)

# 假设某项指标随时间变化
value = 2 * time + 5 + np.random.normal(0, 2, 100)

# 绘制模拟数据
plt.scatter(time, value, label="Observed data")

# 绘制理论趋势线
plt.plot(time, 2 * time + 5, color="red", label="Trend line")

plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Mathematical Modeling Demo")
plt.legend()
plt.grid(True)

plt.show()
