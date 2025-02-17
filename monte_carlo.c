#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NumThreads 4
#define NumPoints 1000000
int Total_Hits = 0;
pthread_mutex_t MyMutex;
pthread_t ThreadID[NumThreads];

void *Compute_Random(void *);
void *Compute_Rand_r(void *);

double Square_Num(double a) { return a * a; }

double Rand_Double(double max, double min) {
  double Rand_Num = (double)random();
  double Normalize = Rand_Num / (double)RAND_MAX;
  double Shift_Range = Normalize * (max - min) + min;
  return Shift_Range;
}

double Rand_r_Double(double max, double min, int *rand_seed) {
  double Rand_Num = (double)rand_r(rand_seed);
  double Normalize = Rand_Num / (double)RAND_MAX;
  double Shift_Range = Normalize * (max - min) + min;
  // printf("Shifted Range: %lf",Shift_Range);
  return Shift_Range;
}

int main(int argc, char *argv[]) {
  int ret;
  int Count = NumPoints / NumThreads;
  double result;
  int Rand_Mode = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-alt") == 0) {
      Rand_Mode = 1;
    }
  }

  pthread_mutex_init(&MyMutex, NULL);

  if (Rand_Mode == 1) {
    for (int i = 0; i < NumThreads; i++) {
      ret = pthread_create(&ThreadID[i], NULL, Compute_Rand_r, (void *)&Count);
    }
  } else {
    for (int i = 0; i < NumThreads; i++) {
      ret = pthread_create(&ThreadID[i], NULL, Compute_Random, (void *)&Count);
    }
  }

  for (int i = 0; i < NumThreads; i++) {
    pthread_join(ThreadID[i], NULL);
  }

  double Pi_Approx = ((double)Total_Hits / (double)NumPoints) * 4.0;

  printf("%lf\n", Pi_Approx);

  return 0;
}

void *Compute_Random(void *My_Count) {
  int count = *((int *)My_Count);
  int Num_Hits = 0;
  unsigned int Rand_Seed = time(NULL) ^ (long)pthread_self();
  srandom(Rand_Seed);
  for (int i = 0; i < count; i++) {

    double random_X = Rand_Double(1.0, -1.0);
    double random_Y = Rand_Double(1.0, -1.0);

    if ((Square_Num(random_X) + Square_Num(random_Y)) <= 1) {
      Num_Hits += 1;
    }
  }

  pthread_mutex_lock(&MyMutex);

  Total_Hits += Num_Hits;

  pthread_mutex_unlock(&MyMutex);

  return ((void *)NULL);
}

void *Compute_Rand_r(void *My_Count) {
  unsigned int Rand_Seed = time(NULL) ^ (long)pthread_self();
  int count = *((int *)My_Count);
  int Num_Hits = 0;

  // printf("count: %d\n",count);
  // printf("Rand_Seed: %d\n",Rand_Seed);

  for (int i = 0; i < count; i++) {

    double random_X = Rand_r_Double(1.0, -1.0, &Rand_Seed);
    double random_Y = Rand_r_Double(1.0, -1.0, &Rand_Seed);

    if ((Square_Num(random_X) + Square_Num(random_Y)) <= 1) {
      Num_Hits += 1;
    }
  }

  pthread_mutex_lock(&MyMutex);
  Total_Hits += Num_Hits;

  pthread_mutex_unlock(&MyMutex);

  return ((void *)NULL);
}
