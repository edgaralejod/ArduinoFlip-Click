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
// Additional Comments: Documentation for every method is provided in the 
//                      cpp file. For new releases I want to add a generic
//                      Serial port object. For now it uses the Serial3 in 
//                      an arduino due compatible board (Flip&Click-Mikroe).
//////////////////////////////////////////////////////////////////////////////////
#ifndef _GPRS_LIB_H_
#define _GPRS_LIB_H_

#include "arduino.h"

#define ERROR_STATUS 1
#define SUCCESS_STATUS 2
#define TIME_OUT_STATUS 3

class QuectelM95GPRS
{
  public:
    QuectelM95GPRS(uint32_t baud_rate, uint8_t power_key);
    void begin( uint8_t retries  );
    void flush( void );
    String getImei( unsigned long timeOut );
    uint8_t getQualityOfService( unsigned long timeOut );
    uint8_t connectToGPRS( unsigned long timeOut, uint8_t retries  );   
    bool isGPRSConnected( void );
    uint8_t HTTPpost(String url, String data, unsigned long timeOut, uint8_t retries  ); 
    uint8_t selectEcho (bool on_or_off, unsigned long timeOut, uint8_t retries);  
  private:
    uint32_t _GPRS_baud_rate;
    uint8_t _GPRS_power_key;
    uint8_t sendCommand( String atCommand, String response1, String response2, unsigned long timeOut);
    uint8_t sendCommand( String atCommand, String response, unsigned long timeOut ); 
    String sendCommand( String atCommand, unsigned long timeOut );   
};
#endif
