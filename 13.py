data = open("13.txt").read().split("\n")
carts = []
rails = []
rots = [[0]*len(data[0]) for _ in data]
count = 0
for l in data:
    carts.append([])
    rails.append([])
    for i in l:
        if i in "><^v":
            count += 1
            carts[-1].append(i)
            if i in "<>":
                rails[-1].append("-")
            else:
                rails[-1].append("|")
        else:
            carts[-1].append(" ")
            rails[-1].append(i)

p1 = False

while count > 1:
    new_carts = [[" "] * len(data[0]) for _ in data]
    for i in range(len(data)):
        for j in range(len(data[i])):
            if carts[i][j] != ' ':
                ni, nj = {'>': (i, j+1), '<': (i, j-1), '^': (i-1, j), 'v': (i+1, j)}[carts[i][j]]
                if carts[ni][nj] != ' ' or new_carts[ni][nj] != ' ':
                    if not p1:
                        print(nj, ni)
                        p1 = True
                    count -= 2
                    carts[i][j] = ' '
                    carts[ni][nj] = ' '
                    new_carts[ni][nj] = ' '
                    continue
                r = rails[ni][nj]
                if r in "|-":
                    c = carts[i][j]
                elif r == '/':
                    c = {'>': "^", "<": "v", "v": '<', "^": ">"}[carts[i][j]]
                elif r == '\\':
                    c = {'>': "v", "<": "^", "v": '>', "^": "<"}[carts[i][j]]
                elif r == '+':
                    turn = rots[i][j]
                    c = {">": "^>v", "<": "v<^", "^": "<^>", "v": ">v<"}[carts[i][j]][turn]
                    rots[i][j] += 1
                    rots[i][j] %= 3
                else:
                    exit(12)
                carts[i][j] = " "
                new_carts[ni][nj] = c
                rots[i][j], rots[ni][nj] = 0, rots[i][j]
    carts = new_carts
for i in range(len(data)):
    for j in range(len(data[i])):
        if carts[i][j] != ' ':
            print(j, i)
            exit(0)
