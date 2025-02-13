## COS_542_Homework_2
- **Name:** Jacob Lorenzo
- **Date:** 2/7/2025
- **Instructor:** Dr. Dickens
- **Class:** COS 542
- **Assignment:** Homework 2

## Additional Help:
- I used the code displayed in lectures 5 and 6
- I used GeeksForGeeks to jog my memory on how to work with C
- Stackoverflow post to figure out how to get C to output time in miliseconds: 
https://stackoverflow.com/questions/10192903/time-in-milliseconds-in-c

## Observations: 
- Had to use the POSIX standard library for time.h because ANSI doesn't
  do millisecond precision. 

## Results:
|  | 10000 | 100000 | 1000000 |
|--|:-----:|:------:|:-------:|
|4 |.001801|.017195 |.167773  |
|8 |.002163|.026725 |.280091  |
|16|.003874|.020877 |.366582  |

## How To Run:
- You can compile it with 'make build'
- You can run it with 'make run'
- You can clean up the compiled file with 'make clean' 
- You can use 'make all' to compile, run, and cleanup. 
