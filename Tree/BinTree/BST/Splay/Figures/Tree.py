from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([1, 0, 0], [-1, -1, -2], 'k')
plt.plot([2, 1, 1], [0, 0, -1], 'k')
plt.plot([2, 5, 5], [0, 0, -1], 'k')
plt.plot([3, 4, 4], [-2, -2, -3], 'k')
plt.plot([5, 3, 3], [-1, -1, -2], 'k')
plt.plot([5, 9, 9], [-1, -1, -2], 'k')
plt.plot([7, 6, 6], [-3, -3, -4], 'k')
plt.plot([7, 8, 8], [-3, -3, -4], 'k')
plt.plot([9, 7, 7], [-2, -2, -3], 'k')
plt.plot([9, 12, 12], [-2, -2, -3], 'k')
plt.plot([10, 11, 11], [-4, -4, -5], 'k')
plt.plot([12, 10, 10], [-3, -3, -4], 'k')
plt.plot([12, 14, 14], [-3, -3, -4], 'k')
plt.plot([14, 13, 13], [-4, -4, -5], 'k')
plt.plot([14, 15, 15], [-4, -4, -5], 'k')
plt.text(0, -2, "0", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(1, -1, "1", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(2, 0, "2", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(3, -2, "3", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(4, -3, "4", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(5, -1, "5", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(6, -4, "6", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(7, -3, "7", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(8, -4, "8", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(9, -2, "9", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(10, -4, "11", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(11, -5, "12", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(12, -3, "13", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(13, -5, "14", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(14, -4, "15", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.text(15, -5, "17", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('Tree')
plt.show()
