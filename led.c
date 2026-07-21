/*
 * led.c
 *
 *  Created on: 29-Jun-2026
 *      Author: Subarno Pal
 */


#include "led.h"

void delay(uint32_t count){
	for(uint32_t i = 0; i<count ; i++);
}

void led_init_all(void){
	uint32_t *pRCCAHB1ENR = (uint32_t *)(RCC_BASE_ADDR + 0x30);
	uint32_t *pGPIO_MODER = (uint32_t *)(GPIOC_BASE_ADDR + 0x00);

	*pRCCAHB1ENR |= (1 << 2); //Peripheral Clock of GPIOC is enabled

	//Set the mode of all the LED pins as Output
	*pGPIO_MODER |= (1 << (2*LED1));
	*pGPIO_MODER |= (1 << (2*LED2));
	*pGPIO_MODER |= (1 << (2*LED3));
	*pGPIO_MODER |= (1 << (2*LED4));

#if 0
	pGPIO_optype |= (1 << (2*LED1));
	pGPIO_optype |= (1 << (2*LED2));
	pGPIO_optype |= (1 << (2*LED3));
	pGPIO_optype |= (1 << (2*LED4));

#endif
	led_off(LED1);
	led_off(LED2);
	led_off(LED3);
	led_off(LED4);
}

void led_on(uint8_t led_no){
	uint32_t *pGPIO_ODR = (uint32_t *)(GPIOC_BASE_ADDR + 0x14);
	*pGPIO_ODR |= (1 << led_no);
}

void led_off(uint8_t led_no){
	uint32_t *pGPIO_ODR = (uint32_t *)(GPIOC_BASE_ADDR + 0x14);
	*pGPIO_ODR &= ~(1 << led_no);
}
