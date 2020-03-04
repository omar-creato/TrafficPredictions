# -*- coding: utf-8 -*-
"""
Created on Wed Mar  4 12:38:30 2020

@author: Shraddha Jain
"""

# -*- coding: utf-8 -*-
"""
Created on Mon Mar  2 15:43:12 2020

@author: Shraddha Jain
"""
from pylab import*
import math
import numpy as np
import matplotlib.pyplot as plt
from random import randrange
from random import sample
num_cars = 5
L = 100
num_cells = (int)(L/7.5)
tot_time = 5
Vmax = 5
prob = 0.3
c=0
pos_time = np.zeros([tot_time,num_cells])
flag=0
num = np.linspace(0,num_cells-1,num_cells,dtype=int)
num = num.tolist()
for i in range(num_cars):
    rdm = sample(num,1)
    num.remove(rdm[0])
    pos_time[0,rdm[0]] = rdm[0]+1
    

vel = np.zeros(num_cars)
for i in range(num_cars):
    R = randrange(0,Vmax+1,1)
    vel[i] = R
print(vel)
print(pos_time)

"""
for t in range(tot_time):
    for p in range(num_cars):
        if(p==num_cars-1):
            d = num_cells - pos_time[t,p] + pos_time[t,0]#math.abs(pos_time[t,0]-pos_time[t,p])
        else:
            d = math.abs(pos_time[t,p+1]-pos_time[t,p])
            
        if(vel[p]<Vmax):
            vel[p] = vel[p]+1
        if(d<=vel[p]):
            vel[p] = d-1
        if(vel[p]>0):
            r = np.random.random()
            if(r<prob):
                vel[p] = vel[p]-1
        
        pos_time[t,p] = pos_time[t,p] + vel[p]
        
 """       

