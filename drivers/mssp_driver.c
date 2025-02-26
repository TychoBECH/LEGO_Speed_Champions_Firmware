/* 
 * File:   io_driver.c
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

#include "mssp_driver.h"

void MSSP1_SPI_Init(void) {
	SSP1ADD = 0x01; // SCk clock periode: ((n+1)*4)/Fosc -> 4MHz with FOSC=32MHz
	SSP1STAT = 0b01000000; //Set to use Mode 0 SCK idle low and sample on ring edge
	SSP1CON1 = 0b00101010;
	SSP1CON2 = 0b00000000;
	SSP1CON3 = 0b00010000;

	//Set CS IO high for idle high
	IO_WritePin(CS_Pin, true);
}

void MSSP1_DeInit(void) {
	SSP1ADD = 0x00;
	SSP1MSK = 0xFF;
	SSP1STAT = 0x00;
	SSP1CON1 = 0x00;
	SSP1CON2 = 0x00;
	SSP1CON3 = 0x00;
}

void MSSP1_SPI_WriteByte(uint8_t data) {
	SSP1BUF = data;
	while (!SSP1IF);
	SSP1IF = 0;
}

void MSSP1_SPI_WriteNByte(uint8_t *data_array, uint8_t size) {
	for (uint8_t count = 0; count <= size; count++) {
		SSP1BUF = data_array[count];
		while (!SSP1IF);
		SSP1IF = 0;
	}
}

uint8_t MSSP1_SPI_TransferByte(uint8_t data) {
	SSP1BUF = data;
	while (!SSP1IF);
	SSP1IF = 0;
	return SSP1BUF;
}

void MSSP1_SPI_TransferNByte(uint8_t *buffer, uint8_t size) {
	for (uint8_t count = 0; count <= size; count++) {
		SSP1BUF = buffer[count];
		while (!SSP1IF);
		SSP1IF = 0;
		buffer[count] = SSP1BUF;
	}
}

void MSSP1_SPI_Start(void) {
	IO_WritePin(CS_Pin, false);
}

void MSSP1_SPI_Stop(void) {
	IO_WritePin(CS_Pin, true);
}

