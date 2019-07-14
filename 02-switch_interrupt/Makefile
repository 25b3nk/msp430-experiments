CC=msp430-gcc
CFLAGS=-Os -Wall -g -mmcu=msp430g2553

OBJS=switch_interrup.o


all: $(OBJS)
	$(CC) $(CFLAGS) -o main.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr main.elf $(OBJS)
