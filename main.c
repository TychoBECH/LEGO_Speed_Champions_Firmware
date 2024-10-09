 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

//Define States used by the state machine
#define state_idel 0
#define state_drive_forward 1
#define state_turn_left 2
#define state_turn_right 3
#define state_drive_backward 4

/*
    Main application
*/

uint8_t state = state_idel;

uint8_t read_command(void);

int main(void)
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
	IO_RA5_SetHigh();
	
	__delay_ms(50);
	
	uint8_t command = 0;
	//Use WASD as drive command set 
	//		W
	//	    ¦
	//  A -- -- D
	//      ¦
	//      S

	
    while(1)
    {
		switch( state){
			case state_idel:
				IO_RA0_SetLow();
				IO_RA6_SetLow();
				IO_RC1_SetLow();
				IO_RB1_SetLow();
				IO_RA7_SetLow();
				IO_RA1_SetLow();
				IO_RC0_SetLow();
				IO_RC7_SetLow();
				
				if(command == 0x57){ //HEX value of "W"
					state = state_drive_forward;
				}
				if(command == 0x41){ //HEX value of "A"
					state = state_turn_left;
				}
				if (command == 0x44) { //HEX value of "D"
					state = state_turn_right;
				}
				if (command == 0x53) { //HEX value of "S"
					state = state_drive_backward;
				}
				break;
			case state_drive_forward:
				IO_RB1_SetHigh();
				IO_RC1_SetHigh();
				IO_RA6_SetHigh();
				IO_RA0_SetHigh();
				
				__delay_ms(100);
				state = state_idel;
				break;
			case state_turn_left:
				//right forward M1 and M4
				IO_RB1_SetHigh();
				IO_RC1_SetHigh();
				
				//left backward M2 and M3
				IO_RA7_SetHigh();
				IO_RA1_SetHigh();
				
				__delay_ms(100);
				state = state_idel;
				break;
			case state_turn_right:
				//right backward M1 and M4
				IO_RC7_SetHigh();
				IO_RC0_SetHigh();
				
				//left forward M2 and M3
				IO_RA6_SetHigh();
				IO_RA0_SetHigh();
				
				__delay_ms(100);
				state = state_idel;
				break;
			case state_drive_backward: 
				IO_RC7_SetHigh();
				IO_RC0_SetHigh();
				IO_RA7_SetHigh();
				IO_RA1_SetHigh();
				
				__delay_ms(100);
				state = state_idel;
				break;
			default:
				
				break;
		}
		NOP();
		
		//Read back command from UART
		command = read_command();
		
		__delay_ms(1);
    }    
}

uint8_t read_command(void){
	if(EUSART1_IsRxReady()){
		uint8_t receaved = EUSART1_Read();
		if (receaved > 32 ) {//Filter for actual Text insted of controll caracters
			return receaved;
		}
	}
	return 0;
}