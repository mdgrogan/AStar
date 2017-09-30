import sys
import numpy as np
import math
import pylab as py
import matplotlib.patches as mpatches 
import matplotlib.pyplot as plt 

#file_list = [("H1_33.txt",'red'),("H2_33.txt",'blue'),
#             ("H1_34.txt",'red'),("H2_34.txt",'blue'),
#             ("H1_35.txt",'red'),("H2_35.txt",'blue')]

file_list = [("H1_33.txt",'red'),("H2_33.txt",'blue'),
data_list = [(py.loadtxt(filename), color) for filename, color in file_list]

for data, color in data_list:
    plt.scatter(data[:,2], data[:,3], s=4, color=color)

red_patch = mpatches.Patch(color='red', label='H1')
blue_patch = mpatches.Patch(color='blue', label='H2')
plt.title("3 Stacks, 3 Blocks",fontsize=20)
plt.xlabel("Depth",fontsize=20)
plt.ylabel("Queue size",fontsize=30)
plt.legend(handles=[red_patch, blue_patch])
plt.show()
