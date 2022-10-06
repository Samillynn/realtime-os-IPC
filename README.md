# Authors
- Hongyu Ding (20838222)
- Renhang Liu (21049351)

# project

# Build Instructions
## download

## build
```bash
cd cs452_k2
make clean && make
```
## run
put Pi number as the parameter for the ./upload.sh

for example, CS017542 (Pi No.2):
```bash
./upload.sh 2
```

# Kernel Descriptions
## Algorithms & Data Structures
- Multiple Producers Single Consumer (MPSC)
Both name server and RPS server use MPSC since MPSC suits their server-client pattern. 

For the name server, it acts like a single consumer that keeps consuming things sent from producers (clients) and process them from there. The name clients then acts like multiple producers that produces name queries to the server.

Similarly, the RPS server acts like a single consumer that keeps consuming queries sent from producers, and the RPS clients are producers that produce game actions and send those actions to the server.

- Hash Table
The name server uses a hash table to map names to Tids. From the reference http://www.cse.yorku.ca/~oz/hash.html a djb2 hash function is used by our hash table, which hashes a string to an unsigned word.

- Memory Pool
For simplicity, we have a simple memory pool for simple dynamic memory allocation. It preallocates a fixed-size array as the data pool, and it defines a fixed data chunk size. Every time we apply for some new memory, we find a non-used memory chunk in the data pool and give it to the user. Then set that chunk as used. When freeing an address, we simply set that corresponding chunk as non-used. The drawback of this method is that we cannot allocate a memory size greater than the predefined chunk size, and it takes linear time to find a free chunk in the pool. However, it gets things done easily.

- Queues
  - RPS queue
  We use a queue for storing signing up players. Whenever there are more than 2 players, we pop two as a pair.
  - message passing
  For every receiver there is a queue dedicated for it to get data from the senders. Basically all the data sent from the senders will be pushed into the corresponding receiver's queue, and the receiver will then be able to get the data from the queue.

## Limitations
## Bugs
# Output Descriptions
RPS game output:
```

```

