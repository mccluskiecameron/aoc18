
n = 147061+10
#n = 5+10
scoreboard = [3, 7]
elf1 = 0
elf2 = 1
recip = '147061'
last = '0'
while recip not in last:
    add = str(scoreboard[elf1] + scoreboard[elf2])
    scoreboard.append(int(add[0]))
    if len(add) > 1: scoreboard.append(int(add[1]))
    s_len = len(scoreboard)
    elf1 = (elf1 + 1 + scoreboard[elf1])%s_len
    elf2 = (elf2 + 1 + scoreboard[elf2])%s_len
    last = ''.join(str(d) for d in scoreboard[-7:])
print scoreboard[-10:]
print s_len-6 #+- 1, but doesn't matter
