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

#define PIC_CFG_SEC(reg, sec, val) \
    (((val) << _ ## reg ## _ ## sec ## _POSITION) | \
    (~(unsigned long int)_ ## reg ## _ ## sec ## _MASK))

/* PGEC1/PGED1 */
const unsigned long int DEVCFG0_VAL __attribute__ ((section(".devcfg0"))) =
    _DEVCFG0_w_MASK &
    PIC_CFG_SEC(DEVCFG0, DEBUG, 0x03) &
    PIC_CFG_SEC(DEVCFG0, JTAGEN, 0x01) &
    PIC_CFG_SEC(DEVCFG0, ICESEL, 0x03) &
    PIC_CFG_SEC(DEVCFG0, PWP, 0x01ff) &
    PIC_CFG_SEC(DEVCFG0, BWP, 0x01) &
    PIC_CFG_SEC(DEVCFG0, CP, 0x01);

/* WDT off, clock switching enabled, PBCLK is SYSCLK/2, OSC is primary with PLL */
const unsigned long int DEVCFG1_VAL __attribute__ ((section(".devcfg1"))) =
    _DEVCFG1_w_MASK &
    PIC_CFG_SEC(DEVCFG1, FNOSC, 0x03) &
    PIC_CFG_SEC(DEVCFG1, FSOSCEN, 0x00) &
    PIC_CFG_SEC(DEVCFG1, IESO, 0x00) &
    PIC_CFG_SEC(DEVCFG1, POSCMOD, 0x02) &
    PIC_CFG_SEC(DEVCFG1, OSCIOFNC, 0x01) &
    PIC_CFG_SEC(DEVCFG1, FPBDIV, 0x01) &
    PIC_CFG_SEC(DEVCFG1, FCKSM, 0x03) &
    PIC_CFG_SEC(DEVCFG1, WDTPS, 0x14) &
    PIC_CFG_SEC(DEVCFG1, WINDIS, 0x01) &
    PIC_CFG_SEC(DEVCFG1, FWDTEN, 0x00) &
    PIC_CFG_SEC(DEVCFG1, FWDTWINSZ, 0x01);

/* PLL div 2,  mul 20, div2 */
const unsigned long int DEVCFG2_VAL __attribute__ ((section(".devcfg2"))) =
    _DEVCFG2_w_MASK &
    PIC_CFG_SEC(DEVCFG2, FPLLIDIV, 0x01) &
    PIC_CFG_SEC(DEVCFG2, FPLLMUL, 0x05) &
    PIC_CFG_SEC(DEVCFG2, UPLLIDIV, 0x01) &
    PIC_CFG_SEC(DEVCFG2, UPLLEN, 0x01) &
    PIC_CFG_SEC(DEVCFG2, FPLLODIV, 0x01);

/* USB pins controlled by port function, allow 1 peripheral reconfiguration */
const unsigned long int DEVCFG3_VAL __attribute__((section(".devcfg3"))) =
    _DEVCFG3_w_MASK &
    PIC_CFG_SEC(DEVCFG3, USERID, 0x2424) &
    PIC_CFG_SEC(DEVCFG3, PMDL1WAY, 0x01) &
    PIC_CFG_SEC(DEVCFG3, IOL1WAY, 0x01) &
    PIC_CFG_SEC(DEVCFG3, FUSBIDIO, 0x00) &
    PIC_CFG_SEC(DEVCFG3, FVBUSONIO, 0x00);
