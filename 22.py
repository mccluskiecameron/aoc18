from collections import defaultdict
from functools import lru_cache

D = 10647
Tx = 7
Ty = 770

@lru_cache((Tx+1)*(Ty+1))
def geologe(x, y):
    if(x == Tx and y == Ty) or (x == 0 and y == 0):
        return 0
    if(y == 0):
        return x * 16807
    if(x == 0):
        return y * 48271
    return erose(x-1, y) * erose(x, y-1)

def erose(x, y): return (geologe(x, y) + D) % 20183

def risk(x, y): return erose(x, y) % 3

def ty(x, y): return {0: "rocky", 1: "wet", 2: "narrow"}[risk(x, y)]

R = 0
for x in range(Tx+1):
    for y in range(Ty+1):
        R += risk(x, y)
print(R)

opts = {"rocky": {"climb", "torch"},
        "wet": {"climb", "neither"},
        "narrow": {"torch", "neither"}}

def circle(p):
    yield (p[0], p[1]-1)
    yield (p[0]-1, p[1])
    yield (p[0]+1, p[1])
    yield (p[0], p[1]+1)

tools = ["climb", "torch", "neither"]
visited = set()
distances = defaultdict(lambda: float("inf"))
distances[(0, 0, "torch")] = 0
to_visit = [(0, 0, "torch")]
while to_visit:
    nx = min(to_visit, key=lambda x: distances[x])
    if nx in ((Tx, Ty, t)  for t in tools):
        break
    to_visit.remove(nx)
    visited.add(nx)
    for n in circle(nx):
        if(n[0]<0 or n[0]>Tx*10 or n[1]<0 or n[1]>Ty*10):
            continue
        for tool in tools:
            if(tool not in opts[ty(n[0], n[1])] or tool not in opts[ty(nx[0], nx[1])]):
                continue
            nd = distances[nx] + 1
            if tool != nx[2]:
                nd += 7
            if nd < distances[(n[0], n[1], tool)]:
                distances[(n[0], n[1], tool)] = nd
                to_visit.append((n[0], n[1], tool))
if nx[2] != "torch":
    distances[nx] += 7
print(nx)
print(distances[nx])
