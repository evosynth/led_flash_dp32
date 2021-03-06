/* Copyright 2017 Julian Ingram
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "p32mx250f128b.h"

#include <mips/hal.h>
#include <mips/cpu.h>

static const unsigned long int SYS_CLK = 40000000UL;

void gie(void)
{
    __asm__ __volatile__("ei");
    __asm__ __volatile__("ehb");
}

void gid(void)
{
    __asm__ __volatile__("di");
    __asm__ __volatile__("ehb");
}

static void led_toggle(const unsigned char id)
{
    PORTBINV = 1u << id;
}

static void leds_init(void)
{
	PORTBCLR = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    TRISBCLR = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
}

static void core_timer_init(void)
{
    /* 1s tick */
    mips32_set_c0(C0_COMPARE, mips32_get_c0(C0_COUNT) + (SYS_CLK / 2));

    /* clear interrupt flag */
    IFS0CLR = _IFS0_CTIF_MASK;

    /* set interrupt priority */
    IPC0CLR = _IPC0_CTIP_MASK;
    IPC0SET = (1 << _IPC0_CTIP_POSITION); /* priority 1 */
    /* set interrupt subpriority */
    IPC0CLR =  _IPC0_CTIS_MASK;
    IPC0SET = (0 << _IPC0_CTIS_POSITION); /* subpriority 0 */

    /* enable interrupt */
    IEC0SET = _IEC0_CTIE_MASK;
}

static void single_vector_mode_init(void)
{
    /* disable interrupts */
	gid();

	/* set ebase */
	mips32_set_c0(C0_EBASE, 0x9d000000ul);
    /* set IV */
	const unsigned long int tmp = mips32_get_c0(C0_CAUSE) | 0x00800000ul;
	mips32_set_c0(C0_CAUSE, tmp);

	INTCONCLR = _INTCON_MVEC_MASK;

	/* enable interrupts */
	gie();
}

static void board_init(void)
{
	/* ansel to digital */
	ANSELACLR = _ANSELA_w_MASK;
	ANSELBCLR = _ANSELB_w_MASK;

    leds_init();

    single_vector_mode_init();
}

void __attribute__ ((interrupt, keep_interrupts_masked)) _mips_interrupt(void)
{
    if (((IEC0 & _IEC0_CTIE_MASK) != 0) && ((IFS0 & _IFS0_CTIF_MASK) != 0))
    {
        /* core timer interrupt */
        led_toggle(0);
        IFS0CLR = _IFS0_CTIF_MASK;
        mips32_set_c0(C0_COMPARE, mips32_get_c0(C0_COMPARE) + (SYS_CLK / 2));
    }
}

int main(void)
{
    board_init();
    core_timer_init();
    led_toggle(0);

    while (1)
    {
    }
    return -1;
}
