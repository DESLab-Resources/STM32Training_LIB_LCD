/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stm32f1xx.h>
#include "lcd.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void ClockInit();

int main(void)
{

	ClockInit();

	LCD_init();
	LCD_clear();
	LCD_setCursor(0, 0);
	LCD_printf("I love STM32!");

    /* Loop forever */
	for(;;);
}

void ClockInit(){
	// Bit 4 PRFTBE: Prefetch buffer enable
	FLASH->ACR |= (1 << 4); // Prefetch is enabled

	//
	// HSE Configuration
	// Bit 16 HSEON: HSE clock enable
	RCC->CR |= (1 << 16); // HSE oscillator ON

	/* Wait till HSE is ready */
	// Bit 17 HSERDY: External high-speed clock ready flag
	while(!(RCC->CR & (1 << 17)));

	//
	// PLL Configuration
	/* Disable the main PLL. */
	// Bit 24 PLLON: PLL enable
	RCC->CR &= ~(1 << 24); // PLL OFF

	/* Wait till PLL is disabled */
	// Bit 25 PLLRDY: PLL clock ready flag
	while(RCC->CR & (1 << 25));

	/* Set PREDIV1 Value */
	// Bit 17 PLLXTPRE: HSE divider for PLL entry
	RCC->CFGR &= ~(1 << 17); // HSE clock not divided

	/* Configure the main PLL clock source and multiplication factors. */
	// Bit 16 PLLSRC: PLL entry clock source
	RCC->CFGR |= (1 << 16); // HSE oscillator clock selected as PLL input clock
	// Bits 21:18 PLLMUL: PLL multiplication factor
	RCC->CFGR &= ~(0b1111 << 18);
	RCC->CFGR |= (0b111 << 18); // PLL input clock x 9

	/* Enable the main PLL. */
	// Bit 24 PLLON: PLL enable
	RCC->CR |= (1 << 24); // PLL ON

	/* Wait till PLL is ready */
	// Bit 25 PLLRDY: PLL clock ready flag
	while(!(RCC->CR & (1 << 25)));

	// Bits 2:0 LATENCY: Latency
	FLASH->ACR &= (0b111 << 0);
	FLASH->ACR |= (0b10 << 0); // Two wait states, if 48 MHz < SYSCLK <= 72 MHz

	// HCLK Configuration
	/* Set the highest APBx dividers in order to ensure that we do not go through
	      5     a non-spec phase whatever we decrease or increase HCLK. */
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	RCC->CFGR |= (0b111 << 8); // HCLK divided by 16
	// Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	RCC->CFGR |= (0b111 << 11); // HCLK divided by 16

	/* Set the new HCLK clock divider */
	// Bits 7:4 HPRE: AHB prescaler
	RCC->CFGR &= ~(0b1111 << 4); // SYSCLK not divided

	//
	// SYSCLK Configuration
	/* PLL is selected as System Clock Source */
	// Bit 25 PLLRDY: PLL clock ready flag
	/* Check the PLL ready flag */
	while(!(RCC->CR & (1 << 25)));

	// Bits 1:0 SW: System clock switch
	RCC->CFGR &= ~(1 << 0); // PLL selected as system clock
	RCC->CFGR |= (1 << 1);

	while( ( ( RCC->CFGR & (0b11 << 2) ) >> 2 ) != (0b10) ); // Bits 3:2 SWS: System clock switch status

	//
	// PCLK1 Configuration
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	RCC->CFGR &= ~(0b111 << 8);
	RCC->CFGR |= (0b100 << 8); // HCLK divided by 2

	// PCLK2 Configuration
	// Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	RCC->CFGR &= ~(0b111 << 11); // HCLK not divided
}

void LCD_DelayMS(uint16_t ms)
{
	for(size_t i = 0;i < ms;i++)
	{
		SysTick->LOAD = 9000; // 1ms delay
		SysTick->CTRL = 0x01; // 9MHz clock
		while((SysTick->CTRL & (1<<16)) == 0);
		SysTick->CTRL = 0x00;
	}
}

void LCD_GPIO_init()
{

	SET_BIT(RCC->APB2ENR, (1 << 4));

	MODIFY_REG(GPIOC->CRL, (0b111 << 17) | (0b111 << 21) | (0b111 << 25) | (0b111 << 29)
			, (1 << 16) | (1 << 20) | (1 << 24) | (1 << 28));

	MODIFY_REG(GPIOC->CRH, (0b111 << 1) | (0b111 << 5)
			, (1 << 0) | (1 << 4));

}
