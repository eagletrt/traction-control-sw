// COMMON DEFINITIONS FILE
#ifndef DEFINES_H
#define DEFINES_H

// COMMON INCLUDES
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define SIMULATOR 0

#define BENCHMARK 0
#define RUN_FREQUENCY 500 // Hz

#define SLIP_PEAK 60.0
#define SLIP_SPEED_CUTOFF 3.0
#define SLIP_START_TORQUE 20.0
#define STEER_CONVERSION_FACTOR 4.588f
#define WHEEL_RADIUS 0.2035f

#define TV_KUF 0.001
#define TV_PID_KP 150.0
#define TV_PID_KI 300.0

// MACRO FUNCTIONS
#define eprintf(m, ...) fprintf(stderr, "\033[1;31m*** ERROR: \033[0m" m, ##__VA_ARGS__)

#define wprintf(m, ...) fprintf(stderr, "\033[1;33m*** WARNING: \033[0m" m, ##__VA_ARGS__)

#define UNUSED(x) (void)(x)

#define INV_MAX_SPEED 6500.f // MOT_RPM_LIMIT_REAL

static uint64_t get_timestamp_u() {
	static struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}

// static bool equal_d(double a, double b) { return fabs(a - b) < 0.0001; }

#endif // DEFINES_H
