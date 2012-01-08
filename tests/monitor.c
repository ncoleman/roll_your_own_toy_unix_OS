/*
* =====================================================================================
*
*       Filename:  monitor.c
*
*    Description:  
*
*        Version:  1.0
*        Created:  01/07/12 17:57:25
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Nick Coleman (), 
*        Company:  
*
* =====================================================================================
*/

#include	"monitor.h"


void monitor_write_hex(u32int n) {
    // since the int is guaranteed to be 4 bytes, just use 4 simple masks rather than bother with looping through.
    char HEX[] = "0123456789ABCDEF";
    // 6 chars of FFFFFF plus 1 terminator; prefill it with null-terminaters
    const u8int MAX_CHARS = 6;
    char hex_string[MAX_CHARS + 1];
    hex_string[0] = '\0';
    u8int i = 0; u8int j = 0;
    for (i=0 ; i < MAX_CHARS ; i++) {
	// mask in only the relevant byte, then shift it to LSB.
	// mask is shifted in decrementing amounts of 4 to the left.
	// e.g. 0xF00000 which is 0xF << 20, then << 16, then << 12, etc
	// LSB is the result from applying the mask then shifted to the right by 20, then 16, then 12, etc.
	hex_string[i] = HEX[(n & (0xF << (4*(MAX_CHARS - 1 - i)))) >> (20-i*4)];		    // mask in only the relevant byte, then shift it to LSB to use as an index
    }
    hex_string[i] = '\0';
    /*  
    hex_string[1] = HEX[(n && 0x0F0000) >> 20];		    // mask in only the relevant byte, then shift it to LSB to use as an index
    hex_string[2] = HEX[(n && 0x00F000) >> 16];
    hex_string[3] = HEX[(n && 0x000F00) >> 8];
    hex_string[4] = HEX[(n && 0x0000F0) >> 4];
    hex_string[5] = HEX[n && 0x000000F];*/
    // remove leading '0' chars
    i = 0 ; j = 0;
    while (!(hex_string[i] - '0'))				    // find first char not '0'
	i++;
    if (i) {							    // i is not zero, so there were some leading '0' chars
	while ( hex_string[i] != '\0' ) 
	    hex_string[j++] = hex_string[i++];			    // move the chars to the beginning
	hex_string[j] = '\0';					    // suppend the terminater
    }
    printf("%s\n", hex_string);
}

void monitor_write_dec(u32int n) {
    // a 32 bit uint has a max value of 4294967296, which is 10 places plus a \0
    u32int temp = n;
    u32int power_of_ten = 1000000000;			    // should be 9 zeros
    char dec_string [11] = "";				    // prefill it with null-terminaters
    u8int i = 0 ; u8int j = 0;
    for (i = 9 ; i >= 0 ; i--) {			    // step through with diminishing powers of ten.  9 is the max possible.
	if ( power_of_ten < 1 )				    // run out of digits yet?
	    break;
	dec_string[j++] = (temp / power_of_ten) + '0';
	temp %= power_of_ten;
	power_of_ten /= 10;
    }
    dec_string[++j] = '\0';
    // TODO removing leading '0' chars
    i = 0 ; j = 0;
    while (!(dec_string[i] - '0'))				    // find first char not '0'
	i++;
    if (i) {							    // i is not zero, so there were some leading '0' chars
	while ( dec_string[i] != '\0' ) 
	    dec_string[j++] = dec_string[i++];			    // move the chars to the beginning
	dec_string[j] = '\0';					    // suppend the terminater
    }
    printf("%s\n",dec_string);
}
