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
// Description:
//              
//
// Dependencies: 
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments: Documentation for every method is provided in the 
//                      cpp file.
//////////////////////////////////////////////////////////////////////////////////
#ifndef _OLED_DISPLAY_LIB_H_
#define _OLED_DISPLAY_LIB_H_
#include "Wire.h"

//Definitions for the Display
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  

class OLED_DISPLAY 
{
  private:
    uint8_t _diplay_add;
    uint8_t sendCommand( uint8_t disp_command );
  public:
    OLED_DISPLAY( uint8_t address);
    void begin( void );
    void printBMP( uint8_t *image );
};
#endif
