#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "inc/can.h"
#include "inc/can_messages.h"

#include "exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.h"

can_t can[CAN_SOCKET_COUNT];

DW rtDW;
RT_MODEL model;

bool init_model(void);

// CAN thread
bool kill_can_thread;
pthread_mutex_t model_mutex;
pthread_t can_thread_id[CAN_SOCKET_COUNT];

void can_thread(can_socket_t socket);

#endif // __MAIN_H__