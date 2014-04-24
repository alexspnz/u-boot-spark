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
#include <stm/socregs.h>
#include <asm/io.h>
#include <stm/pio.h>
#include <stm/sysconf.h>


void flashWriteEnable(void)
{
	/* Enable Vpp for writing to flash */
	/* Nothing to do! */
}

void flashWriteDisable(void)
{
	/* Disable Vpp for writing to flash */
	/* Nothing to do! */
}


#if defined(CONFIG_STM_STXH415)
#define PIOALT(port, pin, alt, dir)			\
do							\
{							\
	stxh415_pioalt_select((port), (pin), (alt));	\
	stxh415_pioalt_pad((port), (pin), (dir));	\
} while(0)
#define SYSCONF(_reg)	((unsigned long*)STXH415_SYSCFG(_reg))
#elif defined(CONFIG_STM_STXH416)
#define PIOALT(port, pin, alt, dir)			\
do							\
{							\
	stxh416_pioalt_select((port), (pin), (alt));	\
	stxh416_pioalt_pad((port), (pin), (dir));	\
} while(0)
#define SYSCONF(_reg)	((unsigned long*)STXH416_SYSCFG(_reg))
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */


/*
 *	MII1: PIO3[0] = RGMII1_notRESET
 */
#if CONFIG_SYS_STM_STMAC_BASE == CONFIG_SYS_STM_STMAC1_BASE	/* MII1, on U77 */
#	define GMII_PHY_NOT_RESET	3, 0
#else
#	error GMAC #0 is not usable on the B2020 board!
#endif


extern int board_early_init_f(void)
{
	/* Setup PIOs for ASC device */

#if defined(CONFIG_STM_STXH415)
#if CONFIG_SYS_STM_ASC_BASE == STXH415_ASC2_BASE

	/* Route UART2 via PIO17 for TX, RX, CTS & RTS (Alternative #1) */
	PIOALT(17, 4, 2, stm_pad_direction_output);	/* UART2-TX */
	PIOALT(17, 5, 2, stm_pad_direction_input);	/* UART2-RX */
//	PIOALT(17, 7, 2, stm_pad_direction_output);	/* UART2-RTS */
//	PIOALT(17, 6, 2, stm_pad_direction_input);	/* UART2-CTS */

#elif CONFIG_SYS_STM_ASC_BASE == STXH415_SBC_ASC0_BASE

	/* Route SBC_UART0 via PIO3 for TX, RX, CTS & RTS (Alternative #1) */
	PIOALT(3, 4, 1, stm_pad_direction_output);	/* SBC_UART0-TX */
	PIOALT(3, 5, 1, stm_pad_direction_input);	/* SBC_UART0-RX */
//	PIOALT(3, 7, 1, stm_pad_direction_output);	/* SBC_UART0-RTS */
//	PIOALT(3, 6, 1, stm_pad_direction_input);	/* SBC_UART0-CTS */

#elif CONFIG_SYS_STM_ASC_BASE == STXH415_SBC_ASC1_BASE

	/* Route SBC_UART1 via PIO2,3 for TX, RX, CTS & RTS (Alternative #3) */
	PIOALT(2, 6, 3, stm_pad_direction_output);	/* SBC_UART1-TX */
	PIOALT(2, 7, 3, stm_pad_direction_input);	/* SBC_UART1-RX */
//	PIOALT(3, 1, 3, stm_pad_direction_output);	/* SBC_UART1-RTS */
//	PIOALT(3, 0, 3, stm_pad_direction_input);	/* SBC_UART1-CTS */

#else
#error Unknown ASC port selected!
#endif	/* CONFIG_SYS_STM_ASC_BASE == STXH415_ASCx_REGS_BASE */

#elif defined(CONFIG_STM_STXH416)
#if CONFIG_SYS_STM_ASC_BASE == STXH416_ASC2_BASE

	/* Route UART2 via PIO17 for TX, RX, CTS & RTS (Alternative #1) */
	PIOALT(17, 4, 2, stm_pad_direction_output);	/* UART2-TX */
	PIOALT(17, 5, 2, stm_pad_direction_input);	/* UART2-RX */
//	PIOALT(17, 7, 2, stm_pad_direction_output);	/* UART2-RTS */
//	PIOALT(17, 6, 2, stm_pad_direction_input);	/* UART2-CTS */

#elif CONFIG_SYS_STM_ASC_BASE == STXH416_SBC_ASC0_BASE

	/* Route SBC_UART0 via PIO3 for TX, RX, CTS & RTS (Alternative #1) */
	PIOALT(3, 4, 1, stm_pad_direction_output);	/* SBC_UART0-TX */
	PIOALT(3, 5, 1, stm_pad_direction_input);	/* SBC_UART0-RX */
//	PIOALT(3, 7, 1, stm_pad_direction_output);	/* SBC_UART0-RTS */
//	PIOALT(3, 6, 1, stm_pad_direction_input);	/* SBC_UART0-CTS */

#elif CONFIG_SYS_STM_ASC_BASE == STXH416_SBC_ASC1_BASE

	/* Route SBC_UART1 via PIO2,3 for TX, RX, CTS & RTS (Alternative #3) */
	PIOALT(2, 6, 3, stm_pad_direction_output);	/* SBC_UART1-TX */
	PIOALT(2, 7, 3, stm_pad_direction_input);	/* SBC_UART1-RX */
//	PIOALT(3, 1, 3, stm_pad_direction_output);	/* SBC_UART1-RTS */
//	PIOALT(3, 0, 3, stm_pad_direction_input);	/* SBC_UART1-CTS */

#else
#error Unknown ASC port selected!
#endif	/* CONFIG_SYS_STM_ASC_BASE == STXH416_ASCx_REGS_BASE */
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */

	return 0;
}


#ifdef CONFIG_DRIVER_NET_STM_GMAC
extern void stmac_phy_reset(void)
{
	/*
	 * Reset the Ethernet PHY.
	 */
	STPIO_SET_PIN2(GMII_PHY_NOT_RESET, 1);
	udelay(10000);				/* 10 ms */
	STPIO_SET_PIN2(GMII_PHY_NOT_RESET, 0);
	udelay(10000);				/* 10 ms */
	STPIO_SET_PIN2(GMII_PHY_NOT_RESET, 1);
	udelay(10000);				/* 10 ms */
}
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */


#ifdef CONFIG_DRIVER_NET_STM_GMAC
extern void stmac_set_mac_speed(int speed)
{
	/*
	 * Manage the MAC speed
	 */
	if (speed==1000)	/* Gigabit ? */
	{
		/*
		 * Output clock driven by MII_TXCLK.
		 * 125MHz Clock from PHY is used for retiming and also to drive GTXCLK.
		 */
		const struct stm_pad_sysconf gbit_sc =
#if defined(CONFIG_STM_STXH415)
			STM_PAD_SYSCONF(SYSCONF(29), 6, 8, 1);
#elif defined(CONFIG_STM_STXH416)
			STM_PAD_SYSCONF(SYSCONF(508), 6, 8, 1);
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */
		stm_configure_sysconfs(&gbit_sc, 1);
	}
	else
	{
		/*
		 * Output clock driven by Clockgen.
		 * 125MHz clock provided by PHY is not suitable for retiming.
		 * So TXPIO retiming must therefore be clocked by an
		 * internal 2.5/25MHz clock generated by Clockgen.
		 */
		const struct stm_pad_sysconf gbit_sc =
#if defined(CONFIG_STM_STXH415)
			STM_PAD_SYSCONF(SYSCONF(29), 6, 8, 7);
#elif defined(CONFIG_STM_STXH416)
			STM_PAD_SYSCONF(SYSCONF(508), 6, 8, 7);
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */
		stm_configure_sysconfs(&gbit_sc, 1);
		writel(0x1F/*800MHz/(31+1)=25MHz*/, 0xFEE62B20/*CKGA0_PLL1_DIV8_CFG*/);
	}
}
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */


extern int board_init(void)
{
#ifdef CONFIG_DRIVER_NET_STM_GMAC
	/*
	 * Configure the Ethernet PHY Reset signal
	 */
	SET_PIO_PIN2(GMII_PHY_NOT_RESET, STPIO_OUT);
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

#if 0	/* QQQ - TO IMPLEMENT */
#if defined(CONFIG_STM_SATA)
	stx7105_configure_sata ();
#endif	/* CONFIG_STM_SATA */
#endif	/* QQQ - TO IMPLEMENT */

#ifdef CONFIG_DRIVER_NET_STM_GMAC
#if CONFIG_SYS_STM_STMAC_BASE == CONFIG_SYS_STM_STMAC1_BASE	/* MII1 */
#	if defined(CONFIG_STMAC_IP1001)		/* IC+ IP1001 (U77) */
#if defined(CONFIG_STM_STXH415)
	stxh415_configure_ethernet(1, &(struct stxh415_ethernet_config) {
			.mode = stxh415_ethernet_mode_rgmii,
			.ext_clk = 1,
			.phy_bus = 1, });
#elif defined(CONFIG_STM_STXH416)
	stxh416_configure_ethernet(1, &(struct stxh416_ethernet_config) {
			.mode = stxh416_ethernet_mode_rgmii,
			.ext_clk = 1,
			.phy_bus = 1, });
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */
#	else
#	error Unknown PHY type associated with STM GMAC #1
#	endif	/* CONFIG_STMAC_IP1001 */
#else
#error Unknown base address for the STM GMAC
#endif
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

#if defined(CONFIG_CMD_I2C)
#if defined(CONFIG_STM_STXH415)
	stxh415_configure_i2c();
#elif defined(CONFIG_STM_STXH416)
	stxh416_configure_i2c();
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */
#endif	/* CONFIG_CMD_I2C */

	return 0;
}


int checkboard (void)
{
	printf ("\n\nBoard: B2020"
#if defined(CONFIG_STM_STXH415)
		"-STxH415"
#elif defined(CONFIG_STM_STXH416)
		"-STxH416"
#endif
#if defined(CONFIG_ARM)
		"  [ARM]"
#elif defined(CONFIG_ST40_SE_MODE)
		"  [32-bit mode]"
#else
		"  [29-bit mode]"
#endif
		"\n");

#if defined(CONFIG_SOFT_SPI)
	/*
	 * Configure for the SPI Serial Flash.
	 * Note: for CONFIG_SYS_BOOT_FROM_SPI + CONFIG_ENV_IS_IN_EEPROM, this
	 * needs to be done after env_init(), hence it is done
	 * here, and not in board_init().
	 */
#if defined(CONFIG_STM_STXH415)
	stxh415_configure_spi();
#elif defined(CONFIG_STM_STXH416)
	stxh416_configure_spi();
#endif	/* CONFIG_STM_STXH415/CONFIG_STM_STXH416 */
#endif	/* CONFIG_SPI */

#if defined(CONFIG_DRIVER_NET_STM_GMAC)
	/* Hard Reset the PHY -- do after we have configured the MAC */
	stmac_phy_reset();
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

	return 0;
}


