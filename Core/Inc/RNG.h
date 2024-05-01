/*
 * RNG.h
 *
 *  Created on: Apr 28, 2024
 *      Author: tyler
 */

#ifndef INC_RNG_H_
#define INC_RNG_H_
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_rng.h"
#include <stdint.h>
#include <stdbool.h>

// set IE bit in RNG_CR reg

// enable rng by setting RNGEN bit in RNG_CR

// check no error occurred SEIS and CEIS bits should be 0 in RNG_SR reg

// check Random number is ready DRDY bit is 1 in the RNG_SR reg

// RNG_DR can now be read


void RNG_Init();
uint32_t Get_Random_Number();


#endif /* INC_RNG_H_ */
