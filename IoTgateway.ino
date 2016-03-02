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
// Description: 
//        
//
// Dependencies:  Arduino.h 
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//////////////////////////////////////////////////////////////////////////////////
#include "DueTimer.h"
#include "IoTDefs.h"
#include "gprs_lib.h"
#include "oled_display_lib.h"
#include "oled_display_resources.h"
//#include "MQTT_QUECTEL.h"

bool send_data_flag = false;
uint8_t connecting_screen_status = 0;
uint8_t connected_screen_status = 0;
uint8_t stateMachineStatus = 0;
QuectelM95GPRS gsmRadio( 115200, GPRS_PWR );
OLED_DISPLAY displayScreen( SCREEN_ADD );
String posting_url = "http://h2odoctors.com/utils/edgar/testing.php";
String radioIMEI;
String dataToSend;
uint8_t time_counter = 0;
/*********************************************************************************
*
*  void setup();
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
void setup() 
{
  pinMode(DIG_INPUT1, INPUT);
  pinMode(DIG_INPUT2, INPUT);
  pinMode(DIG_INPUT3, INPUT);
  pinMode(AN_INPUT1, INPUT);
  pinMode(AN_INPUT2, INPUT);
  pinMode(AN_INPUT3, INPUT);
  Serial.begin(115200);
  Serial.print("ProgramBegin");
  displayScreen.begin();
  displayScreen.printBMP(IMG_BMP_WELCOME);
  stateMachineStatus = CONNECTING_STATE;
}
/*********************************************************************************
*
*
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
void loop() {
  //State Machine
  switch( stateMachineStatus ) 
  {
    //State that starts the connection to the cellular network
    case CONNECTING_STATE: 
    {
      gsmRadio.begin(20);
      delay(3000);
      displayScreen.printBMP(IMG_BMP_CONNECTING1);
      connecting_screen_status = 1;
      Timer6.attachInterrupt(updateScreen);
      Timer6.start(2000000); 
      radioIMEI = gsmRadio.getImei(500);
      uint8_t connect_status = gsmRadio.connectToGPRS( 50000, 5 );
      if( connect_status == SUCCESS_STATUS )
      { 
        Timer6.stop();
        stateMachineStatus = CONNECTED_STATE;
        displayScreen.printBMP(IMG_BMP_CONNECTED);
        Timer7.attachInterrupt(countTime);
        Timer7.start(10000000);
      }  
      else
      {
        displayScreen.printBMP(CONERROR);
        delay(2000);
        stateMachineStatus = RETRY_CONNECTION;
        Timer6.stop();
      }
    }break;  
    case CONNECTED_STATE:
    {

      if(send_data_flag)
      {
        Timer7.stop();
        sendData();
        connected_screen_status = gsmRadio.getQualityOfService(500);
        updateScreen();
        gsmRadio.HTTPpost(posting_url, dataToSend, 5000, 5 ); 
        send_data_flag = false;
        Timer7.start(10000000);
      }
    }break;
    case RETRY_CONNECTION:
    {
      
    }
  }
}
/*********************************************************************************
*
*
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
void countTime ( void ) 
{
  send_data_flag = true;
}
/*********************************************************************************
*
*
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
void sendData ( void )
{
  dataToSend = "";
  uint16_t an1 = analogRead(AN_INPUT1);
  uint16_t an2 = analogRead(AN_INPUT2);
  uint16_t an3 = analogRead(AN_INPUT3);
  uint8_t dig1 = digitalRead(DIG_INPUT1);
  uint8_t dig2 = digitalRead(DIG_INPUT2);
  uint8_t dig3 = digitalRead(DIG_INPUT3);
  dataToSend.concat("IMEI=");
  dataToSend.concat(radioIMEI);
  dataToSend.concat("&");
  dataToSend.concat("AN1=");
  dataToSend.concat(String(an1,DEC));
  dataToSend.concat("&");
  dataToSend.concat("AN2=");
  dataToSend.concat(String(an2,DEC));
  dataToSend.concat("&");
  dataToSend.concat("AN3=");
  dataToSend.concat(String(an3,DEC));
  dataToSend.concat("&");
  dataToSend.concat("DIG1=");
  dataToSend.concat(String(dig1,DEC));
  dataToSend.concat("&");
  dataToSend.concat("DIG2=");
  dataToSend.concat(String(dig2,DEC));
  dataToSend.concat("&");
  dataToSend.concat("DIG3=");
  dataToSend.concat(String(dig3,DEC));
  Serial.println(dataToSend);
}
/*********************************************************************************
*
*
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
void updateScreen ( void )
{
  switch(stateMachineStatus)
  {
    case CONNECTING_STATE:
    {
      switch(connecting_screen_status)
      {
        case 1:
        {
          displayScreen.printBMP(IMG_BMP_CONNECTING2);
          connecting_screen_status =2;
        }break;
        case 2:
        {
          displayScreen.printBMP(IMG_BMP_CONNECTING3);
          connecting_screen_status =3;
        }break;
        case 3:
        {
          displayScreen.printBMP(IMG_BMP_CONNECTING1);
          connecting_screen_status =1;
        }break;
        default:break;
      }
    }break;
    case CONNECTED_STATE:
    {
      switch(connected_screen_status)
      {
        case 0:
        {
          displayScreen.printBMP(CONNECTEDNOBAR);
        }break;
        case 1:
        {
          displayScreen.printBMP(CONNECTEDONEBAR);
        }break;
        case 2:
        {
          displayScreen.printBMP(CONNECTEDTWOBAR);
        }break;
        case 3:
        {
          displayScreen.printBMP(CONNECTEDTHREEBAR);
        }break;
        case 4:
        {
          displayScreen.printBMP(CONNECTEDFOURBAR);
        }break;
        default:break;
      }
    }
    default:break;
  }
}
