CC      := gcc
LD      := ld
CFLAGS  := -std=gnu11 -ffreestanding -fno-stack-protector 
           -fno-pic -fno-pie -Wall -Wextra -Iinclude
LDFLAGS :=

BUILD_DIR := build
TARGET    := $(BUILD_DIR)/crk.bin

SOURCES := $(shell find . -type f -name '*.c' 
           -not -path './$(BUILD_DIR)/*' 
           -not -path './.git/*')

OBJECTS := $(patsubst ./%.c,$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY: all clean list

all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)


$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)


$(BUILD_DIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

list:
	@printf '%s\n' $(SOURCES)

clean:
	rm -rf $(BUILD_DIR)
