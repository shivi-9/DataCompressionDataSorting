import random
import string

def workload_generator(n, k, l):
    unique = int(n * 0.1) # 
    duplicate = int(n * 0.9) # number of duplicate values in the workload
    max_freq = duplicate/unique
    data = []
    
    for i in range(unique):
        data.append(i)

    for i in range((n - unique) + 1):
        num = random.randint(0, unique - 1)
        freq = random.randint(1, max_freq - 1)
        data.extend([num] * freq)
        
        if(len(data) >= n):
            data = data[:n]
            break

    data = sorted(data)

    # k is number of out of order entries
    # l is max displacement of out of order entries

    while k != 0:
        index = random.randint(0, n - 1)
        displ = random.randint(1, l)
        dir = random.randint(0, 1)
        if(dir > 0):
            new_index = index + displ
            if new_index > (n - 1):
                new_index = n - 1
        else:
            new_index = index - displ
            if new_index < 0:
                new_index = 0

        temp = data.pop(index)

        if new_index > len(data) - 1:
            new_index = len(data) - 1
        
        data.insert(new_index, temp)
        k -= 1

    with open('./Workload/workload.txt', 'w') as f:
        for item in data:
            f.write("%s\n" % item)

workload_generator(200, 8, 5)