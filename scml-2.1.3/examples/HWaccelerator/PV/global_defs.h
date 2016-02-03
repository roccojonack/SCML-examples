#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

typedef unsigned int	uint32;
typedef unsigned short	ushort;
typedef unsigned char	uchar;

#ifndef MAX
#define   MAX(a,b)             (((a)>(b))?(a):(b))
#endif

#define INT_DISABLE      0x000000C0  // Disable IRQ and FIQ
#define INT_ENABLE       0xFFFFFF3F  // Enable IRQ and FIQ
#define INT_DISABLE_IRQ  0x00000080  // Disable IRQ
#define INT_DISABLE_FIQ  0x00000040  // Disable FIQ
#define INT_ENABLE_IRQ   0xFFFFFF7F  // Enable IRQ
#define INT_ENABLE_FIQ   0xFFFFFFBF  // Enable FIQ

#define CACHE_DISABLE    0xFFFFEFFB  // Disable Dcache and Icache
#define CACHE_ENABLE     0x00001004  // Enable Dcache and Icache
#define CACHE_DISABLE_D  0xFFFFFFFB  // Disable Dcache
#define CACHE_DISABLE_I  0xFFFFEFFF  // Disable Icache
#define CACHE_ENABLE_D   0x00000004  // Enable Dcache
#define CACHE_ENABLE_I   0x00001000  // Enable Icache

#endif
