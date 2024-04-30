import matplotlib.pyplot as plt
from matplotlib.patches import Polygon

triangles = []
with open("output.txt", "r") as f:
    for line in f:
        x1, y1, x2, y2, x3, y3 = map(int, line.split())
        triangles.append([(x1, y1), (x2, y2), (x3, y3)])
fig, ax = plt.subplots(figsize=(10, 8), dpi=300)
# Axis should not be visible in the plot vertices of triangle marked in black and edges in gray
for triangle in triangles:
    ax.add_patch(Polygon(triangle, closed=True, fill=None, edgecolor="gray"))
    for x, y in triangle:
        ax.plot(x, y, "ko", markersize=4)

ax.autoscale()
ax.axis("off")
plt.savefig("./outfolder/output.png", bbox_inches="tight", pad_inches=0)
plt.close()
