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
#define USE_TLM_VELOCITY_ESTIMATION 1
#define USE_INVERTERS_SPEED 1

#define BENCHMARK 0
#define RUN_FREQUENCY 200								// Hz
#define LOOP_DURATION 1000000 / RUN_FREQUENCY								// us
#define SOC_UPDATE_FREQUENCY 50					// Hz
#define CHECK_CAN_MESSAGES_FREQUENCY 10 // Hz

#define REGEN_ENABLE 1
#define REGEN_BRAKE_FRONT_ON_THRESHOLD 1.5f // enables regen over this value
#define REGEN_THROTTLE_ON_THRESHOLD 0.05f		// enables regen under this value
#define REGEN_SOC_ON_THRESOLD 0.95f					// enables when under this value
#define REGEN_BRAKE_HYSTERESIS 0.5f
#define REGEN_THROTTLE_HYSTERESYS 0.02f
#define REGEN_SOC_HYSTERESYS 0.01f
static_assert(REGEN_THROTTLE_ON_THRESHOLD > REGEN_THROTTLE_HYSTERESYS);
static_assert(REGEN_BRAKE_FRONT_ON_THRESHOLD > REGEN_BRAKE_HYSTERESIS);

#define SLIP_PEAK 60.0
#define SLIP_SPEED_CUTOFF 3.0
#define SLIP_START_TORQUE 20.0
#define STEER_CONVERSION_FACTOR 4.588f
#define WHEEL_RADIUS 0.2035f

#define TV_KUS (0.000f)
#define TV_PID_KP (150.0f)
#define TV_PID_KI (300.0f)

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
