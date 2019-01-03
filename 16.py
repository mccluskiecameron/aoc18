from operator import *

def i(cmd, a, b, c, regs):
    out = regs[:]
    out[c] = cmd(regs[a], b)
    return out

def r(cmd, a, b, c, regs):
    out = regs[:]
    out[c] = cmd(regs[a], regs[b])
    return out

def ir(cmd, a, b, c, regs):
    out = regs[:]
    out[c] = cmd(a, regs[b])
    return out

def s(a, b):
    return a

def seti(a, b, c, regs):
    out = regs[:]
    out[c] = a
    return out

commands = [
    lambda *x: r(add, *x),
    lambda *x: i(add, *x),
    lambda *x: r(mul, *x),
    lambda *x: i(mul, *x),
    lambda *x: r(and_, *x),
    lambda *x: i(and_, *x),
    lambda *x: r(or_, *x),
    lambda *x: i(or_, *x),
    lambda *x: r(s, *x),
    lambda *x: seti(*x),
    lambda *x: r(gt, *x),
    lambda *x: i(gt, *x),
    lambda *x: ir(gt, *x),
    lambda *x: r(eq, *x),
    lambda *x: i(eq, *x),
    lambda *x: ir(eq, *x),
]
command_names =["addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
"setr", "seti", "gtrr", "gtri", "gtir", "eqrr", "eqri", "eqir"]
print(len(commands))

cmds = [0x7fff for _ in range(16)]

data = open("16.txt").read().strip().split("\n")

bef = data[::3]
cmd = data[1::3]
aft = data[2::3]

#g = [8, 12, 14, 10, 11, 1, 9, 9, 7, 6, 15, 0, 3, 2, 13, 4]
g = [11, 5, 13, 12, 15, 7, 9, 8, 0, 6, 3, 4, 1, 14, 2, 10]
init = [0, 0, 0, 0]
for line in open("16-cmds.txt"):
    cmd, a, b, c = map(int, line.strip().split())
    init = commands[g[cmd]](a, b, c, init)
    print(init)
print(init[0])

exit(0)

total = 0
col = zip(bef, cmd, aft)
for b, c, a in col:
    regs = eval(b[7:])
    out = eval(a[7:])
    real, a, b, c = map(int, c.split(" "))
    once = 0
    for n, cmd in enumerate(commands):
        if cmd(a, b, c, regs) != out:
            cmds[n] &= ~(1<<real)
        else:
            once += 1

    if once >= 3:
        total += 1
print(cmds)

#g = {}
#g = {5: 1, 3: 10, 4: 11, 2: 14, 8: 7, 10: 3, 12: 3, 11: 0, 14: 13, 13: 2, 15: 4, 9: 6, 6: 9, 0: 8, 7: 5, 1: 12}
#while 1:
#    for n, x in enumerate(cmds):
#        b = []
#        for i in range(16):
#            if x & (1<<i):
#                b.append(i)
#        if(len(b))==1:
#            g[n] = b[0]
#    print(g)
#    for k in g:
#        for i in range(16):
#            if i != k:
#                cmds[n] &= ~(1<<g[k])
#
#    print(cmds)

