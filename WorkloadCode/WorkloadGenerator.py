import random

def workload_generator(n, k, l):
    unique = int(n * 0.75)
    duplicate = int(n * 0.25)
    max_freq = int(duplicate/unique)
    data = []
    
    for i in range(unique):
        data.append(i)

    for i in range((n - unique) + 1):
        num = random.randint(0, unique - 1)
        freq = random.randint(1, duplicate)
        data.extend([num] * freq)
        
        if(len(data) >= n):
            data = data[:n]
            break

    data = sorted(data)

    k = int((k * n)/100)
    l = int((l * n)/100)

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
        # print(k)
        k -= 1

    with open('./Workload-75%/1_1.txt', 'w') as f:
        for item in data:
            f.write("%s\n" % item)

workload_generator(20480, 1, 1)