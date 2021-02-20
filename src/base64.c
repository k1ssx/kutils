#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



const char* progName = "base64";
const char* progVer = "1.0.0";

static const char* const usage[] = {
	"base64 [-di] [-w COLS] [FILE]",
	NULL
};

unsigned char b64_chr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned int b64_int(unsigned int ch) {

	// ASCII to base64_int
	// 65-90  Upper Case  >>  0-25
	// 97-122 Lower Case  >>  26-51
	// 48-57  Numbers     >>  52-61
	// 43     Plus (+)    >>  62
	// 47     Slash (/)   >>  63
	// 61     Equal (=)   >>  64~
	if (ch==43)
	return 62;
	if (ch==47)
	return 63;
	if (ch==61)
	return 64;
	if ((ch>47) && (ch<58))
	return ch + 4;
	if ((ch>64) && (ch<91))
	return ch - 'A';
	if ((ch>96) && (ch<123))
	return (ch - 'a') + 26;
	return 0;
}

unsigned int b64e_size(unsigned int in_size) {

	// size equals 4*floor((1/3)*(in_size+2));
	int i, j = 0;
	for (i=0;i<in_size;i++) {
		if (i % 3 == 0)
		j += 1;
	}
	return (4*j);
}

unsigned int b64d_size(unsigned int in_size) {

	return ((3*in_size)/4);
}

unsigned int b64_encode(const unsigned char* in, unsigned int in_len, unsigned char* out) {

	unsigned int i=0, j=0, k=0, s[3];
	
	for (i=0;i<in_len;i++) {
		s[j++]=*(in+i);
		if (j==3) {
			out[k+0] = b64_chr[ (s[0]&255)>>2 ];
			out[k+1] = b64_chr[ ((s[0]&0x03)<<4)+((s[1]&0xF0)>>4) ];
			out[k+2] = b64_chr[ ((s[1]&0x0F)<<2)+((s[2]&0xC0)>>6) ];
			out[k+3] = b64_chr[ s[2]&0x3F ];
			j=0; k+=4;
		}
	}
	
	if (j) {
		if (j==1)
			s[1] = 0;
		out[k+0] = b64_chr[ (s[0]&255)>>2 ];
		out[k+1] = b64_chr[ ((s[0]&0x03)<<4)+((s[1]&0xF0)>>4) ];
		if (j==2)
			out[k+2] = b64_chr[ ((s[1]&0x0F)<<2) ];
		else
			out[k+2] = '=';
		out[k+3] = '=';
		k+=4;
	}

	out[k] = '\0';
	
	return k;
}

unsigned int b64_decode(const unsigned char* in, unsigned int in_len, unsigned char* out) {

	unsigned int i=0, j=0, k=0, s[4];
	
	for (i=0;i<in_len;i++) {
		s[j++]=b64_int(*(in+i));
		if (j==4) {
			out[k+0] = ((s[0]&255)<<2)+((s[1]&0x30)>>4);
			if (s[2]!=64) {
				out[k+1] = ((s[1]&0x0F)<<4)+((s[2]&0x3C)>>2);
				if ((s[3]!=64)) {
					out[k+2] = ((s[2]&0x03)<<6)+(s[3]); k+=3;
				} else {
					k+=2;
				}
			} else {
				k+=1;
			}
			j=0;
		}
	}
	
	return k;
}

bool isbase64(char c) {
	return ((c < 58 && c > 46) || (c < 91 && c > 64) || (c < 123 && c > 96) ||
			(c == 43));
}

void wrap_write() {

}

#define B64_DEC_SZ (1024*3) 

void do_decode(FILE* in, FILE* out, bool ignore) {
	char inbuf[b64d_size(B64_DEC_SZ)];
	char outbuf[B64_DEC_SZ];
	size_t sum = 0;
	do {
		size_t n;

		sum = 0;
		while(sum < b64d_size(B64_DEC_SZ) && !feof(in)) {
			n = fread(&inbuf + sum, 1, b64d_size(B64_DEC_SZ) - sum, in);
		 	if(ignore) { // Ignore garbage.
				for(size_t i = 0; n > 0 && i < n;) {
					if(isbase64(inbuf[sum + i]) || inbuf[sum + i] == '=')
						i++;
					else {
						memmove(inbuf + sum + i, inbuf + sum + i + 1, --n - i);
					}
				}
		 	}
		 	sum += n;
		 	if(ferror(in)) {
				 die("File Read error");
		 	}	
		}
		


	} while(!feof(in));
}

void do_encode() {
}

int main(int argc, const char** argv) {
	int decode = 0;
	int ignore_garbage = 0;
	int wrap = 76;
	struct argparse_option options[] = {
		OPT_MYHELP(),
		OPT_BOOLEAN('d', "decode", &decode, "decode data"),
		OPT_BOOLEAN('i', "ignore-garbage", &ignore_garbage, "when decoding, ignore non-alphabet character"),
		OPT_INTEGER('w', "wrap", &wrap, "wrap encoded lines after COLS character (default 76). Use 0 to disable line wrapping"),
		OPT_END()
	};
	struct argparse argp;
	argparse_init(&argp, options, usage, 0);
	argparse_describe(&argp, "base64 encode/decode data and print to standard output", NULL);
	argc = argparse_parse(&argp, argc, argv);
	if(argc != 1) {
		die("Missing [FILE] argument");
	}
	const char* file = argv[argc -1];
	
	if(strcmp(file, "-") == 0) {
		
	}
	/* Program goes here.
	 */
	if(decode == 1) {
//		do_decode();
	} else {
		do_encode();
	}
	return 0;
}


