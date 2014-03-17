# TARGET=atmega88
TARGET=attiny13
ISP=usbasp

CC=avr-gcc
CFLAGS=-Wall -Os -std=c99 -I. -mmcu=$(TARGET)

# clkdiv 8
# HFUSE=0xdf
# LFUSE=0x62
# EFUSE=0x01

# clkdiv 1
HFUSE=0xDF
LFUSE=0xE2
EFUSE=0x01

HFUSE_TINY=0xFF
LFUSE_TINY=0x7A

.PHONY: clean all flash

all: main.hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.bin *.hex *.map

main.bin: main.o lcd.o
	$(CC) $(CFLAGS) -o main.bin main.o lcd.o

main.hex: main.bin
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex

disasm:	main.bin
	avr-objdump -d main.bin

flash: main.hex
	avrdude -c ${ISP} -p ${TARGET} -U flash:w:main.hex

setfuse:
	avrdude -c ${ISP} -p ${TARGET} -u -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m -U efuse:w:$(EFUSE):m

readfuse:
	avrdude -c ${ISP} -p ${TARGET} -u -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h

setfuse_tiny:
	avrdude -c ${ISP} -p ${TARGET} -u -U hfuse:w:$(HFUSE_TINY):m -U lfuse:w:$(LFUSE_TINY):m

readfuse_tiny:
	avrdude -c ${ISP} -p ${TARGET} -u -U hfuse:r:-:h -U lfuse:r:-:h


avrdude:
	avrdude -c ${ISP} -p ${TARGET} -v

tags:
	ctags -eR
