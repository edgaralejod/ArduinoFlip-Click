//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Edgar Duarte
//
// Create Date: 
// Design Name: 
// Module Name:  
// Project Name:  IoT low Cost Gateway.
// Target Devices: Atmel ATSAM32X8E. (Using Flip&Click development board
//                                    by Mikroelectronica
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
#include "gprs_lib.h"
#define _DEBUG_ //Uncomment to use Arduino serial port to debug.
/*********************************************************************************
*
* QuectelM95GPRS( uint32_t baud_rate, uint8_t power_key);
* Parameters:
*   Baud Rate to operate the Quectel M95 Radio.
* Returns:
*   Void
* Description:
*   Constructor for the QuectelM95 library.
*********************************************************************************/
QuectelM95GPRS::QuectelM95GPRS( uint32_t baud_rate, uint8_t power_key)
{
  _GPRS_baud_rate = baud_rate;
  _GPRS_power_key = power_key;
}
/*********************************************************************************
*
*  void QuectelM95GPRS::begin ( uint8_t retries );
*  Parameters:
*    retries: Number of times that the method will retry to get a sucess status.
*  Returns:
*     N/A
*  Description:
*
*********************************************************************************/
void QuectelM95GPRS::begin ( uint8_t retries )
{
  uint8_t flow_control = ERROR_STATUS;
  Serial3.begin(_GPRS_baud_rate);
  pinMode(_GPRS_power_key, OUTPUT);
  digitalWrite(_GPRS_power_key, LOW);
  delay(2500);
  digitalWrite(_GPRS_power_key, HIGH);
  delay(5000);
  while ( (retries--) && !(flow_control == SUCCESS_STATUS) )
  {
    flow_control = sendCommand("AT", "OK", 500);
  }
}
/*********************************************************************************
*
*  uint8_t QuectelM95GPRS::sendCommand( String commandToSend, String response1, 
*                                       String response2, unsigned long timeOut );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t QuectelM95GPRS::sendCommand( String commandToSend, String response1, 
                                     String response2, unsigned long timeOut )
{
  uint8_t returnStatus = ERROR_STATUS;
  unsigned long initTime = millis();
  unsigned long currentTime = 0;
  bool readyFlag = true;
  String readVal;
  Serial3.print(commandToSend);
  Serial3.write(0x0D);
  while (readyFlag)
  {
    currentTime = millis();
    if ( Serial3.available() > 0 )
    {
      readVal = Serial3.readString();
      readyFlag = false;
    }
    if ( (currentTime - initTime) > timeOut )
    {
      returnStatus = TIME_OUT_STATUS;
      readyFlag = false;
    }
  }
  if ( (readVal.indexOf(response1) > 0) &&
       (readVal.indexOf(response2) > 0)
     )
  {
    returnStatus = SUCCESS_STATUS;
  }
  else if ( readVal.indexOf("ERROR") > 0 )
  {
    returnStatus = ERROR_STATUS;
  }
  Serial3.flush();
#ifdef _DEBUG_
  Serial.print(readVal);
  Serial.println(returnStatus);
#endif
  return returnStatus;
}
/*********************************************************************************
*
*  uint8_t QuectelM95GPRS::sendCommand( String atCommand, String response, 
                                        unsigned long timeOut );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t QuectelM95GPRS::sendCommand( String atCommand, String response, 
                                     unsigned long timeOut )
{
  uint8_t returnStatus = ERROR_STATUS;
  unsigned long initTime = millis();
  unsigned long currentTime = 0;
  bool readyFlag = true;
  String readVal;
  Serial3.print(atCommand);
  Serial3.write(0x0D);
  while (readyFlag)
  {
    currentTime = millis();
    if ( (currentTime - initTime) > timeOut )
    {
      returnStatus = TIME_OUT_STATUS;
      readyFlag = false;
    }
    if ( Serial3.available() > 0 )
    {
      readVal = Serial3.readString();
      readyFlag = false;
    }
  }
  if (readVal.indexOf(response) > 0)
  {
    returnStatus = SUCCESS_STATUS;
  }
  else if ( readVal.indexOf("ERROR") > 0 )
  {
    returnStatus = ERROR_STATUS;
  }
  Serial3.flush();
#ifdef _DEBUG_
  Serial.print(readVal);
  Serial.println(returnStatus);
#endif
  return returnStatus;
}
/*********************************************************************************
*
*  String QuectelM95GPRS::sendCommand( String atCommand, unsigned long timeOut );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
String QuectelM95GPRS::sendCommand( String atCommand, unsigned long timeOut )
{

  unsigned long initTime = millis();
  unsigned long currentTime = 0;
  bool readyFlag = true;
  String readVal;
  Serial3.print(atCommand);
  Serial3.write(0x0D);
  while (readyFlag)
  {
    currentTime = millis();
    if ( Serial3.available() > 0 )
    {
      readVal = Serial3.readString();
      readyFlag = false;
    }
    if ( (currentTime - initTime) > timeOut )
    {
      readVal = "TIMEOUT";
      readyFlag = false;
    }
  }
  Serial3.flush();
#ifdef _DEBUG_
  Serial.print(readVal);
#endif
  return readVal;
}
/*********************************************************************************
*
*  void QuectelM95GPRS::flush( void );
*  Parameters:
*    N/A
*  Returns:
*    N/A
*  Description:
*
*********************************************************************************/
void QuectelM95GPRS::flush( void )
{
 Serial3.flush();
}
/*********************************************************************************
*
*  String QuectelM95GPRS::getImei( unsigned long timeOut );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
String QuectelM95GPRS::getImei( unsigned long timeOut )
{
  String gsmRadioIMEI;
  String trimmedIMEI;
  flush();
  selectEcho (false, 500, 5);      
  gsmRadioIMEI = sendCommand("AT+GSN", timeOut);
  if( !(gsmRadioIMEI.indexOf("TIMEOUT")>0 ) )
  {
    trimmedIMEI =gsmRadioIMEI.substring(2,17);
  }
  else
  {
    trimmedIMEI ="TIMEOUT";
  }
  selectEcho (true, 500, 5);
  return trimmedIMEI;
}
/*********************************************************************************
*
*  uint8_t QuectelM95GPRS::getQualityOfService( unsigned long timeOut );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t QuectelM95GPRS::getQualityOfService( unsigned long timeOut )
{
  uint8_t qualityOfService = 0;
  String response;
  String qualityOS;
  flush();
  selectEcho (false, 500, 5); 
  response = sendCommand("AT+CSQ", timeOut);
  if( !(response.indexOf("TIMEOUT")>0 ) )
  {
    qualityOS = response.substring(8,10);
    qualityOfService = qualityOS.toInt();
    if(qualityOfService>0 && qualityOfService <=7)
    {
      qualityOfService = 0;
    }
    else if(qualityOfService>8 && qualityOfService <=14)
    {
      qualityOfService = 1;
    }
    else if(qualityOfService>15 && qualityOfService <=21)
    {
      qualityOfService = 2;
    }
    else if(qualityOfService>=22)
    {
      qualityOfService = 3;
    }
    else
    {
      qualityOfService = 0;     
    }
  }
  else 
  {
    qualityOfService = 0;
  }
#ifdef _DEBUG_
  Serial.print(qualityOfService);
#endif
  selectEcho (true, 500, 5);
  return qualityOfService;

}
/*********************************************************************************
*
*  uint8_t QuectelM95GPRS::selectEcho ( bool on_or_off, 
                                        unsigned long timeOut, uint8_t retries );
*  Parameters:
*   retries: Number of times that the method will retry to get a sucess status.
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t QuectelM95GPRS::selectEcho ( bool on_or_off, 
                                     unsigned long timeOut, uint8_t retries )
{
  uint8_t flow_control = ERROR_STATUS;
  if( on_or_off )
  {
    while ( (retries--) && !(flow_control == SUCCESS_STATUS) )
    {
      flow_control = sendCommand("ATE1", "OK", 500);
    }
  }
  else
  {
    while ( (retries--) && !(flow_control == SUCCESS_STATUS) )
    {
      flow_control = sendCommand("ATE0", "OK", 500);
    }    
  }
  return flow_control;
}
/*********************************************************************************
*
*  uint8_t QuectelM95GPRS::connectToGPRS( unsigned long timeOut, uint8_t retries );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t QuectelM95GPRS::connectToGPRS( unsigned long timeOut, uint8_t retries )
{
  uint8_t returnStatus = ERROR_STATUS;
  uint8_t int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+CPIN?", "READY", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+CREG?", "1,1", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+CGATT?", "1", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QICSGP=1,\"wholesale\"", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIMUX=0", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIMODE=0", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIDNSIP=0", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIREGAPP", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIFGCNT=0", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIACT", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QILOCIP", ".", timeOut);
  }
  return returnStatus;
}
/*********************************************************************************
*
*  bool QuectelM95GPRS::isGPRSConnected ( void );
*  Parameters:
*    N/A
*  Returns:
*    True: If the module is connected to a GPRS context.
*    False: If the module is not connected.
*  Description:
*    N/A
*
*********************************************************************************/
bool QuectelM95GPRS::isGPRSConnected ( void )
{
  int8_t returnStatus = ERROR_STATUS;
  returnStatus = sendCommand("AT+CGATT?", "1", "OK", 500);
  if (returnStatus = SUCCESS_STATUS)
    return true;
  else
    return false;
}
/*********************************************************************************
*
*  uint8_t QuectelM95GPRS::HTTPpost( String url, String data, 
                                  unsigned long timeOut, uint8_t retries );
*  Parameters:
*    url: Url where data needs to be posted.
*    data: data that is wished to be posted to the given URL.
*    timeOut: Timeout to receive valid response from the server.
*    retries: Number of times that the method will retry to get a sucess status.
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t QuectelM95GPRS::HTTPpost( String url, String data, 
                                  unsigned long timeOut, uint8_t retries )
{
  uint8_t returnStatus = ERROR_STATUS;
  uint8_t int_retries = retries;
  String at_url_command = "AT+QHTTPURL=";
  String at_post_command = "AT+QHTTPPOST=";
  uint16_t urlSize = url.length();
  uint16_t dataSize = data.length();
  String sizeOfUrl = String(urlSize, DEC);
  String sizeOfData = String(dataSize, DEC);
  at_url_command.concat(sizeOfUrl);
  at_url_command.concat(",60");
  at_post_command.concat(sizeOfData);
  at_post_command.concat(",50,10");
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIFGCNT=0", "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand(at_url_command, "CONNECT", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand(url, "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand(at_post_command, "CONNECT", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand(data, "OK", timeOut);
  }
  returnStatus = ERROR_STATUS;
  int_retries = retries;
  while ( (int_retries--) && !(returnStatus == SUCCESS_STATUS) )
  {
    returnStatus = sendCommand("AT+QIDEACT", "DEACT", "OK", timeOut);
  }
  return returnStatus;
}


