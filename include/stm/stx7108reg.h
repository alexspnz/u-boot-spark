/*
 * Copyright (C) STMicroelectronics Ltd. 2008,2010-2013
 *
 * All rights reserved.
 */

/*
 * This is derived from STMicroelectronics gnu toolchain example:
 *   sh-superh-elf/examples/bare/sh4reg/sti7105.h
 */


#ifndef __INCLUDE_STM_STX7108REG_H
#define __INCLUDE_STM_STX7108REG_H

#include <stm/regtype.h>

/*----------------------------------------------------------------------------*/

/*
 * Base addresses for control register banks.
 */

/* Generic SH4 control registers */
#ifndef SH4_TMU_REGS_BASE
#define SH4_TMU_REGS_BASE		0xffd80000
#endif

/* Common ST40 control registers */
#ifndef ST40_CPG_REGS_BASE
#define ST40_CPG_REGS_BASE		0xffc00000		/* QQQ - TO CHECK */
#endif

/* STx7108 control registers */
#ifndef STX7108_COMMS_BASE
#define STX7108_COMMS_BASE		0xfd700000
#endif

#ifndef STX7108_SYSCONF_BANK0_BASE
#define STX7108_SYSCONF_BANK0_BASE	0xfde30000
#endif
#ifndef STX7108_SYSCONF_BANK1_BASE
#define STX7108_SYSCONF_BANK1_BASE	0xfde20000
#endif
#ifndef STX7108_SYSCONF_BANK2_BASE
#define STX7108_SYSCONF_BANK2_BASE	0xfda50000
#endif
#ifndef STX7108_SYSCONF_BANK3_BASE
#define STX7108_SYSCONF_BANK3_BASE	0xfd500000
#endif
#ifndef STX7108_SYSCONF_BANK4_BASE
#define STX7108_SYSCONF_BANK4_BASE	0xfe700000
#endif


/* System Architecture Volume 2: Bus Interfaces */
#ifndef STM_EMI_REGS_BASE
#define STM_EMI_REGS_BASE		0xfe900000
#endif

#ifndef STM_EMI_SIZE			/* total addressable size of EMI */
#define STM_EMI_SIZE			(256 << 20)	/* 256 MiB */
#endif

/* EMISS (aka EMIPCISS) Register Configuration Space */
#define STM_EMISS_REGS_BASE		0xfdaa8000

/*----------------------------------------------------------------------------*/

/* Recommended STBus Bridge Values for GMAC */
#ifndef STM_GMAC_AHB2STBUS_BASE
#define STM_GMAC_AHB2STBUS_BASE			0x7000		/* offset */
#endif
#ifndef STM_GMAC_AHB2STBUS_CONFIG
#define STM_GMAC_AHB2STBUS_CONFIG		0x25C608	/* from validation */
#endif

/*----------------------------------------------------------------------------*/

/* System Architecture Volume 4: I/O Devices */
#ifndef STM_PIO0_REGS_BASE
#define STM_PIO0_REGS_BASE (STX7108_COMMS_BASE + 0x00020000)
#endif
#ifndef STM_PIO1_REGS_BASE
#define STM_PIO1_REGS_BASE (STX7108_COMMS_BASE + 0x00021000)
#endif
#ifndef STM_PIO2_REGS_BASE
#define STM_PIO2_REGS_BASE (STX7108_COMMS_BASE + 0x00022000)
#endif
#ifndef STM_PIO3_REGS_BASE
#define STM_PIO3_REGS_BASE (STX7108_COMMS_BASE + 0x00023000)
#endif
#ifndef STM_PIO4_REGS_BASE
#define STM_PIO4_REGS_BASE (STX7108_COMMS_BASE + 0x00024000)
#endif
#ifndef STM_PIO5_REGS_BASE
#define STM_PIO5_REGS_BASE (STX7108_COMMS_BASE + 0x00025000)
#endif
#ifndef STM_PIO6_REGS_BASE
#define STM_PIO6_REGS_BASE (STX7108_COMMS_BASE + 0x00026000)
#endif
#ifndef STM_PIO7_REGS_BASE
#define STM_PIO7_REGS_BASE (STX7108_COMMS_BASE + 0x00027000)
#endif
#ifndef STM_PIO8_REGS_BASE
#define STM_PIO8_REGS_BASE (STX7108_COMMS_BASE + 0x00028000)
#endif
#ifndef STM_PIO9_REGS_BASE
#define STM_PIO9_REGS_BASE (STX7108_COMMS_BASE + 0x00029000)
#endif

#ifndef STM_ASC0_REGS_BASE
#define STM_ASC0_REGS_BASE (STX7108_COMMS_BASE + 0x00030000)
#endif
#ifndef STM_ASC1_REGS_BASE
#define STM_ASC1_REGS_BASE (STX7108_COMMS_BASE + 0x00031000)
#endif
#ifndef STM_ASC2_REGS_BASE
#define STM_ASC2_REGS_BASE (STX7108_COMMS_BASE + 0x00032000)
#endif
#ifndef STM_ASC3_REGS_BASE
#define STM_ASC3_REGS_BASE (STX7108_COMMS_BASE + 0x00033000)
#endif

#ifndef STM_SSC0_REGS_BASE
#define STM_SSC0_REGS_BASE (STX7108_COMMS_BASE + 0x00040000)
#endif
#ifndef STM_SSC1_REGS_BASE
#define STM_SSC1_REGS_BASE (STX7108_COMMS_BASE + 0x00041000)
#endif
#ifndef STM_SSC2_REGS_BASE
#define STM_SSC2_REGS_BASE (STX7108_COMMS_BASE + 0x00042000)
#endif
#ifndef STM_SSC3_REGS_BASE
#define STM_SSC3_REGS_BASE (STX7108_COMMS_BASE + 0x00043000)
#endif
#ifndef STM_SSC4_REGS_BASE
#define STM_SSC4_REGS_BASE (STX7108_COMMS_BASE + 0x00044000)
#endif
#ifndef STM_SSC5_REGS_BASE
#define STM_SSC5_REGS_BASE (STX7108_COMMS_BASE + 0x00045000)
#endif
#ifndef STM_SSC6_REGS_BASE
#define STM_SSC6_REGS_BASE (STX7108_COMMS_BASE + 0x00046000)
#endif

#ifndef STM_PIO10_REGS_BASE
#define STM_PIO10_REGS_BASE	0xfda60000
#endif
#ifndef STM_PIO11_REGS_BASE
#define STM_PIO11_REGS_BASE	0xfda61000
#endif
#ifndef STM_PIO12_REGS_BASE
#define STM_PIO12_REGS_BASE	0xfda62000
#endif
#ifndef STM_PIO13_REGS_BASE
#define STM_PIO13_REGS_BASE	0xfda63000
#endif
#ifndef STM_PIO14_REGS_BASE
#define STM_PIO14_REGS_BASE	0xfda64000
#endif
#ifndef STM_PIO15_REGS_BASE
#define STM_PIO15_REGS_BASE	0xfe740000
#endif
#ifndef STM_PIO16_REGS_BASE
#define STM_PIO16_REGS_BASE	0xfe741000
#endif
#ifndef STM_PIO17_REGS_BASE
#define STM_PIO17_REGS_BASE	0xfe742000
#endif
#ifndef STM_PIO18_REGS_BASE
#define STM_PIO18_REGS_BASE	0xfe743000
#endif
#ifndef STM_PIO19_REGS_BASE
#define STM_PIO19_REGS_BASE	0xfe744000
#endif
#ifndef STM_PIO20_REGS_BASE
#define STM_PIO20_REGS_BASE	0xfe745000
#endif
#ifndef STM_PIO21_REGS_BASE
#define STM_PIO21_REGS_BASE	0xfe746000
#endif
#ifndef STM_PIO22_REGS_BASE
#define STM_PIO22_REGS_BASE	0xfe747000
#endif
#ifndef STM_PIO23_REGS_BASE
#define STM_PIO23_REGS_BASE	0xfe748000
#endif
#ifndef STM_PIO24_REGS_BASE
#define STM_PIO24_REGS_BASE	0xfe749000
#endif
#ifndef STM_PIO25_REGS_BASE
#define STM_PIO25_REGS_BASE	0xfe720000
#endif
#ifndef STM_PIO26_REGS_BASE
#define STM_PIO26_REGS_BASE	0xfe721000
#endif

#define STM_PIO_BASE(x)					\
	(							\
		((x) < 10)					\
		? (STM_PIO0_REGS_BASE +(0x1000*(x)))		\
		:						\
		((x) < 15)					\
		? (STM_PIO10_REGS_BASE+(0x1000*((x)-10)))	\
		:						\
		((x) < 25)					\
		? (STM_PIO15_REGS_BASE+(0x1000*((x)-15)))	\
		:						\
		(STM_PIO25_REGS_BASE+(0x1000*((x)-25)))	\
	)

/*----------------------------------------------------------------------------*/

/*
 * STx7108 System Configuration "accessors"
 *
 * Note: for Bank#0, there are no SYSCFG9, SYSCFG10, nor SYSCFG11 registers!
 */
#define STX7108_BANK0_SYSCFG(x)		STM_U32_REG(STX7108_SYSCONF_BANK0_BASE + 0x004 + (((x)>8)?(x)-3:(x))*0x4)
#define STX7108_BANK1_SYSCFG(x)		STM_U32_REG(STX7108_SYSCONF_BANK1_BASE + 0x03c + (x)*0x4)
#define STX7108_BANK2_SYSCFG(x)		STM_U32_REG(STX7108_SYSCONF_BANK2_BASE + 0x000 + (x)*0x4)
#define STX7108_BANK3_SYSCFG(x)		STM_U32_REG(STX7108_SYSCONF_BANK3_BASE + 0x018 + (x)*0x4)
#define STX7108_BANK4_SYSCFG(x)		STM_U32_REG(STX7108_SYSCONF_BANK4_BASE + 0x000 + (x)*0x4)

/*
 * STx7108 System Status "accessors"
 */
#define STX7108_BANK0_SYSSTS(x)		STM_U32_REG(STX7108_SYSCONF_BANK0_BASE + 0x000 + (x)*0x4)
#define STX7108_BANK1_SYSSTS(x)		STM_U32_REG(STX7108_SYSCONF_BANK1_BASE + 0x000 + (x)*0x4)
#define STX7108_BANK2_SYSSTS(x)		STM_U32_REG(STX7108_SYSCONF_BANK2_BASE + 0x0e4 + (x)*0x4)
#define STX7108_BANK3_SYSSTS(x)		STM_U32_REG(STX7108_SYSCONF_BANK3_BASE + 0x000 + (x)*0x4)
#define STX7108_BANK4_SYSSTS(x)		STM_U32_REG(STX7108_SYSCONF_BANK4_BASE + 0x11c + (x)*0x4)


/*----------------------------------------------------------------------------*/

#include <stm/stxxxxxreg.h>

/*----------------------------------------------------------------------------*/

/*
 * Device ID register & bitfields
 */

#define STX7108_SYSCONF_DEVICEID_0	STM_U32_REG(STX7108_SYSCONF_BANK1_BASE + 0x0000)

/* Device ID values, masks & predicates */
#define STX7108_DEVID_7108_VAL		0x043
#define STX7108_DEVID_ID_SHIFT		12
#define STX7108_DEVID_ID_MASK		0x3ff
#define STX7108_DEVID_CUT_SHIFT		28
#define STX7108_DEVID_CUT_MASK		0xf

#define STX7108_DEVICEID_7108(ID) ((((ID) >> STX7108_DEVID_ID_SHIFT) & STX7108_DEVID_ID_MASK) == STX7108_DEVID_7108_VAL)
#define STX7108_DEVICEID_CUT(ID)  ((((ID) >> STX7108_DEVID_CUT_SHIFT) & STX7108_DEVID_CUT_MASK) + 1)

#endif /* __INCLUDE_STM_STX7108REG_H */
