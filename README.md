## COS_542_Homework_3
- **Name:** Jacob Lorenzo
- **Date:** 2/16/2025
- **Instructor:** Dr. Dickens
- **Class:** COS 542
- **Assignment:** Homework 3

## How To Run:
- You can compile it with 'make build'
- You can run it with 'make run' or 'make run_alt' if you want to use rand_r() instead of random()
- You can clean up the compiled file with 'make clean' 
- You can use 'make all' or 'make all_alt' to compile, run, and cleanup respective to the methods mentioned above. 

## Additional Help:
- I used the code displayed in lectures 5 and 6
- I used GeeksForGeeks to jog my memory on how to work with C

## Results:

### Random()
|          |1      |4      |8       |16       |
|:--------:|:-----:|:-----:|:------:|:-------:|
|100000000 |0:03.44|0:10.63|0:38.84 |0:27.90  |
|1000000000|0:34.38|2:10.62|8:38.55 |3:54.89  |
|2000000000|1:08.90|4:42.53|18:01.53|14:32.58 |

### Random()
|            |1       |4            |8       |16           |
|:----------:|:------:|:-----------:|:------:|:-----------:|
|100000000   |3.141620|3.141118     |3.141283|3.141590     |
|1000000000  |3.141611|3.141523     |3.141606|3.141519     |
|2000000000  |3.141611|3.141557     |3.141593|3.141618     |
|PI (Average)|3.141614|3.14139933333|3.141494|3.14157566667|

### rand_r

|          |1       |4       |16      |
|:--------:|:------:|:------:|:------:|
|100000000 |3.141596|3.141286|3.141718|


### Graduate Students

|       |1      |4      |16     |
|:-----:|:-----:|:-----:|:-----:|
|random |0:03.44|0:10.63|0:27.90|
|rand_r |0:02.63|0:00.66|0:00.33|


#### Discussion

From my observations, the random() method increases in time per iteration, while the rand_r() method tends to decrease in time as the number of threads increases. As was discussed in class, random() is not a thread-safe method for generating random numbers.

This is because random() relies on state information maintained by a global variable. What this means is that each thread is trying to access and modify the same global state simultaneously, which introduces significant overhead. The threads contend for access to the same memory block, which can lead to race conditions. A race condition occurs if one thread modifies the global state before another thread finishes its operation. Additionally, this can lead to false sharing: when threads cache the global state and another thread updates it, the cached memory is invalidated, forcing the threads to reload the updated state from RAM. This further increases the time spent on memory operations, adding more overhead.

On the other hand, rand_r() uses a seed per thread, with each thread maintaining its own seed in its local memory. Each thread’s seed is modified when it calls rand_r(), meaning there is no conflict with other threads trying to access or modify the same memory block. This is why rand_r() is considered thread-safe; each thread operates independently with its own local state.



##### Sources:
- https://man7.org/linux/man-pages/man3/random.3.html
- https://man7.org/linux/man-pages/man3/random_r.3.html
- https://man7.org/linux/man-pages/man3/srandom.3.html 
- https://man7.org/linux/man-pages/man3/rand.3p.html
- https://en.wikipedia.org/wiki/False_sharing 
