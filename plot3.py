import matplotlib.pyplot as plt
import os
import numpy as np
import itertools

time_parallel = "Parallel_time.txt"
time_serial = "Serial_time.txt"

def read_file(file_name):
	with open(file_name, 'r') as file:
		size = []
		time = []
		for line in file:
			data = [float(s) for s in line.split(",")]
			size.append(data[0])
			time.append(data[1])
	return size,time

sizehp,timehp = read_file(time_parallel)
sizeh,timeh = read_file(time_serial)

plt.subplot(111)
plt.plot(sizehp,timehp, 'b', marker ='o', linestyle="--")
plt.plot(sizeh,timeh, 'b', marker ='o', linestyle="-")
plt.legend(["Parallel Hybridsort","Serial Hybridsort"])
plt.xlabel("size")
plt.ylabel("Execution time")
plt.show()