/*
 * (C) Copyright 2008-2013 STMicroelectronics.
 *
 * Sean McGoogan <Sean.McGoogan@st.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
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


#define PIOALT(port, pin, alt, dir)			\
do							\
{							\
	stxh416_pioalt_select((port), (pin), (alt));	\
	stxh416_pioalt_pad((port), (pin), (dir));	\
} while(0)
#define SYSCONF(_reg)	((unsigned long*)STXH416_SYSCFG(_reg))


/*
 *	MII1: PIO0[7] = RGMII1_notRESET
 */
#if CONFIG_SYS_STM_STMAC_BASE == CONFIG_SYS_STM_STMAC1_BASE	/* MII1, on JE1 */
#	define GMII_PHY_NOT_RESET	0, 7
#else
#	error GMAC #0 is not usable on the B2116 board!
#endif


static void configPIO(void)
{
	/* Setup PIOs for ASC device */

#if CONFIG_SYS_STM_ASC_BASE == STXH416_SBC_ASC0_BASE

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

#ifdef CONFIG_DRIVER_NET_STM_GMAC
	/*
	 * Configure the Ethernet PHY Reset signal
	 */
	SET_PIO_PIN2(GMII_PHY_NOT_RESET, STPIO_OUT);
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */
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
			STM_PAD_SYSCONF(SYSCONF(508), 6, 8, 1);
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
			STM_PAD_SYSCONF(SYSCONF(508), 6, 8, 7);
		stm_configure_sysconfs(&gbit_sc, 1);
		writel(0x1F/*800MHz/(31+1)=25MHz*/, 0xFEE62B20/*CKGA0_PLL1_DIV8_CFG*/);
	}
}
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */


extern int board_init(void)
{
	configPIO();

#if 0	/* QQQ - TO IMPLEMENT */
#if defined(CONFIG_STM_SATA)
	stx7105_configure_sata ();
#endif	/* CONFIG_STM_SATA */
#endif	/* QQQ - TO IMPLEMENT */

#ifdef CONFIG_DRIVER_NET_STM_GMAC
#if CONFIG_SYS_STM_STMAC_BASE == CONFIG_SYS_STM_STMAC1_BASE	/* MII1 */
#	if defined(CONFIG_STMAC_RTL8211E)	/* Realtek RTL8211E PHY (UE1) */
	stxh416_configure_ethernet(1, &(struct stxh416_ethernet_config) {
			.mode = stxh416_ethernet_mode_rgmii,
			.ext_clk = 1,
			.phy_bus = 1, });
#	else
#	error Unknown PHY type associated with STM GMAC #1
#	endif	/* CONFIG_STMAC_RTL8211E */
#else
#error Unknown base address for the STM GMAC
#endif
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

#if defined(CONFIG_CMD_I2C)
	stxh416_configure_i2c();
#endif	/* CONFIG_CMD_I2C */

	return 0;
}


int checkboard (void)
{
	printf ("\n\nBoard: B2116-STxH315"
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
	stxh416_configure_spi();
#endif	/* CONFIG_SPI */

#if defined(CONFIG_DRIVER_NET_STM_GMAC)
	/* Hard Reset the PHY -- do after we have configured the MAC */
	stmac_phy_reset();
#endif	/* CONFIG_DRIVER_NET_STM_GMAC */

	return 0;
}
