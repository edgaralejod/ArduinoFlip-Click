//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Edgar Duarte
//
// Create Date: 
// Design Name: 
// Module Name:  
// Project Name:  IoT low Cost Gateway.
// Target Devices: Atmel ATSAM32X8E. (Using Flip&Click development board
//                                    by Mikroelectronica).
//                                    http://www.mikroe.com/flip-n-click/).
// Tool Versions: Arduino 1.6.7 Hourly Build.
//               
// Description: Header file for the GPRS library using the Quectel M95
//              GSM module.
//
// Dependencies:  Arduino.h 
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////
#ifndef _IOTDEFS_H_
#define _IOTDEFS_H_
#include "flip_click_defs.h"
#define TRUE 1
#define FALSE 0
#define LEDA 64
//Inputs and Outputs definitions.
#define DIG_INPUT1 2
#define DIG_INPUT2 3
#define DIG_INPUT3 5
#define DIG_INPUT4 5
#define DIG_INPUT5 6
#define DIG_INPUT6 7
#define AN_INPUT1 A0
#define AN_INPUT2 A1
#define AN_INPUT3 A2
#define AN_INPUT4 A3
#define AN_INPUT5 A4
#define AN_INPUT6 A5
#define DIG_OUT1 8
#define DIG_OUT2 9
#define DIG_OUT3 10
#define DIG_OUT4 11
#define DIG_OUT5 12
#define DIG_OUT6 13 
//Definitions for state machine
#define INITIALIZATION 0
#define CONNECTING_STATE 1
#define CONNECTED_STATE 2
#define RETRY_CONNECTION 3
//Definitions for the Flash memory
#define _SERIAL_FLASH_CMD_RDID  0x9F // 25P80
#define _SERIAL_FLASH_CMD_READ  0x03
#define _SERIAL_FLASH_CMD_WRITE 0x02
#define _SERIAL_FLASH_CMD_WREN  0x06
#define _SERIAL_FLASH_CMD_RDSR  0x05
#define _SERIAL_FLASH_CMD_ERASE 0xC7  // 25P80
#define _SERIAL_FLASH_CMD_EWSR  0x06  // 25P80
#define _SERIAL_FLASH_CMD_WRSR  0x01
#define _SERIAL_FLASH_CMD_SER   0xD8   //25P80 
#define FLASH_CS D_CS
#define GPRS_PWR B_RST
#define SCREEN_ADD 0X3C
#endif
