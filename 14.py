def digs(n):
    if not n:
        yield 0
    while n:
        yield n % 10
        n //= 10

N = 919901
match = list(digs(N))[::-1]

rec = [3, 7]
e1 = 0
e2 = 1

while 1:
    for d in list(digs(rec[e1] + rec[e2]))[::-1]:
        if len(rec) == N + 10: 
            print("".join(map(str, rec[N:N+10])))
        if rec[-len(match):] == match:
            print(len(rec) - len(match))
            exit(0)
        rec.append(d)
    e1 += rec[e1] + 1
    e1 %= len(rec)
    e2 += rec[e2] + 1
    e2 %= len(rec)
