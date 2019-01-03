from itertools import *
from heapq import *
from math import *

points = []
for i, line in enumerate(open("23.txt")):
    x, y, z, r = map(int, line.strip().split())
    points.append((x, y, z, r))

width = 1<<31
mins = [-1<<30, -1<<30, -1<<30]
choices = []

while width:
    for x,y,z in product(*((i, i+width) for i in mins)):
        c = 0
        for xa,ya,za,r in points:
            for xi,yi,zi in ((xa,ya,za), (xa-r,ya,za),(xa+r,ya,za), (xa,ya-r,za),(xa,ya+r,za), (xa,ya,za-r),(xa,ya,za+r)):
                if x<=xi<x+width and y<=yi<y+width and z<=zi<z+width:
                    break
            else:
                for xi, yi, zi in product(*((i, i+width-1) for i in [x,y,z])):
                    if abs(xi-xa) + abs(yi-ya) + abs(zi-za) <= r:
                        break
                else:
                    c+=1
        heappush(choices, (c, width//2, [x, y, z]))
    c, width, mins = heappop(choices)

print(mins)
