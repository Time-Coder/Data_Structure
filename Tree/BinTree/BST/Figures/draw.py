from matplotlib.patches import Ellipse, Circle
import matplotlib.pyplot as plt

plt.plot([0,5], [0,5]);
plt.text(0, 0, "test", size=10, ha="center", va="center", bbox=dict(boxstyle="circle", ec="k", fc="w"))

plt.axis('scaled')
plt.axis('equal')

plt.xlim(-10, 10)
plt.ylim(-10, 10)

plt.axis('off')
plt.tight_layout()
plt.show()