#ifndef __MAIN_H__
#define __MAIN_H__

#include "external/soc/core/src/soc/soc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

extern "C" {
#include "inc/can.h"
#include "inc/data.h"
#include "inc/can_messages.h"

#include "external/can/lib/primary/primary_network.h"
#include "external/can/lib/primary/primary_watchdog.h"
}

bool running;
can_t can[CAN_SOCKET_COUNT];

can_data_t gl_can_data;
can_received_bitset_t can_received;
bool received_controls_data;
bool received_hv_soc_data;
bool received_lv_soc_data;

SOC hvSOC;
SOC lvSOC;

void check_received_messages(can_received_bitset_t *bitset);

bool load_soc_state(const char *path, Eigen::VectorXd &state);
bool save_soc_state(const char *path, const Eigen::VectorXd &state);

// CAN thread
bool kill_can_thread;
pthread_mutex_t model_mutex;
pthread_t can_threads[CAN_SOCKET_COUNT];

void *can_thread(void *);
void can_send_data(can_data_t can_data);
void sig_handler(int signo);

#endif // __MAIN_H__
