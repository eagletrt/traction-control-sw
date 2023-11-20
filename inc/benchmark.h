#ifndef BENCHMARK_H
#define BENCHMARK_H

#ifdef __cplusplus
extern "C" {
#endif


// Use tick and tock macros to push and pop the current time in the stack
// each tick push a also the __LINE__ and __FILE__ macros and __PRETTY_FUNCTION__ if available
// each tock pop the last tick

#define BENCHMARK_MAX_DEPTH 1000
#define BENCHMARK_BATCH_SIZE 200

#if 1==BENCHMARK
#define BENCHMARK_START() benchmark_start()
#define BENCHMARK_END() benchmark_end()
#define BENCHMARK_TICK() benchmark_tick(__LINE__, __FILE__, __PRETTY_FUNCTION__)
#define BENCHMARK_TOCK() benchmark_tock()
#else
#define BENCHMARK_START()
#define BENCHMARK_END()
#define BENCHMARK_TICK()
#define BENCHMARK_TOCK()
#endif

void benchmark_tick(int line, const char *file, const char *function);
void benchmark_tock();

void benchmark_start();
void benchmark_end();

#ifdef __cplusplus
}
#endif
#endif // BENCHMARK_H