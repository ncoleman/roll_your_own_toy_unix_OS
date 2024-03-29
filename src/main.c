/*
* =====================================================================================
*
*       Filename:  main.c
*
*    Description:  
*
*        Version:  1.0
*        Created:  01/07/12 10:50:33
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Nick Coleman (), 
*        Company:  
*
* =====================================================================================
*/

#include	"monitor.h"

// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made for JamesM's tutorials 

int main(struct multiboot *mboot_ptr)
{
  // All our initialisation calls will go in here.
  monitor_clear();
  monitor_write("Hello world!\n");
  monitor_write_hex(12345678);
  monitor_write("\n");
  monitor_write_dec(12345678);
  monitor_write("\n");
  return 0xDEADBABA;
}

