/*
 * (C) Copyright 2006 DENX Software Engineering
 * (C) Copyright 2008-2010 STMicroelectronics, Sean McGoogan <Sean.McGoogan@st.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/pio.h>
#include <asm/fli7540reg.h>
#include <asm/stm-nand.h>


/*
 * Board-specific NAND initialization. The following members of the
 * argument are board-specific (per include/linux/mtd/nand.h):
 * - IO_ADDR_R?: address to read the 8 I/O lines of the flash device
 * - IO_ADDR_W?: address to write the 8 I/O lines of the flash device
 * - hwcontrol: hardwarespecific function for accesing control-lines
 * - dev_ready: hardwarespecific function for  accesing device ready/busy line
 * - enable_hwecc?: function to enable (reset)  hardware ecc generator. Must
 *   only be provided if a hardware ECC is available
 * - eccmode: mode of ecc, see defines
 * - chip_delay: chip dependent delay for transfering data from array to
 *   read regs (tR)
 * - options: various chip options. They can partly be set to inform
 *   nand_scan about special functionality. See the defines for further
 *   explanation
 * Members with a "?" were not set in the merged testing-NAND branch,
 * so they are not set here either.
 */
#ifdef CFG_NAND_FLEX_MODE	/* for STM "flex-mode" (c.f. "bit-banging") */
extern int board_nand_init(struct nand_chip *nand)
{
	nand->eccmode       = NAND_ECC_SOFT;
	nand->options       = NAND_NO_AUTOINCR;

	nand->select_chip   = stm_flex_select_chip;
	nand->dev_ready     = stm_flex_device_ready;
	nand->hwcontrol     = stm_flex_hwcontrol;
	nand->read_byte     = stm_flex_read_byte;
	nand->write_byte    = stm_flex_write_byte;
	nand->read_buf      = stm_flex_read_buf;
	nand->write_buf     = stm_flex_write_buf;

	/* override scan_bbt(), even if not using a Bad Block Table (BBT) */
	nand->scan_bbt      = stm_nand_default_bbt;

#if 1	/* Enable to use a NAND-resident (non-volatile) Bad Block Table (BBT) */
	nand->options      |= NAND_USE_FLASH_BBT;
#endif

	return 0;
}
#else
#error It is not possible to use bit-banging with NAND on the Freeman Ultra Development Board.
#endif /* CFG_NAND_FLEX_MODE */


