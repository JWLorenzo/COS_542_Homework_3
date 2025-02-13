#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NumThreads 4
#define NumPoints 10000
#include <sys/time.h>

int TotalHits = 0;
pthread_mutex_t MyMutex;
pthread_t ThreadID[NumThreads];

void *Compute(void *);

double SquareNum(double a) { return a * a; }

double RandDouble(double max, double min) {

  double RandNum = (double)rand();
  double Normalize = RandNum / (double)RAND_MAX;
  double ShiftRange = Normalize * (max - min) + min;

  return ShiftRange;
}

int main() {
  int ret;
  int Count = NumPoints / NumThreads;
  double result;
  struct timeval start, end;

  gettimeofday(&start, NULL);
  pthread_mutex_init(&MyMutex, NULL);

  for (int i = 0; i < NumThreads; i++) {
    ret = pthread_create(&ThreadID[i], NULL, Compute, (void *)&Count);
  }
  for (int i = 0; i < NumThreads; i++) {
    pthread_join(ThreadID[i], NULL);
  }

  double PiApprox = ((double)TotalHits / (double)NumPoints) * 4.0;

  printf("%lf\n", PiApprox);

  gettimeofday(&end, NULL);

  result = (double)(end.tv_usec - start.tv_usec) / 1000000 +
           (double)(end.tv_sec - start.tv_sec);

  printf("Time: %f\n", result);

  return 0;
}

void *Compute(void *My_Count) {
  int count = *((int *)My_Count);
  int num_hits = 0;

  for (int i = 0; i < count; i++) {

    double randomX = RandDouble(1.0, -1.0);
    double randomY = RandDouble(1.0, -1.0);

    if ((SquareNum(randomX) + SquareNum(randomY)) <= 1) {
      num_hits += 1;
    }
  }

  pthread_mutex_lock(&MyMutex);

  TotalHits += num_hits;

  pthread_mutex_unlock(&MyMutex);

  return ((void *)NULL);
}
