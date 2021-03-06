from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([1, 0, 0], [-2, -2, -3], 'k')
plt.plot([1, 2, 2], [-2, -2, -3], 'k')
plt.plot([3, 1, 1], [-1, -1, -2], 'k')
plt.plot([3, 4, 4], [-1, -1, -2], 'k')
plt.plot([5, 3, 3], [0, 0, -1], 'k')
plt.plot([5, 8, 8], [0, 0, -1], 'k')
plt.plot([6, 7, 7], [-2, -2, -3], 'k')
plt.plot([8, 6, 6], [-1, -1, -2], 'k')
plt.plot([8, 11, 11], [-1, -1, -2], 'k')
plt.plot([9, 10, 10], [-3, -3, -4], 'k')
plt.plot([11, 9, 9], [-2, -2, -3], 'k')
plt.plot([11, 13, 13], [-2, -2, -3], 'k')
plt.plot([13, 12, 12], [-3, -3, -4], 'k')
plt.text(0, -3, "0", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -2, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, -3, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -1, "3", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -2, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, 0, "6", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -2, "7", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(7, -3, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(8, -1, "10", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(9, -3, "11", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(10, -4, "15", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(11, -2, "21", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(12, -4, "28", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(13, -3, "30", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('2')
plt.show()
