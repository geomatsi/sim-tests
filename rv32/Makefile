#
#
#

CROSS_COMPILE ?= riscv32-unknown-elf-

CP = $(CROSS_COMPILE)objcopy
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld

SPIKE ?= spike

BUILD ?= build

ASFLAGS = -march=rv32imac_zicsr_zifencei
CCFLAGS = -march=rv32imac_zicsr_zifencei -mabi=ilp32 -std=gnu99 -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -Werror -fno-stack-protector -O2
LDFLAGS = -nostdlib --fatal-warnings --gc-sections

# FIXME: suppress warning about RWX SRAM:
LDFLAGS += --no-warn-rwx-segment

CCFLAGS += -Icommon/include

VPATH += src crt common/src

all:
	@echo "Examples: test1 test2 test3"

TEST1_ASRCS := start1.S
TEST1_CSRCS := test1.c htif.c
TEST1_OBJS := $(patsubst %, $(BUILD)/%, $(TEST1_ASRCS:.S=.o))
TEST1_OBJS += $(patsubst %, $(BUILD)/%, $(TEST1_CSRCS:.c=.o))
TEST1_LDS := ld/spike.ld

test1: $(TEST1_LDS) $(TEST1_OBJS)
	$(LD) $(LDFLAGS) -T$< $(filter-out $<, $^) -o $(BUILD)/$@.elf
	$(SPIKE) -d --isa=rv32imac_zicsr_zifencei -m0x20000:0x80000 $(BUILD)/$@.elf

# common

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.s | $(BUILD)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(OPTS) $(CCFLAGS) -c $< -o $@

tags:
	ctags -a -R src crt

clean:
	rm -rf $(BUILD)

.PHONY: all clean tags
