# # import random
# # import string

# # def workload_generator(n, k, l):
# #     unique = int(n * 0.1) # 
# #     duplicate = int(n * 0.9) # number of duplicate values in the workload
# #     max_freq = duplicate/unique
# #     data = []
    
# #     for i in range(unique):
# #         data.append(i)

# #     for i in range((n - unique) + 1):
# #         num = random.randint(0, unique - 1)
# #         freq = random.randint(1, max_freq - 1)
# #         data.extend([num] * freq)
        
# #         if(len(data) >= n):
# #             data = data[:n]
# #             break

# #     data = sorted(data)

# #     # k is number of out of order entries
# #     # l is max displacement of out of order entries
# #     k = int((k * n)/100)
# #     l = int((l * n)/100)

# #     while k != 0:
# #         index = random.randint(0, n - 1)
# #         displ = random.randint(1, l)
# #         dir = random.randint(0, 1)
# #         if(dir > 0):
# #             new_index = index + displ
# #             if new_index > (n - 1):
# #                 new_index = n - 1
# #         else:
# #             new_index = index - displ
# #             if new_index < 0:
# #                 new_index = 0

# #         temp = data.pop(index)

# #         if new_index > len(data) - 1:
# #             new_index = len(data) - 1
        
# #         data.insert(new_index, temp)
# #         k -= 1

# #     with open('./Workload/Workload40MB/100_1.txt', 'w') as f:
# #         for item in data:
# #             f.write("%s\n" % item)

# # workload_generator(8388608, 100, 1)

import random
import string

def workload_generator(n, k, l):
    unique = int(n * 0.1)
    duplicate = int(n * 0.9)
    max_freq = int(duplicate/unique)
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
        print(k)
        k -= 1

    with open('./Workload/Workload40MB/100_1.txt', 'w') as f:
        for item in data:
            f.write("%s\n" % item)

workload_generator(8388608, 100, 1)

# import random
# import tqdm

# def workload_generator(n, k, l):
#     unique = int(n * 0.1)
#     duplicate = int(n * 0.9)
#     max_freq = int(duplicate/unique)
#     data = [i for i in range(unique)]
#     freqs = random.choices(range(unique), k=duplicate)
#     data += [freqs.count(i) * [i] for i in range(unique)]
#     data = [item for sublist in data for item in sublist]
    
#     for i in range(k):
#         index = random.randint(0, n - 1)
#         displ = random.randint(1, l)
#         direction = random.choice([-1, 1])
#         new_index = max(0, min(n-1, index + direction * displ))
#         data[index:new_index+1] = data[index+1:new_index+1] + [data[index]]
#         print(i)
    
#     with open('./Workload/Workload40MB/100_1.txt', 'w') as f:
#         for item in data:
#             f.write("%s\n" % item)
