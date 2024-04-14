#ifndef LCD_H_
#define LCD_H_

#include "stdlib.h"

#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
	#include "stm32f1xx.h"
#endif

// commands
#define LCD_CLEARDISPLAY 		0x01
#define LCD_RETURNHOME 			0x02
#define LCD_ENTRYMODESET 		0x04
#define LCD_DISPLAYCONTROL 		0x08
#define LCD_CURSORSHIFT 		0x10
#define LCD_FUNCTIONSET 		0x20
#define LCD_SETCGRAMADDR 		0x40
#define LCD_SETDDRAMADDR 		0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 			0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 			0x04
#define LCD_DISPLAYOFF 			0x00
#define LCD_CURSORON 			0x02
#define LCD_CURSOROFF 			0x00
#define LCD_BLINKON 			0x01
#define LCD_BLINKOFF 			0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 		0x08
#define LCD_CURSORMOVE 			0x00
#define LCD_MOVERIGHT 			0x04
#define LCD_MOVELEFT 			0x00

// flags for function set
#define LCD_8BITMODE 			0x10
#define LCD_4BITMODE 			0x00
#define LCD_2LINE 				0x08
#define LCD_1LINE 				0x00
#define LCD_5x10DOTS 			0x04
#define LCD_5x8DOTS 			0x00

// Pins and Ports

#ifndef D4_GPIO_Port
#define D4_GPIO_Port GPIOC
#endif
#ifndef D4_Pin
#define D4_Pin (1 << 4)
#endif
#ifndef D5_GPIO_Port
#define D5_GPIO_Port GPIOC
#endif
#ifndef D5_Pin
#define D5_Pin (1 << 5)
#endif
#ifndef D6_GPIO_Port
#define D6_GPIO_Port GPIOC
#endif
#ifndef D6_Pin
#define D6_Pin (1 << 6)
#endif
#ifndef D7_GPIO_Port
#define D7_GPIO_Port GPIOC
#endif
#ifndef D7_Pin
#define D7_Pin (1 << 7)
#endif
#ifndef RS_GPIO_Port
#define RS_GPIO_Port GPIOC
#endif
#ifndef RS_Pin
#define RS_Pin (1 << 8)
#endif
#ifndef EN_GPIO_Port
#define EN_GPIO_Port GPIOC
#endif
#ifndef EN_Pin
#define EN_Pin (1 << 9)
#endif

// PIN Macro
#define WRITE_PIN(PORT,PIN,STATE) (\
		{\
			if(STATE)\
				PORT->BSRR = PIN;\
			else\
				PORT->BSRR = PIN << 16u;\
		})

/*------------ Declaring Function Prototype -------------*/

void LCD_GPIO_init();

void LCD_sendCmd(uint8_t data);

void LCD_sendChar( uint8_t data);

void LCD_sendNibble(uint8_t data);

void LCD_sendByte( uint8_t data);

void LCD_puts( char * data);

void LCD_init();

void LCD_clear();

void LCD_setCursor(char row, char col);

void LCD_scroll(char isScroll);

int LCD_printf(const char* fmt,...);

// declare this function in your code
void LCD_DelayMS(uint16_t ms);
#endif /* LCD_H_ */
