from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([1, 0, 0], [-13, -13, -14], 'k')
plt.plot([2, 1, 1], [-12, -12, -13], 'k')
plt.plot([3, 2, 2], [-11, -11, -12], 'k')
plt.plot([4, 3, 3], [-10, -10, -11], 'k')
plt.plot([5, 4, 4], [-9, -9, -10], 'k')
plt.plot([6, 5, 5], [-8, -8, -9], 'k')
plt.plot([7, 6, 6], [-7, -7, -8], 'k')
plt.plot([8, 7, 7], [-6, -6, -7], 'k')
plt.plot([9, 8, 8], [-5, -5, -6], 'k')
plt.plot([10, 9, 9], [-4, -4, -5], 'k')
plt.plot([11, 10, 10], [-3, -3, -4], 'k')
plt.plot([12, 11, 11], [-2, -2, -3], 'k')
plt.plot([13, 12, 12], [-1, -1, -2], 'k')
plt.plot([14, 13, 13], [0, 0, -1], 'k')
plt.text(0, -14, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -13, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, -12, "3", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -11, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -10, "5", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, -9, "6", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -8, "7", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(7, -7, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(8, -6, "9", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(9, -5, "10", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(10, -4, "11", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(11, -3, "12", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(12, -2, "13", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(13, -1, "14", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(14, 0, "15", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('1')
plt.show()