#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_THREADS 4
#define NUM_POINTS 1000000

int total_hits = 0;
pthread_mutex_t mutex;
pthread_t thread_id[NUM_THREADS];

void *compute_random(void *);
void *compute_rand_r(void *);

double square_num(double a) {
    return a * a;
}

double rand_double(double max, double min) {
    double rand_num = (double)random();
    double normalize = rand_num / (double)RAND_MAX;
    double shift_range = normalize * (max - min) + min;
    return shift_range;
}

double rand_r_double(double max, double min, int *rand_seed) {
    double rand_num = (double)rand_r(rand_seed);
    double normalize = rand_num / (double)RAND_MAX;
    double shift_range = normalize * (max - min) + min;
    return shift_range;
}

int main(int argc, char *argv[]) {
    int ret;
    int count = NUM_POINTS / NUM_THREADS;
    double result;
    int rand_mode = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-alt") == 0) {
            rand_mode = 1;
        }
    }

    pthread_mutex_init(&mutex, NULL);

    if (rand_mode == 1) {
        for (int i = 0; i < NUM_THREADS; i++) {
            ret = pthread_create(&thread_id[i], NULL, compute_rand_r, (void *)&count);
        }
    } else {
        for (int i = 0; i < NUM_THREADS; i++) {
            ret = pthread_create(&thread_id[i], NULL, compute_random, (void *)&count);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    double pi_approx = ((double)total_hits / (double)NUM_POINTS) * 4.0;

    printf("%lf\n", pi_approx);

    return 0;
}

void *compute_random(void *my_count) {
    int count = *((int *)my_count);
    int num_hits = 0;
    unsigned int rand_seed = time(NULL) ^ (long)pthread_self();
    srandom(rand_seed);

    for (int i = 0; i < count; i++) {
        double random_x = rand_double(1.0, -1.0);
        double random_y = rand_double(1.0, -1.0);

        if ((square_num(random_x) + square_num(random_y)) <= 1) {
            num_hits += 1;
        }
    }

    pthread_mutex_lock(&mutex);
    total_hits += num_hits;
    pthread_mutex_unlock(&mutex);

    return ((void *)NULL);
}

void *compute_rand_r(void *my_count) {
    unsigned int rand_seed = time(NULL) ^ (long)pthread_self();
    int count = *((int *)my_count);
    int num_hits = 0;

    for (int i = 0; i < count; i++) {
        double random_x = rand_r_double(1.0, -1.0, &rand_seed);
        double random_y = rand_r_double(1.0, -1.0, &rand_seed);

        if ((square_num(random_x) + square_num(random_y)) <= 1) {
            num_hits += 1;
        }
    }

    pthread_mutex_lock(&mutex);
    total_hits += num_hits;
    pthread_mutex_unlock(&mutex);

    return ((void *)NULL);
}