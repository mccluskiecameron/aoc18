vals = set()
m = 0
while 1:
    a = int(input())
    if not m and a in vals:
        print(oa)
        m = 1
    if m and a not in vals:
        print("fuck")
    vals.add(a)
    oa = a
