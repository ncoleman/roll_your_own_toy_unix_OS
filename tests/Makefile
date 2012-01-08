# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=main.o monitor.o 

CFLAGS=-std=c99 -Wall -Wextra 
LDFLAGS=
ASFLAGS=-felf

all: $(SOURCES) link 

clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o test $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

