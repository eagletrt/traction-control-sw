#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "inc/can.h"
#include "inc/data.h"
#include "inc/can_messages.h"

#include "exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.h"

can_t can[CAN_SOCKET_COUNT];

DW_Velocity_Estimation rtDW;
RT_MODEL_Velocity_Estimation model;
ve_data_t ve_data;

bool init_model(void);
void model_set_data(ve_data_t *data);

// CAN thread
bool kill_can_thread;
pthread_mutex_t model_mutex;
pthread_t can_threads[CAN_SOCKET_COUNT];

void can_thread(can_socket_t socket);

#endif // __MAIN_H__