/*
 * Scheduler.h
 *
 *  Created on: Jan 29, 2024
 *      Author: tyler
 */
#include <stdint.h>

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t event_number);
void removeSchedulerEvent(uint32_t event_number);

#define LED_TOGGLE_EVENT 0x1
#define LED_DELAY_EVENT 0x1 << 1
#define POLL_BUTTON_EVENT 0x1 << 2
#define GET_GYRO_TEMP_EVENT 0x1 << 3
#define GET_GYRO_AXIS_DATA_EVENT 0x1 << 4
#define REBOOT_GYRO_EVENT 0x1 << 5
#define RESET_GAME_SCREEN_EVENT 0x1 << 6

#endif /* SCHEDULER_H_ */
