.PHONY: all preinstall install clean

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS += -std=gnu99 -Wall -Wextra
CFLAGS += -Os -ffunction-sections -fdata-sections
LDFLAGS += -L.
LDLIBS = -lm
MMCU ?= atmega328p
FREQ ?= 8000000

TARGET ?= blink
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

all: $(TARGET)

preinstall:
ifneq ($(wildcard /etc/lsp-release),)
	apt install avr-libc avrdude binutils-avr gcc-avr
else ifneq ($(wildcard /etc/fedora-release),)
	dnf install avr-libc avrdude avr-binutils avr-gcc
endif

install:
	avrdude -F -c arduino -p $(MMCU) -P /dev/ttyACM* -U flash:w:$(TARGET).ihex

clean:
	rm -f $(TARGET) $(TARGET).* $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -mmcu=$(MMCU) -o $@ $^ $(LDLIBS)
	$(OBJCOPY) -O ihex -R .eeprom $@ $@.ihex

%.o: %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -mmcu=$(MMCU) -DF_CPU=$(FREQ) -c -o $@ $<
