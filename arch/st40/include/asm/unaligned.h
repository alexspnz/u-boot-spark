#ifndef __ARCH_ST40_INCLUDE_ASM_UNALIGNED_H
#define __ARCH_ST40_INCLUDE_ASM_UNALIGNED_H

/* Copied originally from U-Boot's "arch/sh/include/asm/unaligned.h". */

/*
 * ST40 can not handle unaligned accesses!
 * And, ST40 can only support little-endian.
 */
#include <compiler.h>
#if defined(__LITTLE_ENDIAN__)
#	define get_unaligned   __get_unaligned_le
#	define put_unaligned   __put_unaligned_le
#else
#	error ST40 only suppports litttle-endan
#endif	/* __LITTLE_ENDIAN__ */

#include <linux/unaligned/le_byteshift.h>
#include <linux/unaligned/be_byteshift.h>
#include <linux/unaligned/generic.h>

#endif	/* __ARCH_ST40_INCLUDE_ASM_UNALIGNED_H */
