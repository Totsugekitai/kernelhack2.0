# rootfsを作る

こんな感じにすればarchlinuxが構築可能。

```
IMG=qemu-image.img
DIR=mount-point.dir
$ qemu-img create $IMG 1g
$ mkfs.ext4 $IMG
$ mkdir $DIR
$ sudo mount -o loop $IMG $DIR
$ sudo pacstrap $DIR base linux linux-firmware
$ sudo arch-chroot $DIR
# passwd
# exit
$ sudo umount $DIR
$ rmdir $DIR
```
