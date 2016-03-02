//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Edgar Duarte
//
// Create Date: 
// Design Name: 
// Module Name:  
// Project Name:  IoT low Cost Gateway.
// Target Devices: Processor Board: Atmel ATSAM32X8E. (Using Flip&Click development board
//                                    by Mikroelectronica).
//                                    http://www.mikroe.com/flip-n-click/).
//                 Screen: 
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
#include "oled_display_lib.h"
/*********************************************************************************
*
*  OLED_DISPLAY::OLED_DISPLAY ( uint8_t address);
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
OLED_DISPLAY::OLED_DISPLAY ( uint8_t address)
{
	_diplay_add = address;
}

void OLED_DISPLAY::begin( void )
{
  Wire1.begin();
  sendCommand(SSD1306_DISPLAYOFF);                    // 0xAE
  sendCommand(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
  sendCommand(0x80);                                  // the suggested ratio 0x80
  sendCommand(SSD1306_SETMULTIPLEX);                  // 0xA8
  sendCommand(0x3F);
  sendCommand(SSD1306_SETDISPLAYOFFSET);              // 0xD3
  sendCommand(0x0);                                   // no offset
  sendCommand(SSD1306_SETSTARTLINE | 0x0);            // line #0
  sendCommand(SSD1306_CHARGEPUMP);                    // 0x8D
  sendCommand(0x14);
  sendCommand(SSD1306_MEMORYMODE);                    // 0x20
  sendCommand(0x00);                                  // 0x0 act like ks0108
  sendCommand(SSD1306_SEGREMAP | 0x1);
  sendCommand(SSD1306_COMSCANDEC);
  sendCommand(SSD1306_SETCOMPINS);                    // 0xDA
  sendCommand(0x12);
  sendCommand(SSD1306_SETCONTRAST);      
  sendCommand(0xCF);
  sendCommand(SSD1306_SETPRECHARGE);
  sendCommand(SSD1306_SETVCOMDETECT);                 // 0xDB
  sendCommand(0x40);
  sendCommand(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
  sendCommand(SSD1306_NORMALDISPLAY);                 // 0xA6
  sendCommand(SSD1306_DISPLAYON);
}
/*********************************************************************************
*
*  uint8_t OLED_DISPLAY::sendCommand( uint8_t disp_command );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
uint8_t OLED_DISPLAY::sendCommand( uint8_t disp_command )
{
  Wire1.beginTransmission(_diplay_add);
  Wire1.write(0x00);
  Wire1.write(disp_command);
  Wire1.endTransmission();
}
/*********************************************************************************
*
*  void OLED_DISPLAY::printBMP( uint8_t *image );
*  Parameters:
*  Returns:
*  Description:
*
*********************************************************************************/
void OLED_DISPLAY::printBMP( uint8_t *image ) 
{
  for (uint16_t i=0; i<1024; i++) {
    // send a bunch of data in one xmission
    Wire1.beginTransmission(_diplay_add);
    Wire1.write(0x40);
    for (uint8_t x=0; x<16; x++) {
      Wire1.write(image[i]);
      i++;
    }
    i--;
    Wire1.endTransmission();
  }
}
