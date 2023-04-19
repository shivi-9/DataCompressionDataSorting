import random
import string

def workload_generator(n, k, l):
    unique = int(n * 0.1)
    duplicate = int(n * 0.9)
    max_freq = duplicate/unique
    data = []

    for i in range(unique):
        data.append(i)

    for i in range(unique):
        num = random.randint(0, unique)
        freq = random.randint(0, max_freq)
        data.extend([num] * freq)

    if(len(data) != n):
        empty_slots = n - len(data)
        for i in range(empty_slots):
            data.append(random.randint(0, unique))

    data = sorted(data)

    # k is number of out of order entries
    # l is max displacement of out of order entries

    while k != 0:
        index = random.randint(0, n)
        displ = -1
        if index - l < 0:
            displ = index + l
        else:
            displ = index - l

        temp = data.pop(index)
        data.insert(displ, temp)
        k -= 1
    
    with open('./Workload/workload.txt', 'w') as f:
        for item in data:
            f.write("%s\n" % item)

workload_generator(1000000, 5000, 5000)