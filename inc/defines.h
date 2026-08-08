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

#define BENCHMARK 0
#define RUN_FREQUENCY 200.0										// Hz
#define LOOP_DURATION 1000000 / RUN_FREQUENCY // us
#define SOC_UPDATE_FREQUENCY 50								// Hz
#define CHECK_CAN_MESSAGES_FREQUENCY 10				// Hz

#define MAX_TORQUE (100.0)
#define MAX_BRAKE_BAR (10.0)
#define IDEAL_BRAKE_BALANCE (0.8) // 0.8 front

#define HV_SOC_LAST_STATE_FILENAME ".hv_soc_state.txt"
#define LV_SOC_LAST_STATE_FILENAME ".lv_soc_state.txt"

// MACRO FUNCTIONS
#define eprintf(m, ...) fprintf(stderr, "\033[1;31m*** ERROR: \033[0m" m, ##__VA_ARGS__)

// #define wprintf(m, ...) fprintf(stderr, "\033[1;33m*** WARNING: \033[0m" m, ##__VA_ARGS__)

#define UNUSED(x) (void)(x)

#define INV_MAX_SPEED 8000.f // MOT_RPM_LIMIT_REAL

static uint64_t get_timestamp_u() {
	static struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}

// static bool equal_d(double a, double b) { return fabs(a - b) < 0.0001; }

#endif // DEFINES_H
