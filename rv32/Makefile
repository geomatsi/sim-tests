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

#
# test1
#

TEST1_ASRCS := start1.S
TEST1_CSRCS := test1.c htif.c xprintf.c stdlib.c
TEST1_OBJS := $(patsubst %, $(BUILD)/%, $(TEST1_ASRCS:.S=.o))
TEST1_OBJS += $(patsubst %, $(BUILD)/%, $(TEST1_CSRCS:.c=.o))
TEST1_LDS := ld/spike.ld

test1: $(TEST1_LDS) $(TEST1_OBJS)
	$(LD) $(LDFLAGS) -T$< $(filter-out $<, $^) -o $(BUILD)/$@.elf
	#$(SPIKE) --isa=rv32imac_zicsr_zifencei -m0x20000:0x80000 $(BUILD)/$@.elf

#
# test2
#

TEST2_ASRCS := start1.S
TEST2_CSRCS := test2.c htif.c xprintf.c stdlib.c
TEST2_OBJS := $(patsubst %, $(BUILD)/%, $(TEST2_ASRCS:.S=.o))
TEST2_OBJS += $(patsubst %, $(BUILD)/%, $(TEST2_CSRCS:.c=.o))
TEST2_LDS := ld/spike.ld

test2: $(TEST2_LDS) $(TEST2_OBJS)
	$(LD) $(LDFLAGS) -T$< $(filter-out $<, $^) -o $(BUILD)/$@.elf
	#$(SPIKE) --isa=rv32imac_zicsr_zifencei -m0x20000:0x80000 $(BUILD)/$@.elf

#
# test3
#

TEST3_ASRCS := start1.S
TEST3_CSRCS := test3.c htif.c xprintf.c stdlib.c
TEST3_OBJS := $(patsubst %, $(BUILD)/%, $(TEST3_ASRCS:.S=.o))
TEST3_OBJS += $(patsubst %, $(BUILD)/%, $(TEST3_CSRCS:.c=.o))
TEST3_LDS := ld/spike.ld

test3: $(TEST3_LDS) $(TEST3_OBJS)
	$(LD) $(LDFLAGS) -T$< $(filter-out $<, $^) -o $(BUILD)/$@.elf
	#$(SPIKE) --real-time-clint --isa=rv32imac_zicsr_zifencei -m0x20000:0x80000 $(BUILD)/$@.elf

# common

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.s | $(BUILD)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(OPTS) $(CCFLAGS) -c $< -o $@

tags:
	ctags -a -R src crt common

clean:
	rm -rf $(BUILD)

.PHONY: all clean tags
