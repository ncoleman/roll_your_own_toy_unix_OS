/*
* =====================================================================================
*
*       Filename:  main.c
*
*    Description:  
*
*        Version:  1.0
*        Created:  01/08/12 15:20:59
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Nick Coleman (), 
*        Company:  
*
* =====================================================================================
*/

#include    <stdio.h>
#include    <strings.h>
#include    "monitor.h"

void main(int argc, char **argv) {
    monitor_write_hex(12345678);
    monitor_write_dec(12345678);
}
