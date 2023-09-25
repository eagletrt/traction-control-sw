#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>

#include "inc/can.h"

#include "exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.h"

typedef enum {
	CAN_PRIMARY,
	CAN_SECONDARY,
	CAN_INVERTERS,

	CAN_NETWORK_COUNT
} can_network_t;

typedef struct {
	can_network_t network;
	struct can_frame frame;
} can_message_t;

DW rtDW;
RT_MODEL model;

bool model_init(void);

#endif // __MAIN_H__