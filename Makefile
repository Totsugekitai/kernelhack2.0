.RECIPEPREFIX = >

LINUX := linux-5.7.10
BUILDROOT := buildroot-2020.02.4
TOOLS := tools

.PHONY : linux
linux:
> make -j9 -C $(LINUX)
> cp $(LINUX)/arch/x86/boot/bzImage $(TOOLS)
> cp $(LINUX)/vmlinux $(TOOLS)

.PHONY : buildroot
buildroot:
> make -C $(BUILDROOT)
> cp $(BUILDROOT)/output/images/rootfs.ext4 $(TOOLS)

.PHONY : run
run:
> qemu-system-x86_64 -s -kernel $(TOOLS)/bzImage -boot c -m 2049M -hda $(TOOLS)/rootfs.ext4 -append "root=/dev/sda rw console=ttyS0,115200 acpi=off nokaslr" -serial stdio -display none

.PHONY : debug
debug:
> gdb $(LINUX)/vmlinux

.PHONY : clean
clean:
> make clean -C $(LINUX)
> make clean -C $(BUILDROOT)

