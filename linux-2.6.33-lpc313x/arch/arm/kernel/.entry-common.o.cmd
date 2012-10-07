cmd_arch/arm/kernel/entry-common.o := arm-unknown-linux-uclibcgnueabi-gcc -Wp,-MD,arch/arm/kernel/.entry-common.o.d  -nostdinc -isystem /home/brenson/gnublin-buildroot-git/buildroot-2011.11/output/host/usr/lib/gcc/arm-unknown-linux-uclibcgnueabi/4.3.6/include -I/home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-lpc313x/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -include asm/unified.h -msoft-float       -c -o arch/arm/kernel/entry-common.o arch/arm/kernel/entry-common.S

deps_arch/arm/kernel/entry-common.o := \
  arch/arm/kernel/entry-common.S \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/oabi/compat.h) \
    $(wildcard include/config/arm/thumb.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/aeabi.h) \
    $(wildcard include/config/alignment/trap.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/unistd.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/ftrace.h \
    $(wildcard include/config/frame/pointer.h) \
    $(wildcard include/config/arm/unwind.h) \
  arch/arm/mach-lpc313x/include/mach/entry-macro.S \
  arch/arm/mach-lpc313x/include/mach/hardware.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/sizes.h \
  arch/arm/mach-lpc313x/include/mach/constants.h \
  arch/arm/mach-lpc313x/include/mach/registers.h \
    $(wildcard include/config/reg.h) \
    $(wildcard include/config/pec.h) \
    $(wildcard include/config/ecgc.h) \
    $(wildcard include/config/8bit/ecc.h) \
    $(wildcard include/config/tl/528.h) \
    $(wildcard include/config/tl/516.h) \
    $(wildcard include/config/tl/512.h) \
    $(wildcard include/config/tl/mask.h) \
    $(wildcard include/config/eo.h) \
    $(wildcard include/config/dc.h) \
    $(wildcard include/config/m.h) \
    $(wildcard include/config/lc/0.h) \
    $(wildcard include/config/lc/1.h) \
    $(wildcard include/config/lc/2.h) \
    $(wildcard include/config/lc/mask.h) \
    $(wildcard include/config/es.h) \
    $(wildcard include/config/de.h) \
    $(wildcard include/config/ao.h) \
    $(wildcard include/config/wd.h) \
    $(wildcard include/config/ec.h) \
    $(wildcard include/config/cfg/io/drive.h) \
    $(wildcard include/config/cfg/data/def.h) \
    $(wildcard include/config/cfg/cle/1.h) \
    $(wildcard include/config/cfg/ale/1.h) \
    $(wildcard include/config/cfg/we/1.h) \
    $(wildcard include/config/cfg/re/1.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/unwind.h \
  arch/arm/kernel/entry-header.S \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/linkage.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/linkage.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/smp.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/ptrace.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/hwcap.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  arch/arm/kernel/calls.S \

arch/arm/kernel/entry-common.o: $(deps_arch/arm/kernel/entry-common.o)

$(deps_arch/arm/kernel/entry-common.o):
