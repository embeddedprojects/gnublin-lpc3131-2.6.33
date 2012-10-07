cmd_arch/arm/mm/tlb-v4wbi.o := arm-unknown-linux-uclibcgnueabi-gcc -Wp,-MD,arch/arm/mm/.tlb-v4wbi.o.d  -nostdinc -isystem /home/brenson/gnublin-buildroot-git/buildroot-2011.11/output/host/usr/lib/gcc/arm-unknown-linux-uclibcgnueabi/4.3.6/include -I/home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-lpc313x/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -include asm/unified.h -msoft-float       -c -o arch/arm/mm/tlb-v4wbi.o arch/arm/mm/tlb-v4wbi.S

deps_arch/arm/mm/tlb-v4wbi.o := \
  arch/arm/mm/tlb-v4wbi.S \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/linkage.h \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/tlbflush.h \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/cpu/tlb/v3.h) \
    $(wildcard include/config/cpu/tlb/v4wt.h) \
    $(wildcard include/config/cpu/tlb/fa.h) \
    $(wildcard include/config/cpu/tlb/v4wbi.h) \
    $(wildcard include/config/cpu/tlb/feroceon.h) \
    $(wildcard include/config/cpu/tlb/v4wb.h) \
    $(wildcard include/config/cpu/tlb/v6.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/tlb/v7.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/glue.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/abrt/lv4t.h) \
    $(wildcard include/config/cpu/abrt/ev4.h) \
    $(wildcard include/config/cpu/abrt/ev4t.h) \
    $(wildcard include/config/cpu/abrt/ev5tj.h) \
    $(wildcard include/config/cpu/abrt/ev5t.h) \
    $(wildcard include/config/cpu/abrt/ev6.h) \
    $(wildcard include/config/cpu/abrt/ev7.h) \
    $(wildcard include/config/cpu/pabrt/legacy.h) \
    $(wildcard include/config/cpu/pabrt/v6.h) \
    $(wildcard include/config/cpu/pabrt/v7.h) \
  arch/arm/mm/proc-macros.S \
    $(wildcard include/config/cpu/dcache/writethrough.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/brenson/Arbeitsfläche/Studium/01-Praktikum/03-Gnublin-repo/gnublin/lpc3131/rootfs/debian/debian_install/debian_process/linux-2.6.33-lpc313x/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \

arch/arm/mm/tlb-v4wbi.o: $(deps_arch/arm/mm/tlb-v4wbi.o)

$(deps_arch/arm/mm/tlb-v4wbi.o):
