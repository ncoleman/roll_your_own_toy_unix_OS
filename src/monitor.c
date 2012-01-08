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

// The VGA framebuffer starts at 0xB8000
u16int *video_memory = (u16int *)0xB8000;
// Store the cursor position
u8int cursor_x = 0;
u8int cursor_y = 0;

// Updates the hardware cursor.
static void move_cursor()
{
   // The screen is 80 characters wide...
   u16int cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{

   // Get a space character with the default colour attributes.
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(cursor_y >= 25)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = 24;
   }
}

// Writes a single character out to the screen.
void monitor_put(char c)
{
   // The background colour is black (0), the foreground is white (15).
   u8int backColour = 0;
   u8int foreColour = 15;

   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   u16int attribute = attributeByte << 8;
   u16int *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.
   scroll();
   // Move the hardware cursor.
   move_cursor();
}

// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
   // Make an attribute byte for the default colours
   u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   u16int blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(char *c)
{
   int i = 0;
   while (c[i])
   {
       monitor_put(c[i++]);
   }
}

// does not handle negative numbers because tutorial defines n as unsigned
void monitor_write_hex(u32int n) {
    // since the int is guaranteed to be 4 bytes, just use 4 simple masks rather than bother with looping through.
    char HEX[] = "0123456789ABCDEF";
    // 6 chars of FFFFFF plus 1 terminator; prefill it with null-terminaters
    const u8int MAX_CHARS = 6;
    char hex_string[MAX_CHARS + 1];
    hex_string[0] = '\0';
    u8int i = 0; u8int j = 0;
    for (i=0 ; i < MAX_CHARS ; i++) {
	/* 
	Mask in only the relevant byte, then shift it to LSB.
	mask is shifted in decrementing amounts of 4 to the left.
	e.g. 0xF00000 which is 0xF << 20, then << 16, then << 12, etc
	LSB is the result from applying the mask then shifted to the right by 20, then 16, then 12, etc. E.g. an unrolled example:
	hex_string[1] = HEX[(n & 0x0F0000) >> 20];		    
	hex_string[2] = HEX[(n & 0x00F000) >> 16];		    */
	hex_string[i] = HEX[(n & (0xF << (4*(MAX_CHARS - 1 - i)))) >> (20-i*4)];
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
    monitor_write(hex_string);
}

// does not handle negative numbers because tutorial defines n as unsigned
void monitor_write_dec(u32int n) {
    // a 32 bit uint has a max value of 4,294,967,296, which is 10 places plus a \0
    char dec_string [11] = "";				    // prefill it with null-terminaters
    u32int power_of_ten = 1000000000;			    // should be 9 zeros
    u32int temp = n;
    u8int i = 0 ; u8int j = 0;
    for (i = 0 ; i <= 9 ; i--) {			    // step through with diminishing powers of ten.  9 is the max possible.
	if ( power_of_ten < 1 )				    // run out of digits yet?
	    break;
	dec_string[j++] = (temp / power_of_ten) + '0';
	temp %= power_of_ten;
	power_of_ten /= 10;
    }
    dec_string[++j] = '\0';
    // remove leading '0' chars
    i = 0 ; j = 0;
    while (!(dec_string[i] - '0'))				    // find first char not '0'
	i++;
    if (i) {							    // i is not zero, so there were some leading '0' chars
	while ( dec_string[i] != '\0' ) 
	    dec_string[j++] = dec_string[i++];			    // move the chars to the beginning
	dec_string[j] = '\0';					    // suppend the terminater
    }
    monitor_write(dec_string);
}
