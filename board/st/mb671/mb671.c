/*
 * (C) Copyright 2007-2009 STMicroelectronics.
 *
 * Stuart Menefy <stuart.menefy@st.com>
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
#include <stm/stx7200reg.h>
#include <asm/io.h>
#include <stm/pio.h>

#ifdef CONFIG_ST40_SE_MODE
#define EPLD_BASE		0xb5000000	/* Phys 0x05000000 */
#else
#define EPLD_BASE		0xa5000000
#endif	/* CONFIG_ST40_SE_MODE */

#define EPLD_FlashCtrlAddr	STM_U16_REG(EPLD_BASE + 0x400000)

extern void flashWriteEnable(void)
{
	/*  Enable vpp for writing to flash */
	*EPLD_FlashCtrlAddr = 3;
}

extern void flashWriteDisable(void)
{
	/*  Disable vpp for writing to flash */
	*EPLD_FlashCtrlAddr = 2;
}

#define PIO_BASE  0xfd020000

static void configPIO(void)
{
	/*  Setup PIO of ASC device */
	SET_PIO_ASC(PIO_PORT(4), 3, 2, 4, 5);  /* UART2 - AS0 */
	SET_PIO_ASC(PIO_PORT(5), 4, 3, 5, 6);  /* UART3 - AS1 */
}

extern int board_init(void)
{
	unsigned long sysconf;

	/* Serial port set up */
	/* Route UART2&3 or SCI inputs instead of DVP to pins: conf_pad_dvp = 0 */
	sysconf = *STX7200_SYSCONF_SYS_CFG40;
	sysconf &= ~(1<<16);
	*STX7200_SYSCONF_SYS_CFG40 = sysconf;

	/* Route UART2&3/SCI outputs instead of DVP to pins: conf_pad_pio[1]=0 */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf &= ~(1<<25);
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* No idea, more routing: conf_pad_pio[0] = 0 */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf &= ~(1<<24);
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* Route UART2 (inputs and outputs) instead of SCI to pins: ssc2_mux_sel = 0 */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf &= ~(1<<2);
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* conf_pad_pio[4] = 0 */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf &= ~(1<<28);
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* Route UART3 (inputs and outputs) instead of SCI to pins: ssc3_mux_sel = 0 */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf &= ~(1<<3);
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* conf_pad_clkobs = 1 */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf |= (1<<14);
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* I2C and USB related routing */
	/* bit4: ssc4_mux_sel = 0 (treat SSC4 as I2C) */
	/* bit26: conf_pad_pio[2] = 0 route USB etc instead of DVO */
	/* bit27: conf_pad_pio[3] = 0 DVO output selection (probably ignored) */
	sysconf = *STX7200_SYSCONF_SYS_CFG07;
	sysconf &= ~((1<<27)|(1<<26)|(1<<4));
	*STX7200_SYSCONF_SYS_CFG07 = sysconf;

	/* Enable SOFT_JTAG mode.
	 * Taken from OS21, but is this correct?
	 */
	sysconf = *STX7200_SYSCONF_SYS_CFG33;
	sysconf |= (1<<6);
	sysconf &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));
	*STX7200_SYSCONF_SYS_CFG33 = sysconf;

	configPIO();

	return 0;
}


extern int checkboard (void)
{
	printf ("\n\nBoard: STx7200-Reference (MB671)"
#ifdef CONFIG_ST40_SE_MODE
		"  [32-bit mode]"
#else
		"  [29-bit mode]"
#endif
		"\n");

#ifdef CONFIG_DRIVER_NETSTMAC
#if defined(CONFIG_STMAC_MAC0)
	/* On-board PHY on MII0 in RMII mode, using MII_CLK */
	stx7200_configure_ethernet (0, 1, 0, 0);
#elif defined(CONFIG_STMAC_MAC1)
	/* External PHY on MII1 in MII mode, using its own clock */
	stx7200_configure_ethernet (1, 0, 1, 1);
#endif
#endif	/* CONFIG_DRIVER_NETSTMAC */

#if defined(CONFIG_STM_SATA)
	stx7200_configure_sata ();
#endif	/* CONFIG_STM_SATA */

	return 0;
}
