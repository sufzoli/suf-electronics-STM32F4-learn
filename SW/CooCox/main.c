/**
 *	USB VCP for STM32F4xx example.
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision
 *
 * Add line below to use this example with F429 Discovery board (in defines.h file)
 *
 * #define USE_USB_OTG_HS
 */
#include "tm_stm32f4_usb_vcp.h"
#include "tm_stm32f4_disco.h"
#include "defines.h"

int main(void) {
	uint8_t c;
	/* System Init */
	SystemInit();

	/* Initialize LED's. Make sure to check settings for your board in tm_stm32f4_disco.h file */
	TM_DISCO_LedInit();

	/* Initialize USB VCP */
	TM_USB_VCP_Init();

	while (1) {
		/* USB configured OK, drivers OK */
		if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) {
			/* Turn on GREEN led */
			TM_DISCO_LedOn(LED_GREEN);
			TM_DISCO_LedOff(LED_RED);
			/* If something arrived at VCP */
			if (TM_USB_VCP_Getc(&c) == TM_USB_VCP_DATA_OK) {
				/* Return data back */
				TM_USB_VCP_Putc(c);
			}
		} else {
			/* USB not OK */
			TM_DISCO_LedOff(LED_GREEN);
			TM_DISCO_LedOn(LED_RED);
		}
	}
}
