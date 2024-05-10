#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

extern "C" {
#include "inc/can.h"
#include "inc/data.h"
#include "inc/can_messages.h"

#include "lib/can/lib/primary/primary_network.h"
#include "lib/can/lib/primary/primary_watchdog.h"
#include "lib/can/lib/secondary/secondary_network.h"
#include "lib/can/lib/secondary/secondary_watchdog.h"
#include "lib/can/lib/simulator/simulator_network.h"

#include "exported/Regen/Regen.h"
#include "exported/Slip_Control/SLIP.h"
#include "exported/Traction_Control/TV.h"
}

bool running;
can_t can[CAN_SOCKET_COUNT];

double u_bar;

can_data_t can_data;

DW_TV torque_rtDW;
RT_MODEL_TV torque_model;

DW_SLIP slip_rtDW;
RT_MODEL_SLIP slip_model;

RT_MODEL_Regen regen_model;

bool init_model(void);
double torque_max(can_data_t *can_data);
void velocity_estimation(can_data_t *can_data, double *u_bar);
void torque_model_set_data(can_data_t *can_data);
void regen_model_set_data(can_data_t *can_data);
void slip_model_set_data(can_data_t *can_data);

// CAN thread
bool kill_can_thread;
pthread_mutex_t model_mutex;
pthread_t can_threads[CAN_SOCKET_COUNT];

void *can_thread(void *);
void can_send_data();
void sig_handler(int signo);

#endif // __MAIN_H__
