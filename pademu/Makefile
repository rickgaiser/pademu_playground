IOP_OBJS = pademu.o sys_utils.o imports.o exports.o
IOP_INCS = -I$(PS2SDKSRC)/iop/usb/usbd/include

ifeq ($(USE_USB),1)
IOP_CFLAGS += -DUSB
IOP_OBJS += ds34usb.o
endif

ifeq ($(USE_BT),1)
IOP_CFLAGS += -DBT -DUSE_THREAD
IOP_OBJS += ds34bt.o
endif

ifeq ($(VMC),1)
IOP_CFLAGS += -DVMC
endif

IOP_OBJS := $(IOP_OBJS:%=$(IOP_OBJNAME)%)

include $(PS2SDKSRC)/Defs.make
include $(PS2SDKSRC)/iop/Rules.bin.make
include $(PS2SDKSRC)/iop/Rules.make
include $(PS2SDKSRC)/iop/Rules.release
