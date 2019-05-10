import matplotlib.pyplot as plt
import os
import numpy as np
import itertools

time_parallel = "Serial_time.txt"

def read_file(file_name):
	with open(file_name, 'r') as file:
		cutoff = []
		time = []
		for line in file:
			data = [float(s) for s in line.split(",")]
			cutoff.append(data[0])
			time.append(data[1])
	return cutoff,time

cutoff,time = read_file(time_parallel)

plt.subplot(111)
plt.plot(cutoff,time, 'b', marker ='o', linestyle="--")
plt.xlabel("Size of Run")
plt.ylabel("Execution Time")
plt.show()