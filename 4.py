import re
from collections import defaultdict

tots = defaultdict(int)
lists = defaultdict(lambda: [0]*24*60)
with open("4.txt") as f:
    for line in f:
        m = re.match(r"\[[^ ]* (\d+):(\d+)\] (.*)\n", line)
        time = int(m.group(1)) * 60 + int(m.group(2))
        m2 = re.match( "Guard #(\d+) begins shift", m.group(3))
        if m2 is not None:
            guard = int(m2.group(1))
        elif m.group(3) == "falls asleep":
            lt = time
        elif m.group(3) == "wakes up":
            delt = (time - lt) % (24*60)
            tots[guard] += delt
            for i in range(time-delt, time):
                lists[guard][i] += 1

g = max(tots, key=lambda k: (tots[k], k))
v, j = max((lists[g][i], i) for i in range(24*60))
print(g, j, g*j)

v, j, g = max((lists[g][i], i, g) for g in tots for i in range(24*60))
print(g, j, g * j)
