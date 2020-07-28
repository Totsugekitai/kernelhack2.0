# bootのやり方

これでよし。

``` shell
$ qemu-system-x86_64 -kernel /boot/vmlinuz-`uname -r`\
                          -hda qemu-image.img\
                          -append "root=/dev/sda single"
```
