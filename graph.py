import csv
import matplotlib.pyplot as plt
import math

x = []
avlt = []
rbt = []

with open('result.csv') as csv_file:
	csv_reader = csv.reader(csv_file, delimiter=',')
	for row in csv_reader:
		if len(row) == 0:
			break
		else:
			x.append(math.log(int(row[0])))
			avlt.append(float(row[1]))
			rbt.append(float(row[2]))



# print(x)
# print(avlt)
# print(rbt)

plt.plot(x, avlt, linewidth = 2)
plt.plot(x, rbt, linewidth = 2)

plt.xlabel("No of READ-WRITE operations -->")
plt.ylabel("log(Time elapsed in sec) -->")
plt.legend({"AVL Tree", "RB Tree"})

plt.savefig('plots/graph.png', dpi=400)