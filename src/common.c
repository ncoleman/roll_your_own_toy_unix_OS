/*
* =====================================================================================
*
*       Filename:  common.c
*
*    Description:  
*
*        Version:  1.0
*        Created:  01/07/12 17:46:46
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Nick Coleman (), 
*        Company:  
*
* =====================================================================================
*/

// common.c -- Defines some global functions.
// From JamesM's kernel development tutorials.

#include "common.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void memcpy(u32int *src, u32int *dest, u16int len)
{
    while(len--) {
	// no bounds checking, so dest < src+len if you are not careful
	*src++ = *dest++ ;
    }
}

void memset(u32int *src, s32int c, u16int len)
{
    while(len--) {
	*src++ = c;
    }
}

u16int strlen(const char *c) {
    // warning: no bounds checking
    u16int i = 0;
    while(c[i] != '\0')
	i++;
    return i-1;
}

s16int strcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
	i++;
    }
    return (s16int)(s1[i] - s2[i]);
}
