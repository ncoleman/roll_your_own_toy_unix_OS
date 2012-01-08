/*
* =====================================================================================
*
*       Filename:  common.h
*
*    Description:  
*
*        Version:  1.0
*        Created:  01/07/12 17:46:12
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Nick Coleman (), 
*        Company:  
*
* =====================================================================================
*/

// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

void memcpy(u32int *src, u32int *dest, u16int len);
void memset(u32int *src, s32int c, u16int len);

// strlen returns length of string without terminating \0 character
u16int strlen(const char *c); 
// strcmp checks two strings; returns neg if s1 < s2, 0 if equal, pos if s1 > s2
s16int strcmp(const char *s1, const char *s2);

#endif

