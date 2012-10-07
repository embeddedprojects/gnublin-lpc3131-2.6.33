cmd_arch/arm/nwfpe/entry.o := arm-unknown-linux-uclibcgnueabi-gcc -Wp,-MD,arch/arm/nwfpe/.entry.o.d  -nostdinc -isystem /home/brenson/gnublin-buildroot-git/buildroot-2011.11/output/host/usr/lib/gcc/arm-unknown-linux-uclibcgnueabi/4.3.6/include -I/home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-lpc313x/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -include asm/unified.h -msoft-float       -c -o arch/arm/nwfpe/entry.o arch/arm/nwfpe/entry.S

deps_arch/arm/nwfpe/entry.o := \
  arch/arm/nwfpe/entry.S \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \

arch/arm/nwfpe/entry.o: $(deps_arch/arm/nwfpe/entry.o)

$(deps_arch/arm/nwfpe/entry.o):
