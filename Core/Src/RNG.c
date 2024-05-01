#include "RNG.h"

/*
 * RNG.c
 *
 *  Created on: Apr 28, 2024
 *      Author: tyler
 */

void RNG_Init(){
    __HAL_RCC_RNG_CLK_ENABLE();
    LL_RNG_Enable(RNG);
    LL_RNG_EnableIT(RNG);
}

uint32_t Get_Random_Number(){
    bool RNG_error_enabled = LL_RNG_IsActiveFlag_CEIS(RNG) || LL_RNG_IsActiveFlag_SEIS(RNG);

    if(!RNG_error_enabled && LL_RNG_IsActiveFlag_DRDY(RNG)){
        return LL_RNG_ReadRandData32(RNG);
    }

    return -1; //not ready for reading
}
