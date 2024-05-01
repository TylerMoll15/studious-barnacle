/*
 * Scheduler.c
 *
 *  Created on: Jan 29, 2024
 *      Author: tyler
 */
#include "Scheduler.h"

static uint32_t scheduledEvents;

uint32_t getScheduledEvents(){
    return scheduledEvents;
}

void addSchedulerEvent(uint32_t event_number){
    scheduledEvents |= event_number;
}

void removeSchedulerEvent(uint32_t event_number){
    scheduledEvents &= ~event_number;
}
