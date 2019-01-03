from collections import defaultdict
import sys
from copy import deepcopy


class Un:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.h = 200
        self.gone = 0
    
    def p(self):
        return (self.x, self.y)

    def attack(self, foes):
        fs = []
        for c in circle(self.p()):
            f = find(c, foes)
            if f is not None:
                fs.append(f)
        if fs:
            f = min(fs, key=lambda u: u.h)
            if foes == elves or len(sys.argv)<2:
                f.h -= 3
            else:
                f.h -= int(sys.argv[1])
            if f.h <= 0:
                foes.remove(f)
            return 1
        return 0

    def go(self, friends, foes):
        if not self.attack(foes):
            step = route((self.x, self.y), to_attack(foes))
            if step is not None:    
                self.x = step[0]
                self.y = step[1]
                self.attack(foes)
        self.gone = 1

def find(p, l):
    for u in l:
        if u.x == p[0] and u.y == p[1]:
            return u

def clear(l):
    for i in l:
        i.gone = 0
            
def circle(p):
    yield (p[0], p[1]-1)
    yield (p[0]-1, p[1])
    yield (p[0]+1, p[1])
    yield (p[0], p[1]+1)

def to_attack(units):
    fin = set()
    for unit in units:
        fin.update(circle(unit.p()))
    return fin

#taken straight from SO like a full blood pajeet
def route(start, points):
    visited = set()
    distances = defaultdict(lambda: float("inf"))
    distances[start] = 0
    to_visit = [start]
    tentative_parents = {}
    while to_visit:
        nx = min(to_visit, key=lambda x: distances[x])
        if nx in points:
            break
        to_visit.remove(nx)
        visited.add(nx)
        for n in circle(nx):
            if n in visited or terrain[n[1]][n[0]] == '#' or\
                            find(n, gobs) or find(n, elves):
                continue
            nd = distances[nx] + 1
            if nd < distances[n]:
                distances[n] = nd
                tentative_parents[n] = nx
                to_visit.append(n)
    else:
        return None
    path = []
    while nx:
        path.append(nx)
        nx = tentative_parents.get(nx)
    return path[-2]

def disp():
    t = deepcopy(terrain)
    for u in elves:
        t[u.y][u.x] = "E"
    for u in gobs:
        t[u.y][u.x] = "G"
    print("\n".join("".join(l) for l in t))

def healthes():
    for e in elves:
        print("E:", e.h)
    for e in gobs:
        print("G:", e.h)

data = open("15-test.txt").read().split("\n")
elves = [Un(x, y) for y, l in enumerate(data) for x, c in enumerate(l) if c == 'E']
gobs =  [Un(x, y) for y, l in enumerate(data) for x, c in enumerate(l) if c == 'G']
terrain = [['.' if c in ".GE" else '#' for c in l] for l in data]

start_len = len(elves)

rounds = 0
while len(elves) and len(gobs):
    disp()
    healthes()
    while 1:
        try:
            y, x = min(( (u.y, u.x) for u in elves+gobs if u.gone == 0))
        except:
            break
        f = find((x, y), elves)
        if f is not None:
            f.go(elves, gobs)
        f = find((x, y), gobs)
        if f is not None:
            f.go(gobs, elves)
    if elves and gobs:
        rounds += 1
    #print(rounds)
    clear(elves)
    clear(gobs)

H = sum((u.h for u in gobs+elves))

print(rounds * H)

if len(elves) == start_len: 
    print("H:", rounds * H, file=sys.stderr)
    exit(0)
    print("elves")
exit(1)

