import matplotlib.pyplot as plt

def read_csv(filename):
    xs = []
    ys = []
    with open(filename, "r") as f:
        next(f)  # 跳过 header：n,time
        for line in f:
            line = line.strip()
            if not line:
                continue
            n, t = line.split(",")
            xs.append(int(n))
            ys.append(float(t))
    return xs, ys


def main():
    # 读不同算法的结果
    x1, y1 = read_csv("on1.csv")   # O(n)
    x2, y2 = read_csv("on2.csv")   # O(n^2)
    x3, y3 = read_csv("on3.csv")   # O(n^3)

    # 画图
    plt.plot(x1, y1, marker='o', label="O(n)")
    plt.plot(x2, y2, marker='o', label="O(n^2)")
    plt.plot(x3, y3, marker='o', label="O(n^3)")

    # 坐标 & 样式
    plt.xlabel("n (input size)")
    plt.ylabel("time (seconds)")
    plt.yscale("log")        # 关键：对数纵轴
    plt.grid(True)
    plt.legend()
    plt.title("Maximum Subarray: Time Complexity Comparison")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
