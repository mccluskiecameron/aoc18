from itertools import starmap
import sys

def display(lines, m):
    sys.stdout.write("\x1b[2J");
    mx = min(starmap(lambda x, v: x.x+v.x*m, lines))
    my = min(starmap(lambda x, v: x.y+v.y*m, lines))
    for x, v in lines:
        sys.stdout.write("\x1b[{};{}Hx".format(x.y+v.y*m - my, x.x+v.x*m - mx))
    sys.stdout.write("\x1b[20H")

class Vec2:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __mul__(s, o):
        return s.x*o.x + s.y*o.y
    def __sub__(s, o):
        return Vec2(s.x - o.x, s.y - o.y)

with open("10.txt") as f:
    p = []
    for l in f:
        x, y, vx, vy = map(int, l.split("\t"))
        p.append((Vec2(x, y), Vec2(vx, vy)))
    N = 0
    D = 0
    for i in range(len(p)-1):
        xi, vi = p[i]
        xj, vj = p[i+1]
        N += -((xi-xj)*(vi-vj))
        D += (vi-vj) * (vi-vj)
    display(p, round(N/D))
    print(round(N/D))
            
