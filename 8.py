
def read (ind, data):
    #print(data[ind:])
    num = data[ind]
    ind += 1
    count = data[ind]
    ind += 1
    s = 0
    for i in range(num):
        j, c = read(ind, data)
        ind = j
        s += c
    for i in range(count):
        s += data[ind]
        ind += 1
    return ind, s
    
def value (ind, data):
    #print(data[ind:])
    num = data[ind]
    ind += 1
    count = data[ind]
    ind += 1
    if num == 0:
        s = 0
        for i in range(count):
            s += data[ind]
            ind += 1
        return ind, s
    chs = []
    for i in range(num):
        j, c = value(ind, data)
        ind = j
        chs.append(c)
    s = 0
    for i in range(count):
        if data[ind]-1 < num:
            s += chs[data[ind]-1]
        ind += 1
    return ind, s

    

with open("8.txt") as f:
    data = list(map(int, f.read().split(" ")))
    #data = list(map(int, "2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2".split(" ")))
    ind, s = read(0, data)
    print(s)
    ind, s = value(0, data)
    print(s)
