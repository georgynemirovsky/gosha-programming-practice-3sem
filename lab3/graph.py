import matplotlib.pyplot as plt

f = open('results.txt', "r")
line = f.readlines()
x = []
y = []
z = []
for i in range(len(line)):
    x1, y1, z1 = line[i].split()
    x.append(float(x1)/1000)
    y.append(float(y1))
    z.append(float(z1))
fig, ax = plt.subplots()
plt.suptitle("")
ax.plot(x[40::], y[40::], marker='.', markersize=0.2)
ax.plot(x[40::], z[40::], marker='.', markersize=0.2)
ax.set_ylabel("")
ax.set_xlabel("")
plt.show()