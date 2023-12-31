#ifndef __CAN_H__
#define __CAN_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

// CAN libraries (can_utils)
#include <linux/can.h>
#include <linux/can/raw.h>

typedef struct can_t {
	int sock;										 // socket fd
	char device[255];						 // name of device
	struct sockaddr_can address; // address of device

	uint64_t bytes_exchanged;
	bool opened;
} can_t;

/**
 * Sets device string (can0, vcan0)
 * Sets address pointer
 */
void can_init(can_t *can, const char *device);

/**
 * Returns if the socket is opened
 */
bool can_is_open(can_t *can);

/**
 * Opens device updating address,
 *
 * return socket fd, -1 if error
 */
int can_open_socket(can_t *can);

/**
 * Closes the can socket
 *
 * return true if close was successfull
 */
bool can_close_socket(can_t *can);

/**
 * Returns device name
 */
const char *can_get_device(can_t *can);

/**
 * @brief Get the Bytes Sent and received
 *
 */
uint64_t can_get_bytes_exchanged(can_t *can);

/**
 * Sends an array of bytes
 *
 * @param can pointer to struct can_t
 * @param id message id
 * @param data array of bytes
 * @param len num of bytes to be sent (0~8)
 * return success
 */
int can_send(can_t *can, uint16_t id, uint8_t *data, uint8_t len);

/**
 * Receive a can frame from device
 *
 * @param frame pointer of struct that will be filled
 * return success
 */
int can_receive(can_t *can, struct can_frame *frame);

/**
 * Setup filters so select id that can be received
 *
 * @param filter struct filled (id, mask)
 * return success
 */
int can_set_filters(can_t *can, struct can_filter *filter);

#endif // __CAN_H__