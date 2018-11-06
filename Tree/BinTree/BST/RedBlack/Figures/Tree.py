from matplotlib.patches import Circle
import matplotlib.pyplot as plt

plt.plot([0, 1, 1], [0, 0, -1], 'k')
plt.text(0, 0, "2", color = "w", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="#282923"))
plt.text(1, -1, "3", color = "w", size=15, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="r"))
plt.axis('scaled')
plt.axis('equal')

plt.axis('off')
plt.tight_layout()
fig = plt.gcf()
fig.canvas.set_window_title('Tree')
plt.show()
