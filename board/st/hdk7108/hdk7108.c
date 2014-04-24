/*
 * (C) Copyright 2008-2013 STMicroelectronics.
 *
 * Sean McGoogan <Sean.McGoogan@st.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <stm/soc.h>
#include <stm/stx7108reg.h>
#include <asm/io.h>
#include <stm/pio.h>


void flashWriteEnable(void)
{
	/* Enable Vpp for writing to flash */
	/* QQQ - TO DO */
}

void flashWriteDisable(void)
{
	/* Disable Vpp for writing to flash */
	/* QQQ - TO DO */
}


#define PIOALT(port, pin, alt, dir)			\
do							\
{							\
	stx7108_pioalt_select((port), (pin), (alt));	\
	stx7108_pioalt_pad((port), (pin), (dir));	\
} while(0)

extern int board_early_init_f(void)
{
	/* Setup PIOs for ASC device */

#if CONFIG_SYS_STM_ASC_BASE == STM_ASC1_REGS_BASE

	/* Route UART1 via PIO5 for TX, RX, CTS & RTS (Alternative #1) */
	PIOALT(5, 1, 1, stm_pad_direction_output);	/* UART1-TX */
	PIOALT(5, 2, 1, stm_pad_direction_input);	/* UART1-RX */
	PIOALT(5, 4, 1, stm_pad_direction_output);	/* UART1-RTS */
	PIOALT(5, 3, 1, stm_pad_direction_input);	/* UART1-CTS */

#elif CONFIG_SYS_STM_ASC_BASE == STM_ASC3_REGS_BASE

	/* Route UART3 via PIO24/25 for TX, RX (Alternative #1) */
	PIOALT(24, 4, 1, stm_pad_direction_output);	/* UART3-TX */
	PIOALT(24, 5, 1, stm_pad_direction_input);	/* UART3-RX */
//	PIOALT(24, 7, 1, stm_pad_direction_output);	/* UART3-RTS */
//	PIOALT(25, 0, 1, stm_pad_direction_input);	/* UART3-CTS */

#else
#error Unknown ASC port selected!
#endif	/* CONFIG_SYS_STM_ASC_BASE == STM_ASCx_REGS_BASE */

	/*
	 * Some of the peripherals are powered by regulators
	 * controlled by the following PIO line...
	 *	PIO5[0] == POWER_ON
	 */
	SET_PIO_PIN(STM_PIO_BASE(5), 0, STPIO_OUT);
	STPIO_SET_PIN(STM_PIO_BASE(5), 0, 1);

	return 0;
}

#ifdef CONFIG_DRIVER_NET_STM_GMAC
extern void stmac_phy_reset(void)
{
	/*
	 * Reset the Ethernet PHY.
	 * Note both PHYs share the *same* reset line.
	 *
	 *	PIO15[4] = POWER_ON_ETH (a.k.a. ETH_RESET)
	 */
	STPIO_SET_PIN(STM_PIO_BASE(15), 4, 0);
	udelay(10000);				/* 10 ms */
	STPIO_SET_PIN(STM_PIO_BASE(15), 4, 1);
}
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

extern int board_init(void)
{
#ifdef CONFIG_DRIVER_NET_STM_GMAC
	/*
	 * Configure the Ethernet PHY Reset signal
	 *	PIO15[4] == POWER_ON_ETH (a.k.a. ETH_RESET)
	 */
	SET_PIO_PIN(STM_PIO_BASE(15), 4, STPIO_OUT);
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

#ifdef QQQ	/* QQQ - DELETE */
#if defined(CONFIG_STM_SATA)
	stx7105_configure_sata ();
#endif	/* CONFIG_STM_SATA */
#endif		/* QQQ - DELETE */

#ifdef CONFIG_DRIVER_NET_STM_GMAC
#if CONFIG_SYS_STM_STMAC_BASE == CONFIG_SYS_STM_STMAC0_BASE	/* MII0, on MII JP2 */
	stx7108_configure_ethernet(0, &(struct stx7108_ethernet_config) {
			.mode = stx7108_ethernet_mode_mii,
			.ext_clk = 1,
			.phy_bus = 0, });
#elif CONFIG_SYS_STM_STMAC_BASE == CONFIG_SYS_STM_STMAC1_BASE	/* MII1, IC+ IP1001 (UP1) */
	stx7108_configure_ethernet(1, &(struct stx7108_ethernet_config) {
			.mode = stx7108_ethernet_mode_mii,	/* for MII */
//			.mode = stx7108_ethernet_mode_rmii,	/* for RMII */
			.ext_clk = 0,
			.phy_bus = 1, });
#else
#error Unknown base address for the STM GMAC
#endif
	/* Hard Reset the PHY -- do after we have configured the MAC */
	stmac_phy_reset();
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

#if defined(CONFIG_CMD_I2C)
	stx7108_configure_i2c();
#endif	/* CONFIG_CMD_I2C */

	return 0;
}

int checkboard (void)
{
	printf ("\n\nBoard: STx7108-HDK"
#ifdef CONFIG_ST40_SE_MODE
		"  [32-bit mode]"
#else
		"  [29-bit mode]"
#endif
		"\n");

	return 0;
}
