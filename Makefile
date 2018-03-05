all:
	$(MAKE) -C pademu all USE_USB=1 USE_BT=1
	$(MAKE) -C sample_padx all

clean:
	$(MAKE) -C pademu clean USE_USB=1 USE_BT=1
	$(MAKE) -C sample_padx clean

copy:
	cp /usr/local/ps2dev/ps2sdk/iop/irx/*.irx modules/

reset: all
	ps2client -h $(PS2_IP) reset

test: all
	ps2client -h $(PS2_IP) execee host:sample_padx/padx_sample.elf
