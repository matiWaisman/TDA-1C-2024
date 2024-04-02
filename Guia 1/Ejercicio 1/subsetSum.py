from queue import Queue

from collections import deque

class Queue:
    def __init__(self):
        self.queue = deque()

    def put(self, item):
        self.queue.append(item)

    def clear(self):
        self.queue.clear()

    def __str__(self):
        return str(list(self.queue))

elems = Queue()

def subset_sum(c, i, j):
    if(j < 0):
        return False
    if(j == 0):
        print(elems)
        return True
    if(i == -1):
        if (j == 0):
            print(elems)
            return True
        else: 
            return False
    else:
        no_pongo = subset_sum(c, i-1, j) 
        elems.put(c[i])
        pongo = subset_sum(c, i - 1, j - c[i])
        
        # Cuando llego aca es porque ya evalue la combinacion completa y no hay mas que explorar
        elems.clear()
        return pongo or no_pongo
    
subset_sum([6,12,6],2,12)