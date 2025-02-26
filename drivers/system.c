/* 
 * File:   system.c
 * Author: Tycho Kropf
 * Created on: 2024-12-31
 *
 * Description:
 * TODO
 *
 * Revision History:
 * TODO
 * Version 0.0.1: 
 *
 */

#include "io_driver.h"
#include "pps_driver.h"
#include "mssp_driver.h"
#include "CC2500_driver.h"

void System_Init(void) {
	IO_Init();
	PPS_Init();
	MSSP1_SPI_Init();
}

