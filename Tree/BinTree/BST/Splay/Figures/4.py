from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([0, 1, 1], [-4, -4, -5], 'k')
plt.plot([2, 0, 0], [-3, -3, -4], 'k')
plt.plot([2, 5, 5], [-3, -3, -4], 'k')
plt.plot([3, 4, 4], [-5, -5, -6], 'k')
plt.plot([5, 3, 3], [-4, -4, -5], 'k')
plt.plot([5, 7, 7], [-4, -4, -5], 'k')
plt.plot([7, 6, 6], [-5, -5, -6], 'k')
plt.plot([7, 8, 8], [-5, -5, -6], 'k')
plt.plot([9, 2, 2], [-2, -2, -3], 'k')
plt.plot([9, 12, 12], [-2, -2, -3], 'k')
plt.plot([10, 11, 11], [-4, -4, -5], 'k')
plt.plot([12, 10, 10], [-3, -3, -4], 'k')
plt.plot([13, 9, 9], [-1, -1, -2], 'k')
plt.plot([14, 13, 13], [0, 0, -1], 'k')
plt.text(0, -4, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -5, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, -3, "3", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -5, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -6, "5", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, -4, "6", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -6, "7", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(7, -5, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(8, -6, "9", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(9, -2, "11", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(10, -4, "12", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(11, -5, "13", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(12, -3, "14", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(13, -1, "15", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(14, 0, "17", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('4')
plt.show()