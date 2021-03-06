/*
 * Copyright (C) STMicroelectronics Ltd. 2009.
 *
 * All rights reserved.
 */

#ifndef __INCLUDE_STM_FLI7510REG_H
#define __INCLUDE_STM_FLI7510REG_H

#include <stm/regtype.h>

/*----------------------------------------------------------------------------*/

	/*
	 *	PIO_BK_0 ... PIO_BK_27
	 */
#define STM_PIO0_REGS_BASE	0xfd5c0000
#define STM_PIO1_REGS_BASE	0xfd5c4000
#define STM_PIO2_REGS_BASE	0xfd5c8000
#define STM_PIO3_REGS_BASE	0xfd5cc000
#define STM_PIO4_REGS_BASE	0xfd5d0000
#define STM_PIO5_REGS_BASE	0xfd5d4000
#define STM_PIO6_REGS_BASE	0xfd5d8000
#define STM_PIO7_REGS_BASE	0xfd5dc000
#define STM_PIO8_REGS_BASE	0xfd5e0000
#define STM_PIO9_REGS_BASE	0xfd5e4000
#define STM_PIO10_REGS_BASE	0xfd984000
#define STM_PIO11_REGS_BASE	0xfd988000
#define STM_PIO12_REGS_BASE	0xfd98c000
#define STM_PIO13_REGS_BASE	0xfd990000
#define STM_PIO14_REGS_BASE	0xfd994000
#define STM_PIO15_REGS_BASE	0xfd998000
#define STM_PIO16_REGS_BASE	0xfd99c000
#define STM_PIO17_REGS_BASE	0xfd9a0000
#define STM_PIO18_REGS_BASE	0xfd9a4000
#define STM_PIO19_REGS_BASE	0xfd9a8000
#define STM_PIO20_REGS_BASE	0xfd9ac000
#define STM_PIO21_REGS_BASE	0xfd9b0000
#define STM_PIO22_REGS_BASE	0xfd9b4000
#define STM_PIO23_REGS_BASE	0xfd9b8000
#define STM_PIO24_REGS_BASE	0xfd9bc000
#define STM_PIO25_REGS_BASE	0xfd9c0000
#define STM_PIO26_REGS_BASE	0xfd9c4000
#define STM_PIO27_REGS_BASE	0xfd9c8000

#define STM_PIO_BASE(x)					\
	(((x) < 10)						\
		? (STM_PIO0_REGS_BASE +(0x4000*(x)))		\
		: (STM_PIO10_REGS_BASE+(0x4000*((x)-10))))

/*----------------------------------------------------------------------------*/


	/*
	 * Comms block
	 */
#ifndef FLI7510_COMMS_BASE
#define FLI7510_COMMS_BASE	0xfdb00000
#endif

#ifndef STM_ASC0_REGS_BASE	/* UART #1 */
#define STM_ASC0_REGS_BASE	(FLI7510_COMMS_BASE + 0x00030000)
#endif
#ifndef STM_ASC1_REGS_BASE	/* UART #2 */
#define STM_ASC1_REGS_BASE	(FLI7510_COMMS_BASE + 0x00031000)
#endif
#ifndef STM_ASC2_REGS_BASE	/* UART #3 */
#define STM_ASC2_REGS_BASE	(FLI7510_COMMS_BASE + 0x00032000)
#endif


/*----------------------------------------------------------------------------*/


	/*
	 * System Configuration Registers
	 */
#define PRB_PU_CFG_1				0xfd220000
#define PRB_PU_CFG_2				0xfd228000
#define TRS_PU_CFG_0				0xfd9ec000
#define TRS_PU_CFG_1				0xfd9f4000
#define VDEC_PU_CFG_0				0xfd7a0000
#define VDEC_PU_CFG_1				0xfd7c0000
#define VOUT_PU_CFG_1				0xfd5e8000

#define CONFIG_SYS_RESET_CTL			(PRB_PU_CFG_1 + 0x00)
#define CONFIG_SYS_BOOT_CTL			(PRB_PU_CFG_1 + 0x04)
#define CONFIG_SYS_SYS1				(PRB_PU_CFG_1 + 0x08)
#define CONFIG_SYS_MPX_CTL			(PRB_PU_CFG_1 + 0x0c)
#define CONFIG_SYS_PWR_DWN_CTL			(PRB_PU_CFG_1 + 0x10)
#define CONFIG_SYS_SYS2				(PRB_PU_CFG_1 + 0x14)
#define CONFIG_SYS_MODE_PIN_STATUS		(PRB_PU_CFG_1 + 0x18)
#define CONFIG_SYS_PCI_ROPC_STATUS		(PRB_PU_CFG_1 + 0x1c)

#define CONFIG_SYS_ST40_HOST_BOOT_ADDR		(PRB_PU_CFG_2 + 0x00)
#define CONFIG_SYS_ST40_CTL_BOOT_ADDR		(PRB_PU_CFG_2 + 0x04)
#define CONFIG_SYS_SYS10			(PRB_PU_CFG_2 + 0x08)
#define CONFIG_SYS_RNG_BIST_CTL			(PRB_PU_CFG_2 + 0x0c)
#define CONFIG_SYS_SYS12			(PRB_PU_CFG_2 + 0x10)
#define CONFIG_SYS_SYS13			(PRB_PU_CFG_2 + 0x14)
#define CONFIG_SYS_SYS14			(PRB_PU_CFG_2 + 0x18)
#define CONFIG_SYS_EMI_ROPC_STATUS		(PRB_PU_CFG_2 + 0x1c)

#define CONFIG_SYS_COMMS_CONFIG_1		(TRS_PU_CFG_0 + 0x00)
#define CONFIG_SYS_TRS_CONFIG			(TRS_PU_CFG_0 + 0x04)
#define CONFIG_SYS_COMMS_CONFIG_2		(TRS_PU_CFG_0 + 0x08)
#define CONFIG_SYS_USB_SOFT_JTAG		(TRS_PU_CFG_0 + 0x0c)
#define CONFIG_SYS_NOTUSED_1			(TRS_PU_CFG_0 + 0x10)
#define CONFIG_SYS_NOTUSED_2			(TRS_PU_CFG_0 + 0x14)
#define CONFIG_SYS_COMMS_TRS_STATUS		(TRS_PU_CFG_0 + 0x18)
#define CONFIG_SYS_EXTRA_ID1_LSB		(TRS_PU_CFG_0 + 0x1c)

#define CONFIG_SYS_SPARE_1			(TRS_PU_CFG_1 + 0x00)
#define CONFIG_SYS_SPARE_2			(TRS_PU_CFG_1 + 0x04)
#define CONFIG_SYS_SPARE_3			(TRS_PU_CFG_1 + 0x08)
#define CONFIG_SYS_NOTUSED_3			(TRS_PU_CFG_1 + 0x0c)
#define CONFIG_SYS_NOTUSED_4			(TRS_PU_CFG_1 + 0x10)
#define CONFIG_SYS_NOTUSED_5			(TRS_PU_CFG_1 + 0x14)
#define CONFIG_SYS_DEVICE_ID			(TRS_PU_CFG_1 + 0x18)
#define CONFIG_SYS_EXTRA_ID1_MSB		(TRS_PU_CFG_1 + 0x1c)

#define CONFIG_SYS_TOP_SPARE_REG1		(VDEC_PU_CFG_0 + 0x00)
#define CONFIG_SYS_TOP_SPARE_REG2		(VDEC_PU_CFG_0 + 0x04)
#define CONFIG_SYS_TOP_SPARE_REG3		(VDEC_PU_CFG_0 + 0x08)
#define CONFIG_SYS_ST231_DRA2_DEBUG		(VDEC_PU_CFG_0 + 0x0c)
#define CONFIG_SYS_ST231_AUD1_DEBUG		(VDEC_PU_CFG_0 + 0x10)
#define CONFIG_SYS_ST231_AUD2_DEBUG		(VDEC_PU_CFG_0 + 0x14)

#define CONFIG_SYS_ST231_DRA2_PERIPH_REG1	(VDEC_PU_CFG_1 + 0x00)
#define CONFIG_SYS_ST231_DRA2_BOOT_REG2		(VDEC_PU_CFG_1 + 0x04)
#define CONFIG_SYS_ST231_AUD1_PERIPH_REG3	(VDEC_PU_CFG_1 + 0x08)
#define CONFIG_SYS_ST231_AUD1_BOOT_REG4		(VDEC_PU_CFG_1 + 0x0c)
#define CONFIG_SYS_ST231_AUD2_PERIPH_REG5	(VDEC_PU_CFG_1 + 0x10)
#define CONFIG_SYS_ST231_AUD2_BOOT_REG6		(VDEC_PU_CFG_1 + 0x14)

#define CONFIG_SYS_REG1_PIO_ALT_DATA_SEL	(VOUT_PU_CFG_1 + 0x00)
#define CONFIG_SYS_REG2_PIO_ALT_DATA_SEL	(VOUT_PU_CFG_1 + 0x04)
#define CONFIG_SYS_REG3_DEBUG_DATA_SEL		(VOUT_PU_CFG_1 + 0x08)
#define CONFIG_SYS_REG4_DAC_CTRL		(VOUT_PU_CFG_1 + 0x0c)
#define CONFIG_SYS_REG5_VOUT_DEBUG_CTL		(VOUT_PU_CFG_1 + 0x10)
#define CONFIG_SYS_REG6_TVOUT_DEBUG_CTL		(VOUT_PU_CFG_1 + 0x14)

/*----------------------------------------------------------------------------*/

/*
 * Base addresses for control register banks.
 */

#ifndef SH4_TMU_REGS_BASE
#define SH4_TMU_REGS_BASE 0xffd80000
#endif

#ifndef ST40_CPG_REGS_BASE
#define ST40_CPG_REGS_BASE 0xffc00000	/* QQQ - need this, check it is correct ? */
#endif

#ifndef STM_EMI_REGS_BASE
#define STM_EMI_REGS_BASE 0xfd100000
#endif


#include <stm/stxxxxxreg.h>


/*----------------------------------------------------------------------------*/

/* Device ID values, masks & predicates */
#define FLI7510_DEVID_7510_VAL		0x23c	/* for cut 0.x */
#define FLI7510_DEVID_ID_SHIFT		12
#define FLI7510_DEVID_ID_MASK		0x3ff
#define FLI7510_DEVID_CUT_SHIFT		28
#define FLI7510_DEVID_CUT_MASK		0xf

#define FLI7510_DEVICEID_7510(ID) ((((ID) >> FLI7510_DEVID_ID_SHIFT) & FLI7510_DEVID_ID_MASK) == FLI7510_DEVID_7510_VAL)
#define FLI7510_DEVICEID_CUT(ID)  ((((ID) >> FLI7510_DEVID_CUT_SHIFT) & FLI7510_DEVID_CUT_MASK) + 0)

#endif /* __INCLUDE_STM_FLI7510REG_H */
