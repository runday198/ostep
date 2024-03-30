import subprocess
import matplotlib.pyplot as plt
import numpy as np

res_list = []
for i in range(1, 1001):
    trial_list = []
    print(i)
    for j in range(0, 30):
        result = subprocess.run(
            ["python3", "lottery.py", "-l", f"{i}:100,{i}:100", "-s", str(j), "-c"],
            capture_output=True,
            text=True,
        )

        result_lines = [
            line for line in result.stdout.splitlines() if line.startswith("-->")
        ]
        num1 = result_lines[0].split()[-1]
        num2 = result_lines[1].split()[-1]

        trial_list.append((int(num1) / int(num2)) * 100)

    total = 0
    for i in trial_list:
        total += i

    res_list.append(total / 3000)

x = np.arange(1, 1001)
y = np.array(res_list)

plt.plot(x, y)
plt.xlabel("Job Length")
plt.ylabel("Fairness")
plt.savefig("my_plot.png")
plt.show(block=True)

# python3 lottery.py -l 100:100,100:100 -q 10 -c
