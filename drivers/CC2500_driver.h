/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CC2500_DRIVER_H
#define	CC2500_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "mssp_driver.h"
// TODO Insert appropriate #include <>

//<editor-fold desc="CC2500 State Definitions">
#define STATE_IDLE 0b000
#define STATE_RX 0b001
#define STATE_TX 0b010
#define STATE_FSTXON 0b011
#define STATE_CALIBRATE 0b100
#define STATE_SETTLING 0b101
#define STATE_RXFIFO_OVERFLOW 0b110
#define STATE_TXFIFO_UNDERFLOW 0b110
//</editor-fold>

//<editor-fold desc="CC2500 Register Definitions">
#define CC2500_IOCFG2   0x00
#define CC2500_IOCFG1   0x01
#define CC2500_IOCFG0   0x02
#define CC2500_FIFOTHR  0x03
#define CC2500_SYNC1    0x04
#define CC2500_SYNC0    0x05
#define CC2500_PKTLEN   0x06
#define CC2500_PKTCTRL1 0x07
#define CC2500_PKTCTRL0 0x08
#define CC2500_ADDR     0x09
#define CC2500_CHANNR   0x0A
#define CC2500_FSCTRL1  0x0B
#define CC2500_FSCTRL0  0x0C
#define CC2500_FREQ2    0x0D
#define CC2500_FREQ1    0x0E
#define CC2500_FREQ0    0x0F
#define CC2500_MDMCFG4  0x10
#define CC2500_MDMCFG3  0x11
#define CC2500_MDMCFG2  0x12
#define CC2500_MDMCFG1  0x13
#define CC2500_MDMCFG0  0x14
#define CC2500_DEVIATN  0x15
#define CC2500_MCSM2    0x16
#define CC2500_MCSM1    0x17
#define CC2500_MCSM0    0x18
#define CC2500_FOCCFG   0x19
#define CC2500_BSCFG    0x1A
#define CC2500_AGCCTRL2 0x1B
#define CC2500_AGCCTRL1 0x1C
#define CC2500_AGCCTRL0 0x1D
#define CC2500_WOREVT1  0x1E
#define CC2500_WOREVT0  0x1F
#define CC2500_WORCTRL  0x20
#define CC2250_FREND1   0x21
#define CC2250_FREND0   0x22
#define CC2500_FSCAL3   0x23
#define CC2500_FSCAL2   0x24
#define CC2500_FSCAL1   0x25
#define CC2500_FSCAL0   0x26
#define CC2500_RCCTRL1  0x27
#define CC2500_RCCTRL0  0x28
#define CC2500_FSTEST   0x29
#define CC2500_PTEST    0x2A
#define CC2500_AGCTEST  0x2B
#define CC2500_TEST2    0x2C
#define CC2500_TEST1    0x2D
#define CC2500_TEST0    0x2E
//</editor-fold>

//<editor-fold desc="CC2500 R/W and burst flags">
#define CC2500_SingleWrite  0x00
#define CC2500_BurstWrite   0x80
#define CC2500_SingleRead   0x40
#define CC2500_BurstRead    0xC0
//</editor-fold>

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
void CC2500_init(void);

void CC2500_WriteRegister(uint8_t reg, uint8_t value);

uint8_t CC2500_ReadRegister(uint8_t reg);

uint8_t CC2500_TransferRegister(uint8_t reg, uint8_t value);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CC2500_DRIVER_H */

