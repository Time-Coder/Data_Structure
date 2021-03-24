from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([0, 1, 1], [0, 0, -1], 'k')
plt.plot([1, 14, 14], [-1, -1, -2], 'k')
plt.plot([3, 2, 2], [-3, -3, -4], 'k')
plt.plot([3, 10, 10], [-3, -3, -4], 'k')
plt.plot([4, 5, 5], [-6, -6, -7], 'k')
plt.plot([6, 4, 4], [-5, -5, -6], 'k')
plt.plot([6, 8, 8], [-5, -5, -6], 'k')
plt.plot([8, 7, 7], [-6, -6, -7], 'k')
plt.plot([8, 9, 9], [-6, -6, -7], 'k')
plt.plot([10, 6, 6], [-4, -4, -5], 'k')
plt.plot([10, 13, 13], [-4, -4, -5], 'k')
plt.plot([11, 12, 12], [-6, -6, -7], 'k')
plt.plot([13, 11, 11], [-5, -5, -6], 'k')
plt.plot([14, 3, 3], [-2, -2, -3], 'k')
plt.plot([14, 15, 15], [-2, -2, -3], 'k')
plt.text(0, 0, "0", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -1, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, -4, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -3, "3", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -6, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, -7, "5", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -5, "6", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(7, -7, "7", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(8, -6, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(9, -7, "9", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(10, -4, "11", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(11, -6, "12", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(12, -7, "13", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(13, -5, "14", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(14, -2, "15", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(15, -3, "17", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('5')
plt.show()