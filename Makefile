#  Project Name
NAME = stm32f100c8

STDPERIPH_PATH=../STM32F10x_StdPeriph_Lib_V3.5.0
CMSIS_PATH=$(STDPERIPH_PATH)/Libraries/CMSIS/CM3
DEVICE_CMSIS_PATH=$(CMSIS_PATH)/DeviceSupport/ST/STM32F10x

#  List of the objects files to be compiled/assembled

SOURCES=src/main.c
SYSTEM_STM32_SOURCE=$(DEVICE_CMSIS_PATH)/system_stm32f10x.c
SYSTEM_STM32_OBJECT=system_stm32f10x.o
STARTUP_SOURCE=$(DEVICE_CMSIS_PATH)/startup/gcc_ride7/startup_stm32f10x_md_vl.s
STARTUP_OBJECT=startup.o
OBJECTS=$(SOURCES:.c=.o) $(SYSTEM_STM32_OBJECT) $(STARTUP_OBJECT)

OPTIMIZATION = -Os -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD_VL -ffunction-sections -fdata-sections
#DEBUG = -g
INCLUDES = -I. -I$(CMSIS_PATH)/CoreSupport -I$(DEVICE_CMSIS_PATH)

#  Compiler Options
CFLAGS = -Wall -mcpu=cortex-m3 -mfloat-abi=softfp -mthumb $(OPTIMIZATION) $(DEBUG) $(INCLUDES)
LDFLAGS = -static -mcpu=cortex-m3 -mfloat-abi=softfp -nostartfiles -mthumb -Tstm32_flash.ld $(OPTIMIZATION)
ASFLAGS = -mcpu=cortex-m3 --defsym RAM_MODE=0

#  Compiler/Assembler/Linker Paths
GCC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
STRIP = arm-none-eabi-strip
OBJDUMP = arm-none-eabi-objdump
REMOVE = rm -f
SIZE = arm-none-eabi-size

STFLASH = st-flash

#########################################################################
.PHONY: all
all: $(OBJECTS)
	$(GCC) $(LDFLAGS) $(OBJECTS) -o $(NAME).elf
	$(OBJCOPY) -O binary $(NAME).elf $(NAME).bin
	$(REMOVE) $(NAME).elf

.PHONY: clean
clean:
	$(REMOVE) $(OBJECTS) $(NAME).bin

#########################################################################
#  Default rules to compile .c and .cpp file to .o
#  and assemble .s files to .o

.c.o :
	$(GCC) $(CFLAGS) -c $< -o $@

.S.o :
	$(AS) $(ASFLAGS) -o $@ $<

$(STARTUP_OBJECT) :
	$(AS) $(ASFLAGS) -o $@ $(STARTUP_SOURCE)

$(SYSTEM_STM32_OBJECT) :
	$(GCC) $(CFLAGS) -c $(SYSTEM_STM32_SOURCE) -o $@


#########################################################################
flash: all
	$(STFLASH) --reset write $(NAME).bin 0x8000000
erase:
	$(STFLASH) erase
