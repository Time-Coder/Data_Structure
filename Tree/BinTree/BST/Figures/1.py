from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([1, 0, 0], [-2, -2, -3], 'k')
plt.plot([2, 1, 1], [-1, -1, -2], 'k')
plt.plot([2, 3, 3], [-1, -1, -2], 'k')
plt.plot([3, 4, 4], [-2, -2, -3], 'k')
plt.plot([5, 2, 2], [0, 0, -1], 'k')
plt.plot([5, 6, 6], [0, 0, -1], 'k')
plt.text(0, -3, "0", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -2, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, -1, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -2, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -3, "5", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, 0, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -1, "9", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('1')
plt.show()
