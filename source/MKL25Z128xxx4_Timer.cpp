/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MKL25Z128xxx4_Timer.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "SwTimer.h"
#include "Ticker.h"

#define SYSTICK_MS 10U
#define SYSTICK_TICKS CLOCK_GetFreq(kCLOCK_CoreSysClk)/(1000/(SYSTICK_MS))

volatile uint64_t glTicks = 0;


uint64_t getRunTimeInMs() {
	return glTicks * SYSTICK_MS;
}
SwTimer swTimer1(&getRunTimeInMs);
SwTimer swTimer2(&getRunTimeInMs);
SwTimer swTimer3(&getRunTimeInMs);
SwTimer swTimer4(&getRunTimeInMs);
Ticker<5,&swTimer1,&swTimer2,&swTimer3,&swTimer4> ticker1;

extern "C" void SysTick_Handler() {
	++glTicks;
	ticker1.checkExpiration();

}

void callback(SwTimer& swTimer){
	PRINTF("Delay:%d\r\n",(unsigned int) swTimer.getDelayMs());
}
volatile int flag_i = 0;
void callback2(SwTimer& swTimer){
	flag_i++;
	PRINTF("Temp delay:%d\r\n",(unsigned int) swTimer.getDelayMs());

}
/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	// Setup Systick
	SysTick_Config(SYSTICK_TICKS);
	EnableIRQ(SysTick_IRQn);

	PRINTF("Hello World\n");

	swTimer1.startTimer(501);
	swTimer2.startTimer(1002);
	swTimer2.setAutoReload(true);
	swTimer3.startTimer(1503);
	swTimer3.setAutoReload(true);
	swTimer1.setCallbackFn(&callback);
	swTimer2.setCallbackFn(&callback);
	swTimer3.setCallbackFn(&callback);

	void *pt;
	{
		SwTimer swtimerTemp(&getRunTimeInMs,true);
		pt = (void *)&swtimerTemp;
		swtimerTemp.setCallbackFn(&callback2);
		swtimerTemp.startTimer(1000);
		swtimerTemp.attach_to_ticker(ticker1);
		while(flag_i<5);
	}
	memset(pt,0,sizeof(SwTimer));

	/* Force the counter to be placed into memory. */
	volatile static int i = 0;
	/* Enter an infinite loop, just incrementing a counter. */
	while (1) {
		i++;
		/* 'Dummy' NOP to allow source level single stepping of
		 tight while() loop */
		__asm volatile ("nop");
	}
	return 0;
}
