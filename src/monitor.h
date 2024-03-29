/*
* =====================================================================================
*
*       Filename:  monitor.h
*
*    Description:  
*
*        Version:  1.0
*        Created:  01/07/12 17:48:03
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Nick Coleman (), 
*        Company:  
*
* =====================================================================================
*/

// monitor.h -- Defines the interface for monitor.h
// From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

void monitor_write_hex(u32int n);
void monitor_write_dec(u32int n);

#endif // MONITOR_H

