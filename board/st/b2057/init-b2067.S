/*
 * The poke table is a series of long words, in the format
 *
 *	opcode, address, operand, ...
 *
 * An opcode of 0 marks the table end
 */


#include <stm/stxh205reg.h>
#include "../../../arch/st40/cpu/init_ram.S"


	.section .data.init, "a"

	.balign 32

__memory_setup_table:

	/*
	 * include the appropriate set of "GDB pokes", (usually) generated
	 * using the "romgen" utility, from a known good target-pack.
	 *
	 * This file may be regenerated by executing the following
	 * command (redirecting the output), *without* needing any
	 * access to either a MicroConnect or a target board:
	 *
	 * host% romgen --show-comment dummy:b2067stxh205:st40,boot_companions=0,se=0
	 *
	 * Where "dummy" need not correspond to any real IP address on
	 * your network.  In addition, note that "b2067stxh205" should
	 * substituted if you have a custom target-pack connect command.
	 *
	 * It should be noted that the above command explicitly includes
	 * the option "se=0", which disables SE (or 32-bit) mode. This is
	 * correct, even though you may be using 32-bit mode at run-time.
	 * The "GDB pokes" are presently always executed in a 29-bit context,
	 * hence the need to disable 32-bit mode when running "romgen".
	 *
	 * For the B2067 board, the following options should typically
	 * always also be used when running romgen:
	 *		lmi_freq=266
	 *		lmi_16bits=1
	 * i.e.
	 * host% romgen --show-comment dummy:b2067stxh205:st40,boot_companions=0,se=0,lmi_freq=266,lmi_16bits=1
	 *
	 * Note: do not use "spi_4x=1" on B2067A (but, should be okay on rev B).
	 */
#include "b2067-stxh205.romgen"

	END_MARKER

__memory_setup_table_end:

	.end
