cmd_arch/arm/boot/compressed/head.o := arm-unknown-linux-uclibcgnueabi-gcc -Wp,-MD,arch/arm/boot/compressed/.head.o.d  -nostdinc -isystem /home/brenson/gnublin-buildroot-git/buildroot-2011.11/output/host/usr/lib/gcc/arm-unknown-linux-uclibcgnueabi/4.3.6/include -I/home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-lpc313x/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -include asm/unified.h -msoft-float     -Wa,-march=all   -c -o arch/arm/boot/compressed/head.o arch/arm/boot/compressed/head.S

deps_arch/arm/boot/compressed/head.o := \
  arch/arm/boot/compressed/head.S \
    $(wildcard include/config/debug/icedcc.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/v7.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/arch/sa1100.h) \
    $(wildcard include/config/debug/ll/ser3.h) \
    $(wildcard include/config/arch/s3c2410.h) \
    $(wildcard include/config/s3c/lowlevel/uart/port.h) \
    $(wildcard include/config/cpu/cp15.h) \
    $(wildcard include/config/zboot/rom.h) \
    $(wildcard include/config/arch/rpc.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/processor/id.h) \
    $(wildcard include/config/cpu/feroceon/old/id.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/linkage.h \

arch/arm/boot/compressed/head.o: $(deps_arch/arm/boot/compressed/head.o)

$(deps_arch/arm/boot/compressed/head.o):
