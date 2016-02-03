// Copyright (c) 2011 Synopsys, Inc.
// All rights reserved worldwide.

#ifndef	_JPEG_GLOBALS_H
#define	_JPEG_GLOBALS_H

#include "global_defs.h"

extern void inc_jpeg_ptr(int);
extern void get_compressed_16(void);
extern int get_compressed_byte(void);
extern int get_compressed_half(void);

#define FRAME_BUF_SIZE	1024

struct huff_table 
{
	uint32	xC_max[5];
	char *	xC_offset[17];
	char	RS_symbols[256];
};

struct component_descriptor 
{
	char *	dct_ptr;
	int		Td, Ta;
	int	  	repeat_number;
	int	  	component_id;
	int *	Qp_table;
	int		color;
#ifdef FAST_ZERO
	char *  last_cleared;
#endif
};

struct component_spec
{
	short 	C;  /* Component id               */
	int   	H;  /* Horizontal sampling factor */
	int   	V;  /* Vertical   sampling factor */
	int   	Tq; /* Quantization table         */
};


/* new main control block */

#define NH 6
typedef struct ctrl_t
{ 
	int		Qp[4][64];          /* Dequantization tables */
	char *	zigzag_order ;
	char *	k_table ;
	int  *	unzigzag ;
	int  *	unzigzag_transpose ;

	/* frame variables */
	int 	frame_Hmax;
	int 	frame_Vmax;
	int 	frame_P;
	int 	frame_Y;
	int 	frame_X;
	int 	frame_Nf;

	/* scan variables */
	int 	scan_Ns;
	int 	scan_Ss;
	int 	scan_Se;
	int 	scan_Ah;
	int 	scan_Al;

	struct	component_spec * components;

	int *	scale_table_consts ;

	struct	component_descriptor mcu_desc_array[17];

	struct 	huff_table * DC_huff_table_ptr[4];  /* DC Huffman tables */
	struct 	huff_table * AC_huff_table_ptr[4];  /* AC Huffman tables */

	short 	DC_fast_huff_table_dec_ptr[4][(1<<NH)];  /* Fast DC Huffman tables */
	short 	AC_fast_huff_table_dec_ptr[4][(1<<NH)];  /* Fast AC Huffman tables */

	int 	predictor[4];

	int 	current_column[8];

	int 	nsave_count[16];
	int 	eob_count[65];

	int 	old_code_count;
	int 	new_code_count;

	char **	decompressBuffer ;
	int   	bytes_in_dec_buffer[4] ;

} ctrl_t;


#define MAX_DCT_STRUCT_SIZE 134  /* 64 AC/DC halfwords + length, eob fields */

/* DCT constants   */

/* derived from flow graph on page 52 of the JPEG book */

#define AP    12

#if AP == 8
                       /* Ck = cos (k*pi/16)            */
#define A1  181        /* cos(2pi/8) = C4               */
#define A2  138        /* cos(pi/8)-cos(3pi/8) = C2-C6  */
#define A3  181        /* cos(2pi/8) = C4               */
#define A4  334        /* cos(pi/8)+cos(3pi/8) = C2+C6  */
#define A5   98        /* cos(3pi/8) = C6               */

#endif
#if AP == 9

#define A1  362        /* cos(2pi/8) = C4               */
#define A2  277        /* cos(pi/8)-cos(3pi/8) = C2-C6  */
#define A3  362        /* cos(2pi/8) = C4               */
#define A4  669        /* cos(pi/8)+cos(3pi/8) = C2+C6  */
#define A5  196        /* cos(3pi/8) = C6               */

#endif

#if AP == 10

#define A1  724        /* cos(2pi/8) = C4               */
#define A2  554        /* cos(pi/8)-cos(3pi/8) = C2-C6  */
#define A3  724        /* cos(2pi/8) = C4               */
#define A4  1338       /* cos(pi/8)+cos(3pi/8) = C2+C6  */
#define A5  392        /* cos(3pi/8) = C6               */

#endif

#if AP == 11

#define A1  1448       /* cos(2pi/8) = C4               */
#define A2  1108       /* cos(pi/8)-cos(3pi/8) = C2-C6  */
#define A3  1448       /* cos(2pi/8) = C4               */
#define A4  2676       /* cos(pi/8)+cos(3pi/8) = C2+C6  */
#define A5  784        /* cos(3pi/8) = C6               */

#endif

#if AP == 12

#define A1  2896       /* cos(2pi/8) = C4               */
#define A2  2217      /* cos(pi/8)-cos(3pi/8) = C2-C6  */
#define A3  2896       /* cos(2pi/8) = C4               */
#define A4  5352       /* cos(pi/8)+cos(3pi/8) = C2+C6  */
#define A5  1568       /* cos(3pi/8) = C6               */

#endif

#define A1F (cos(2*PI/8))
#define A2F (cos(PI/8)-cos(3*PI/8))
#define A3F (cos(2*PI/8))
#define A4F (cos(PI/8)+cos(3*PI/8))
#define A5F (cos(3*PI/8))


#ifdef USE_FP_A_CONSTS
#define DECLARE_SW_MULT_VARIABLE()
#define MULT_BY_A1(x) x*=A1F;
#define MULT_BY_A2(x) x*=A2F;
#define MULT_BY_A3(x) x*=A3F;
#define MULT_BY_A4(x) x*=A4F;
#define MULT_BY_A5(x) x*=A5F;


#else
#define DECLARE_SW_MULT_VARIABLE()
#define MULT_BY_A1(x) x*=A1; x=x>>AP;
#define MULT_BY_A2(x) x*=A2; x=x>>AP;
#define MULT_BY_A3(x) x*=A3; x=x>>AP;
#define MULT_BY_A4(x) x*=A4; x=x>>AP;
#define MULT_BY_A5(x) x*=A5; x=x>>AP;
#endif



#define MARKER_MARKER 0xff
#define MARKER_SOI    0xd8
#define MARKER_EOI    0xd9
#define MARKER_SOS    0xda
#define MARKER_DQT    0xdb
#define MARKER_DNL    0xdc
#define MARKER_DRI    0xdd
#define MARKER_DHP    0xde
#define MARKER_EXP    0xdf
#define MARKER_SOF0   0xc0
#define MARKER_SOF1   0xc1
#define MARKER_SOF2   0xc2
#define MARKER_SOF3   0xc3
#define MARKER_SOF5   0xc5
#define MARKER_SOF6   0xc6
#define MARKER_SOF7   0xc7
#define MARKER_SOF9   0xc9
#define MARKER_SOF10  0xca
#define MARKER_SOF11  0xcb
#define MARKER_SOF13  0xcd
#define MARKER_SOF14  0xce
#define MARKER_SOF15  0xcf
#define MARKER_DHT    0xc4
#define MARKER_JPG    0xc8
#define MARKER_DAC    0xcc
#define MARKER_COM    0xfe
#define MARKER_APP0   0xe0
#define MARKER_APP15  0xef

/* ------------- Error constants ------------- */
#define E_ERROR_IN_HUFFMAN_TABLE 		1
#define E_MALLOC_FAILED		 			2
#define E_FIRST_BYTE_NOT_MARKER			3
#define E_FIRST_MARKER_NOT_SOI			4
#define E_EXPECTED_MARKER_NOT_FOUND 	5
#define E_UNKNOWN_MARKER				6
#define E_RESERVED_MARKER_FOUND			7
#define E_ERROR_OPEN_FILE				8
#define E_ERROR_STAT_FILE				9
#define E_FILE_SIZE_MISMATCH           10




/* --------------- DCT     funcs----------------------*/
#define SCALE_POWER 12
#define SCALE (1<<SCALE_POWER) /* 2**8 */


/* Define the clock speed, for times in main.c */
#ifdef CLOCK50
#define CLOCK_SPD 50000
#endif
#ifdef CLOCK33
#define CLOCK_SPD 33000   /* should be 33333 */
#endif


#endif	// _JPEG_GLOBALS_H

