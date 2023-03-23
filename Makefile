ifndef $(MSPGCCDIR)
	MSPGCCDIR=$(HOME)/ti/msp430-gcc
endif
#paths
INCLUDES_DIRECTORY = $(MSPGCCDIR)/include

DEVICE = msp430fr2355

# compiler options
CC=$(MSPGCCDIR)/bin/msp430-elf-gcc

CFLAGS = -I . -I $(INCLUDES_DIRECTORY) -mmcu=$(DEVICE) -g -mhwmult=f5series
LFLAGS = -L . -L $(INCLUDES_DIRECTORY)

# mspdebug driver -- used for installation
DRIVER:= tilib

# Compiling
all: main.elf

%.elf : %.c
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

install: main.elf
	mspdebug $(DRIVER) "prog $<" --allow-fw-update

clean:
	rm -f *.o *.elf
