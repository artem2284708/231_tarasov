#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define MIN_ARRAY_SIZE 16

typedef struct {
    int start;
    int end;
    int* array;
} ThreadArgs;

typedef struct {
    int* data;
    size_t size;
} IntArray;

pthread_mutex_t sum_mutex;
int global_sum = 0;

void* worker(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int local_sum = 0;

    for (int i = args->start; i < args->end; ++i) {
        local_sum += args->array[i];
    }

    pthread_mutex_lock(&sum_mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);

    return NULL;
}

IntArray create_random_array(size_t size) {
    IntArray array;
    array.size = size;
    array.data = malloc(sizeof(int) * size);
    
    if (array.data == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; ++i) {
        array.data[i] = rand() % 100;
    }

    return array;
}

void print_array(const IntArray* array) {
    printf("Array: ");
    for (size_t i = 0; i < array->size; ++i) {
        printf("%d ", array->data[i]);
    }
    printf("\n");
}

void parallel_sum(const IntArray* array) {
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int chunk = array->size / NUM_THREADS;
    int remainder = array->size % NUM_THREADS;

    pthread_mutex_init(&sum_mutex, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        args[i].start = i * chunk;
        args[i].end = (i == NUM_THREADS - 1) ? (i + 1) * chunk + remainder : (i + 1) * chunk;
        args[i].array = array->data;
        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&sum_mutex);
}

int main() {
    size_t N;
    printf("Enter size n: ");
    scanf("%zu", &N);

    if (N < MIN_ARRAY_SIZE) {
        fprintf(stderr, "n must be at least %d\n", MIN_ARRAY_SIZE);
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    IntArray array = create_random_array(N);
    print_array(&array);

    parallel_sum(&array);
    printf("Sum: %d\n", global_sum);

    free(array.data);
    return EXIT_SUCCESS;
}
