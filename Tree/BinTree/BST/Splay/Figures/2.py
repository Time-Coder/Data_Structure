from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([0, 1, 1], [-2, -2, -3], 'k')
plt.plot([2, 0, 0], [-1, -1, -2], 'k')
plt.plot([2, 5, 5], [-1, -1, -2], 'k')
plt.plot([3, 4, 4], [-3, -3, -4], 'k')
plt.plot([5, 3, 3], [-2, -2, -3], 'k')
plt.plot([5, 7, 7], [-2, -2, -3], 'k')
plt.plot([7, 6, 6], [-3, -3, -4], 'k')
plt.plot([7, 8, 8], [-3, -3, -4], 'k')
plt.plot([9, 2, 2], [0, 0, -1], 'k')
plt.plot([9, 13, 13], [0, 0, -1], 'k')
plt.plot([11, 10, 10], [-2, -2, -3], 'k')
plt.plot([11, 12, 12], [-2, -2, -3], 'k')
plt.plot([13, 11, 11], [-1, -1, -2], 'k')
plt.plot([13, 14, 14], [-1, -1, -2], 'k')
plt.text(0, -2, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -3, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, -1, "3", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -3, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -4, "5", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, -2, "6", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -4, "7", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(7, -3, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(8, -4, "9", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(9, 0, "10", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(10, -3, "11", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(11, -2, "12", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(12, -3, "13", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(13, -1, "14", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(14, -2, "15", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('2')
plt.show()