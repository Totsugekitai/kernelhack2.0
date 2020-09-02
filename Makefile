.RECIPEPREFIX = >

LINUX := linux-5.7.10
TOOLS := tools
SHARE := share

.PHONY : linux
linux:
> make -j9 -C $(LINUX)
> cp $(LINUX)/arch/x86/boot/bzImage $(TOOLS)
> cp $(LINUX)/vmlinux $(TOOLS)

.PHONY : run
run:
> qemu-system-x86_64 -enable-kvm -s -kernel $(TOOLS)/bzImage -boot c -m 2049M -hda $(TOOLS)/image.img -append "root=/dev/sda rw console=ttyS0,115200 acpi=off nokaslr console=tty9" -serial stdio -display none -virtfs local,path=$(SHARE),security_model=none,mount_tag=share --no-reboot

.PHONY : netrun
netrun:
> qemu-system-x86_64 -enable-kvm -s -kernel $(TOOLS)/bzImage -boot c -m 2049M -hda $(TOOLS)/image.img -append "root=/dev/sda rw console=ttyS0,115200 acpi=off nokaslr console=tty9" -serial stdio -display none -virtfs local,path=$(SHARE),security_model=none,mount_tag=share -net nic -net bridge,br=br3 --no-reboot

.PHONY : debug
debug:
> gdb $(LINUX)/vmlinux

.PHONY : clean
clean:
> make clean -C $(LINUX)

