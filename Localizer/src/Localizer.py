'''
This class is used for localization of the cwru lunabot in the arena
It will eventually take in postieror pdf for the from the vision sensor
and range sensor to determine the initial position of the robot
in the mining field

Author: Eddie Massey III





'''

#uniform probability 1/(b-a) 
world = ['blue', 'red', 'blue', 'green', 'red', 'green']
measurements = ['red', 'green'] #Z
p=[] #probability list
weight = 1.0
n= len(world) #(b-a)

#prior prob. dist. function
for i in range(len(world)):
    p.append(weight/n)


pHit = 0.6
pMiss = 0.2

def sense(p,Z):
    q = []
    #make posterior belief
    for i in range(len(world)):
        hit = (Z == world[i])
        q.append(p[i] * (hit * pHit + (1-hit) * pMiss))
        
    #normalize the probility distrubution
    s = sum(q)
    for j in range(len(p)):
        q[j] = q[j]/s

    return q

for k in range(len(measurements)):
    p = sense(p, measurements[k])

print p 


