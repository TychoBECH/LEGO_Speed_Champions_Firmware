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
 * File:   mpps_driver.h
 * Author: Tycho Kropf  
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MSSP_DRIVER_H
#define	MSSP_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include "io_driver.h" //-> Requirement to set and reset CS pin


// ******** SPI Functions for MSSP1 ********

#define CS_Pin IO_RC1

/**
    <p><b>Function prototype:</b></p>
    void MSSP1_InitSPI(void);

    <p><b>Summary:</b></p>
    Initializes MSSP1 in SPI mode.

    <p><b>Description:</b></p>
    Configures MSSP1 for SPI communication with default settings such as clock polarity,
    clock phase, and clock speed.

    <p><b>Precondition:</b></p>
    None.

    <p><b>Parameters:</b></p>
    None.

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    MSSP1_InitSPI();
    </code>

    <p><b>Remarks:</b></p>
    Call this function before using any MSSP1 SPI operations.
 */
void MSSP1_SPI_Init(void);

void MSSP1_DeInit(void);

/**
    <p><b>Function prototype:</b></p>
    void MSSP1_WriteSPI(uint8_t data);

    <p><b>Summary:</b></p>
    Sends a byte of data via MSSP1 in SPI mode.

    <p><b>Description:</b></p>
    Transmits a single byte of data over the SPI bus using MSSP1.

    <p><b>Precondition:</b></p>
    MSSP1 must be initialized in SPI mode using MSSP1_InitSPI.

    <p><b>Parameters:</b></p>
    <ul>
        <li>uint8_t data - The byte of data to send.</li>
    </ul>

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    MSSP1_WriteSPI(0xA5);
    </code>

    <p><b>Remarks:</b></p>
    Ensure the SPI bus is ready before calling this function.
 */
void MSSP1_SPI_WriteByte(uint8_t data);

void MSSP1_SPI_WriteNByte(uint8_t *data_array, uint8_t size);

/**
 * <p><b>Function prototype:</b></p>
 * uint8_t MSSP1_SPI_TransferByte(uint8_t data);
 * 
 * <p><b>Summary:</b></p>
 * Transfers a single byte over the SPI interface using MSSP1.
 * 
 * <p><b>Description:</b></p>
 * Sends a single byte of data over the SPI interface (Master Synchronous Serial Port 1)
 * and simultaneously receives a byte of data from the SPI bus. This operation is
 * synchronous, meaning the function waits for the SPI transfer to complete before
 * returning the received data.
 * 
 * <p><b>Precondition:</b></p>
 * The MSSP1 SPI module must be initialized and configured for SPI communication.
 * 
 * <p><b>Parameters:</b></p>
 * <ul>
 *   <li><b>data</b> - The byte to be transmitted over the SPI bus.</li>
 * </ul>
 * 
 * <p><b>Returns:</b></p>
 * <ul>
 *   <li>The byte received from the SPI bus during the transfer.</li>
 * </ul>
 * 
 * <p><b>Example:</b></p>
 * <code>
 * uint8_t receivedData;
 * receivedData = MSSP1_SPI_TransferByte(0x55); // Send 0x55 and receive a byte
 * </code>
 * 
 * <p><b>Remarks:</b></p>
 * <ul>
 *   <li>Ensure the SPI clock, polarity, and phase are configured properly for the 
 *       target SPI slave device before calling this function.</li>
 *   <li>The function will block execution until the SPI transfer is complete.</li>
 *   <li>Use this function when both sending and receiving data over SPI are required.
 *       For write-only or read-only operations, other specialized functions may be more efficient.</li>
 * </ul>
 */
uint8_t MSSP1_SPI_TransferByte(uint8_t data);

uint8_t MSSP1_SPI_TransferNByte(uint8_t *buffer,  uint8_t size);

/**
    <p><b>Function prototype:</b></p>
    void MSSP1_SPI_Start(void);

    <p><b>Summary:</b></p>
    Initializes and starts the MSSP1 SPI communication.

    <p><b>Description:</b></p>
    Configures and enables the SPI module (Master Synchronous Serial Port 1) for data transfer. This function prepares the SPI peripheral to initiate communication with SPI slave devices by setting the required settings such as clock polarity, phase, and enabling the SPI module.

    <p><b>Precondition:</b></p>
    The necessary SPI configurations, such as clock settings and slave device configurations, should be done prior to calling this function.

    <p><b>Parameters:</b></p>
    <ul>
        <li>None - This function takes no parameters.</li>
    </ul>

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    MSSP1_SPI_Start(); // Start the SPI communication on MSSP1
    </code>

    <p><b>Remarks:</b></p>
    <ul>
        <li>This function must be called before any SPI transfers can be made.</li>
        <li>Ensure proper configuration of SPI mode (clock polarity and phase) before starting the communication.</li>
        <li>The function will enable the SPI module and prepare the bus for data transmission.</li>
    </ul>
 */
void MSSP1_SPI_Start(void);

/**
    <p><b>Function prototype:</b></p>
    void MSSP1_SPI_Stop(void);

    <p><b>Summary:</b></p>
    Disables and stops the MSSP1 SPI communication.

    <p><b>Description:</b></p>
    Disables the SPI module and disables the SPI interface, effectively stopping communication over the SPI bus. This function ensures the proper shutdown of the SPI module by disabling the necessary control bits and freeing up the bus for other uses.

    <p><b>Precondition:</b></p>
    The SPI communication must have been started with the `MSSP1_SPI_Start()` function before calling this function.

    <p><b>Parameters:</b></p>
    <ul>
        <li>None - This function takes no parameters.</li>
    </ul>

    <p><b>Returns:</b></p>
    None.

    <p><b>Example:</b></p>
    <code>
    MSSP1_SPI_Stop(); // Stop the SPI communication on MSSP1
    </code>

    <p><b>Remarks:</b></p>
    <ul>
        <li>This function should be used to stop communication after the necessary data transfers are completed.</li>
        <li>After stopping the SPI, the bus is no longer active, and the device can be reconfigured or used for other purposes.</li>
        <li>Make sure no ongoing SPI transfers are happening before calling this function to avoid errors.</li>
    </ul>
 */
void MSSP1_SPI_Stop(void);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* MSSP_DRIVER_H */

