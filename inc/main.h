#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#include "inc/can.h"
#include "inc/data.h"
#include "inc/can_messages.h"

#include "lib/can/lib/primary/primary_network.h"
#include "lib/can/lib/primary/primary_watchdog.h"
#include "lib/can/lib/secondary/secondary_network.h"
#include "lib/can/lib/secondary/secondary_watchdog.h"
#include "lib/can/lib/simulator/simulator_network.h"

#include "exported/Slip_Control/SlipV2.h"
#include "exported/Traction_Control/Torque.h"
#include "exported/Velocity_Estimation/Velocity_Estimation.h"

bool running;
can_t can[CAN_SOCKET_COUNT];

can_data_t can_data;

DW_Torque torque_rtDW;
RT_MODEL_Torque torque_model;

DW_Velocity_Estimation ve_rtDW;
RT_MODEL_Velocity_Estimation ve_model;

char SlipError;
// DW_SlipV2 slip_rtDW;
RT_MODEL_SlipV2 slip_model;

bool init_model(void);
void ve_model_set_data(can_data_t *can_data);
void torque_model_set_data(can_data_t *can_data);
void slip_model_set_data(can_data_t *can_data);

// CAN thread
bool kill_can_thread;
pthread_mutex_t model_mutex;
pthread_t can_threads[CAN_SOCKET_COUNT];

void can_thread(can_socket_t socket);
void can_send_data();
void sig_handler(int signo);

#endif // __MAIN_H__