#include "inc/benchmark.h"
#include "inc/defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint64_t start;
    uint64_t end;
    
    uint64_t line;
    const char *file;
    const char *function;
} benchmark_t;

static benchmark_t benchmark_stack[BENCHMARK_MAX_DEPTH];
static benchmark_t *benchmark_stack_ptr = benchmark_stack;
static benchmark_t *benchmark_stack_end = benchmark_stack + BENCHMARK_MAX_DEPTH;
static FILE *benchmark_file = NULL;

void benchmark_start() {
    benchmark_file = fopen("benchmark.json", "w");
    if (!benchmark_file) {
        fprintf(stderr, "Failed to open benchmark file\n");
        abort();
    }
    fprintf(benchmark_file, "[\n");
}
void benchmark_end() {
    if (benchmark_file) {
        // Remove last comma
        fseek(benchmark_file, -2, SEEK_END);
        fprintf(benchmark_file, "]\n");
        fclose(benchmark_file);
    }
}

void benchmark_tick(int line, const char *file, const char *function) {
    if (benchmark_stack_ptr == benchmark_stack_end) {
        fprintf(stderr, "Benchmark stack overflow\n");
        abort();
    }
    benchmark_stack_ptr->start = get_timestamp_u();
    benchmark_stack_ptr->line = line;
    benchmark_stack_ptr->file = file;
    benchmark_stack_ptr->function = function;
    benchmark_stack_ptr++;
}
void benchmark_tock() {
    if (benchmark_stack_ptr == benchmark_stack) {
        fprintf(stderr, "Benchmark stack underflow\n");
        abort();
    }
    benchmark_stack_ptr--;
    benchmark_stack_ptr->end = get_timestamp_u();
    
    if (benchmark_file) {
        fprintf(benchmark_file, "{\"line\":%lu,\"file\":\"%s\",\"function\":\"%s\",\"time\":%lu},\n",
                benchmark_stack_ptr->line,
                benchmark_stack_ptr->file,
                benchmark_stack_ptr->function,
                benchmark_stack_ptr->end - benchmark_stack_ptr->start);
    }
}
