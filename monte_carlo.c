#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NumThreads 4
#define NumPoints 10000

int TotalHits = 0;
pthread_mutex_t MyMutex;
pthread_t ThreadID[NumThreads];

void *ComputeRandom(void *);
void *ComputeRand_r(void *);

double SquareNum(double a) { return a * a; }

double RandDouble(double max, double min) {
  srandom(time(NULL));

  double RandNum = (double)random();
  double Normalize = RandNum / (double)RAND_MAX;
  double ShiftRange = Normalize * (max - min) + min;

  return ShiftRange;
}

double Rand_RDouble(double max, double min) {
	int RandSeed = time(NULL);
	double RandNum = (double)rand_r(&RandSeed);
	double Normalize = RandNum / (double)RAND_MAX;
	double ShiftRange = Normalize * (max-min)+min;

	return ShiftRange;

}

int main(int argc, char *argv[]) {
  int ret;
  int Count = NumPoints / NumThreads;
  double result;
  int rand_mode = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {
      rand_mode = 1;
    }
  }

  pthread_mutex_init(&MyMutex, NULL);

  if (rand_mode == 1) {
    for (int i = 0; i < NumThreads; i++) {
      ret = pthread_create(&ThreadID[i], NULL, ComputeRandom, (void *)&Count);
    }
  } else {
    for (int i = 0; i < NumThreads; i++) {
      ret = pthread_create(&ThreadID[i],NULL, ComputeRandom, (void *)&Count);
    }
  }

  for (int i = 0; i < NumThreads; i++) {
    pthread_join(ThreadID[i], NULL);
  }

  double PiApprox = ((double)TotalHits / (double)NumPoints) * 4.0;

  printf("%lf\n", PiApprox);

  return 0;
}

void *ComputeRandom(void *My_Count) {
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

void *ComputRand_r(void *My_Count) {
  int count = *((int *)My_Count);
  int num_hits = 0;

  for (int i = 0; i < count; i++) {

    double randomX = Rand_RDouble(1.0, -1.0);
    double randomY = Rand_RDouble(1.0, -1.0);

    if ((SquareNum(randomX) + SquareNum(randomY)) <= 1) {
      num_hits += 1;
    }
  }

  pthread_mutex_lock(&MyMutex);
  TotalHits += num_hits;

  pthread_mutex_unlock(&MyMutex);

  return ((void *)NULL);
}
