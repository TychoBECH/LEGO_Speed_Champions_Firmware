/* 
 * File:   io_driver.c
 * Author: Tycho Kropf
 * Created on: 2024-12-31
 *
 * Description:
 * This file contains the implementation of the IO driver for handling GPIO pins. 
 * It defines initialization, deinitialization, and runtime control functions for
 * configuring pin directions and reading/writing pin states. The design uses a 
 * struct-based approach to encapsulate pin-specific properties and functions, 
 * enabling flexibility and modularity.
 *
 * Revision History:
 * Version 0.0.1: 
 *   - Initial implementation with basic IO functionality.
 *   - Includes support for pin initialization, direction setting, value writing, 
 *     and value reading.
 */

#include "io_driver.h"
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

void IO_Init(void){
	//Port A
	LATA = 0x00; //-> Output latch register
	TRISA = 0b00011000; //Tristate register 1 = input
	ANSELA = 0xFF; //Analog select register 1 = Analog input
	WPUA = 0x00; //Wak pull up register 0 = disabled
	INLVLA = 0xFF; //input level setting 1 = standard levels are used
	SLRCONA = 0xFF; //Slew rate controll  1 = slew rate is limited
	ODCONA = 0x00; //Open drain controll 0 = Push Pull opperation
	
	//Port B
	LATB = 0x00; //-> Output latch register
	TRISB = 0b11001011; //Tristate register 1 = input
	ANSELB = 0xFF; //Analog select register 1 = Analog input
	WPUB = 0x00; //Wak pull up register 0 = disabled
	INLVLB = 0xFF; //input level setting 1 = standard levels are used
	SLRCONB = 0xFF; //Slew rate controll  1 = slew rate is limited
	ODCONB = 0x00; //Open drain controll 0 = Push Pull opperation
	
	RB1I2C = 0x00; //Pin specific I2C Settings
	RB2I2C = 0x00;
	
	//Port C
	LATC = 0x00; //-> Output latch register
	TRISC = 0b00011100; //Tristate register 1 = input
	ANSELC = 0xFF; //Analog select register 1 = Analog input
	WPUC = 0x00; //Wak pull up register 0 = disabled
	INLVLC = 0xFF; //input level setting 1 = standard levels are used
	SLRCONC = 0xFF; //Slew rate controll  1 = slew rate is limited
	ODCONC = 0x00; //Open drain controll 0 = Push Pull opperation
	
	RC3I2C = 0x00;
	RC4I2C = 0x00;
	
	//Port E
	LATE = 0x00; //-> Output latch register
	TRISE = 0xFF; //Tristate register 1 = input
	WPUE = 0x00; //Wak pull up register 0 = disabled
	INLVLE = 0xFF; //input level setting 1 = standard levels are used
}

void IO_Deinit(void){
	//Port A
	//PORTA = 0x00; -> No need to be set is the read register
	LATA = 0x00; //-> Output latch register
	TRISA = 0xFF; //Tristate register 1 = input
	ANSELA = 0xFF; //Analog select register 1 = Analog input
	WPUA = 0x00; //Wak pull up register 0 = disabled
	INLVLA = 0xFF; //input level setting 1 = standard levels are used
	SLRCONA = 0xFF; //Slew rate controll  1 = slew rate is limited
	ODCONA = 0x00; //Open drain controll 0 = Push Pull opperation
	
	//Port B
	LATB = 0x00; //-> Output latch register
	TRISB = 0xFF; //Tristate register 1 = input
	ANSELB = 0xFF; //Analog select register 1 = Analog input
	WPUB = 0x00; //Wak pull up register 0 = disabled
	INLVLB = 0xFF; //input level setting 1 = standard levels are used
	SLRCONB = 0xFF; //Slew rate controll  1 = slew rate is limited
	ODCONB = 0x00; //Open drain controll 0 = Push Pull opperation
	
	RB1I2C = 0x00; //Pin specific I2C Settings
	RB2I2C = 0x00;
	
	//Port C
	LATC = 0x00; //-> Output latch register
	TRISC = 0xFF; //Tristate register 1 = input
	ANSELC = 0xFF; //Analog select register 1 = Analog input
	WPUC = 0x00; //Wak pull up register 0 = disabled
	INLVLC = 0xFF; //input level setting 1 = standard levels are used
	SLRCONC = 0xFF; //Slew rate controll  1 = slew rate is limited
	ODCONC = 0x00; //Open drain controll 0 = Push Pull opperation
	
	RC3I2C = 0x00;
	RC4I2C = 0x00;
	
	//Port E
	LATE = 0x00; //-> Output latch register
	TRISE = 0xFF; //Tristate register 1 = input
	WPUE = 0x00; //Wak pull up register 0 = disabled
	INLVLE = 0xFF; //input level setting 1 = standard levels are used
}

void IO_SetPinDirection(uint8_t pin, bool direction){
	//Calculate in which register to work
	uint16_t base_Address = 0x12;
	uint8_t register_offset = pin / 8;
	uint8_t bit_offset = pin%8;
	
	//Build pointer to register
	volatile uint8_t* ptr = (volatile uint8_t*)(base_Address+register_offset);
	//read modify write
	uint8_t buffer = *ptr;
	buffer = buffer & (~(1<<bit_offset));//clears selected bit
	buffer = buffer | ((uint8_t)direction<<bit_offset);
	*ptr = buffer;	
}

void IO_WritePin(uint8_t pin, bool value){
	//Calculate in which register to work
	uint16_t base_Address = 0x18;
	uint8_t register_offset = pin / 8;
	uint8_t bit_offset = pin%8;
	
	//Build pointer to register
	volatile uint8_t* ptr = (volatile uint8_t*)(base_Address+register_offset);
	//read modify write
	uint8_t buffer = *ptr;
	buffer = buffer & (~(1<<bit_offset));//clears selected bit
	buffer = buffer | ((uint8_t)value<<bit_offset);
	*ptr = buffer;		
}

bool IO_ReadPin(uint8_t pin){
	//Calculate in which register to work
	uint16_t base_Address = 0xC;
	uint8_t register_offset = pin / 8;
	uint8_t bit_offset = pin%8;
	
	//Build pointer to register
	volatile uint8_t* ptr = (volatile uint8_t*)(base_Address+register_offset);
	//read modify write
	uint8_t buffer = *ptr;
	buffer = buffer & (1<<bit_offset);//keep selected bit
	
	return(bool)buffer;
}
