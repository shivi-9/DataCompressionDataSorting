import random
import string

class DatasetCreater:
    def __init__(self, length) -> None:
        self.length = length
        
    def create_numerical_workload(self):
        frequncy = random.randint(0, 100)
        stream = []
        for i in range(self.length//frequncy):
            for j in range(frequncy):
                stream.append(i)
        if(len(stream) < self.length):
            for i in range(len(stream), self.length):
                stream.append(random.randint(0, 100))
        random.shuffle(stream)
        self.write_to_csv(stream)  

    def create_ascii_workload(self):
        stream = []
        alphabet = string.ascii_lowercase 
        for i in range(self.length):
            f = random.randint(0, len(alphabet)-1)
            stream.append(alphabet[f])
        random.shuffle(stream)
        self.write_to_csv(stream) 

    def write_to_csv(self, stream):
        with open("./Workload/workload.txt", "w") as file:
            for item in stream:
                file.write(str(item) + "\n")

creater = DatasetCreater(10000)
creater.create_numerical_workload()