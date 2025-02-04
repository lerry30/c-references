MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200
PORT = /dev/ttyACM0
PROGRAMMER = arduino

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall
TARGET = main

SRCS = main.c led_display.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).bin: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(TARGET).hex: $(TARGET).bin
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).bin $(TARGET).hex

flash: $(TARGET).hex
	sudo $(AVRDUDE) -F -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex

clean:
	rm -f $(OBJS) $(TARGET).bin $(TARGET).hex
