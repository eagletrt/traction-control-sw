#ifndef __DATA_H__
#define __DATA_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	double hv_min_cell_voltage;
	double hv_total_current;
	double hv_mean_temp;
	double lv_min_cell_voltage;
	double lv_total_current;
	double lv_mean_temp;
} can_data_t;

typedef enum {
	CAN_REC_HV,
	CAN_REC_LV,
	CAN_REC_COUNT
} can_received_t;

typedef uint32_t can_received_bitset_t;

#define RECEIVED_HV_SOC_MASK (1 << CAN_REC_HV)
#define RECEIVED_LV_SOC_MASK (1 << CAN_REC_LV)

#define CAN_RECEIVED_ALL(value) (value & (CAN_REC_COUNT - 1))
#define CAN_RECEIVED_SET(value, bitset) value = value | (1 << bitset);
#define CAN_RECEIVED_CLEAR(value) value = 0;

#endif // __DATA_H__
