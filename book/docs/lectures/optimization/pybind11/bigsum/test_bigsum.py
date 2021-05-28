import matplotlib.pyplot as plt
import numpy as np
import time
from code import bigsum
from numba import njit


labels = [
    "pybind11",
    "pure python",
    "python sum",
    "numpy",
    "numba (with compilation)",
    "numba (after compilation)",
]


@njit
def numba_sum(n):
    s = 0
    for i in range(n):
        s += i
    return s


def run(N):
    t0 = time.perf_counter()
    # Pybind11
    s1 = bigsum.sum(N)

    t1 = time.perf_counter()
    # Pure python
    s2 = 0
    for i in range(N):
        s2 += i

    t2 = time.perf_counter()

    # python sum
    s3 = sum(range(N))

    t3 = time.perf_counter()

    # numpy sum
    s4 = np.sum(np.arange(N))

    t4 = time.perf_counter()

    s5 = numba_sum(N)

    t5 = time.perf_counter()

    s6 = numba_sum(N)

    t6 = time.perf_counter()

    assert s1 == s2 == s3 == s4 == s5 == s6, f"{s1}, {s2}, {s3}, {s4}, {s5}, {s6}"

    return dict(zip(labels, [t1 - t0, t2 - t1, t3 - t2, t4 - t3, t5 - t4, t6 - t5]))


if __name__ == "__main__":

    Ns = [1_000_000, 5_000_000, 10_000_000, 50_000_000, 100_000_000]
    timings = {k: [] for k in labels}

    for N in Ns:
        res = run(N)
        for label, timing in res.items():
            timings[label].append(timing)

    x = np.arange(len(Ns))
    width = 0.15
    fig, ax = plt.subplots(figsize=(12, 10))

    for i, (label, timing) in enumerate(timings.items(), start=-2):
        ax.bar(x + i * width, timing, width, label=label)

    ax.set_yscale("log")
    ax.legend(
        loc="upper center",
        bbox_to_anchor=(0.5, 1.05),
        ncol=3,
        fancybox=True,
        shadow=True,
    )
    ax.set_xticks(x)
    ax.set_xticklabels([f"{N:.1e}" for N in Ns])
    ax.set_ylabel("Time (seconds)")
    ax.set_xlabel("N")
    plt.show()

    # for label, t in zip(labels, timings):
    #     print(f"{label}: {t:.2e} seconds")
