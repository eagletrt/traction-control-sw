#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "inc/can.h"
#include "inc/data.h"
#include "inc/can_messages.h"

#include "lib/can/lib/primary/primary_network.h"
#include "lib/can/lib/primary/primary_watchdog.h"
#include "lib/can/lib/secondary/secondary_network.h"
#include "lib/can/lib/secondary/secondary_watchdog.h"

#include "exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.h"

can_t can[CAN_SOCKET_COUNT];

DW_All0 all_rtDW;
RT_MODEL_All0 all_model;
DW_Velocity_Estimation ve_rtDW;
RT_MODEL_Velocity_Estimation ve_model;
ve_data_t ve_data;
all_data_t all_data;

bool init_model(void);
void ve_model_set_data(ve_data_t *ve_d);
void all_model_set_data(all_data_t *all_d);

// CAN thread
bool kill_can_thread;
pthread_mutex_t model_mutex;
pthread_t can_threads[CAN_SOCKET_COUNT];

void can_thread(can_socket_t socket);
void can_send_data();

#endif // __MAIN_H__