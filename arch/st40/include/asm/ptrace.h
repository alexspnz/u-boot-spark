#ifndef __ARCH_ST40_INCLUDE_ASM_PTRACE_H
#define __ARCH_ST40_INCLUDE_ASM_PTRACE_H

#include <asm/processor.h>
#include <asm/ubc.h>

/*
 * Copyright (C) 1999, 2000  Niibe Yutaka
 *
 */

/*
 * GCC defines register number like this:
 * -----------------------------
 *	 0 - 15 are integer registers
 *	17 - 22 are control/special registers
 *	24 - 39 fp registers
 *	40 - 47 xd registers
 *	48 -    fpscr register
 * -----------------------------
 *
 * We follows above, except:
 *	16 --- program counter (PC)
 *	22 --- expevt # (Exception Event Number)
 *	23 --- floating point communication register
 */
#define REG_REG0	 0
#define REG_REG15	15

#define REG_PC		16

#define REG_PR		17
#define REG_SR		18
#define REG_GBR      	19
#define REG_MACH	20
#define REG_MACL	21

#define REG_EXPEVT	22

#define REG_FPREG0	23
#define REG_FPREG15	38
#define REG_XFREG0	39
#define REG_XFREG15	54

#define REG_FPSCR	55
#define REG_FPUL	56

#define PTRACE_SETOPTIONS         21

/* options set using PTRACE_SETOPTIONS */
#define PTRACE_O_TRACESYSGOOD     0x00000001

/*
 * This struct defines the way the registers are stored on the
 * kernel stack during a system call or other kernel entry.
 */
struct pt_regs
{
	unsigned long regs[16];
	unsigned long pc;
	unsigned long pr;
	unsigned long sr;
	unsigned long gbr;
	unsigned long mach;
	unsigned long macl;
	unsigned long expevt;
};

#ifdef __KERNEL__
#define user_mode(regs) (((regs)->sr & 0x40000000)==0)
#define instruction_pointer(regs) ((regs)->pc)
extern void show_regs (struct pt_regs *);
#endif

#endif /* __ARCH_ST40_INCLUDE_ASM_PTRACE_H */
