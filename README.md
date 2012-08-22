hid-a320
========

Lenovo Ideacentre a320 linux keyboard driver.
Fix Shift, Alt, and Ctrl keys press.

Install
-------
Downloag and compile source code:
```
git clone https://github.com/aleksandr-rakov/hid-a320.git
cd hid-a320
make
sudo make install
```

Module load at boot time:
On ubuntu 12.04:
1: add ```hid-a320``` to ```/etc/initramfs-tools/modules```
2: run ```sudo update-initramfs -u```
3: reboot

Manual module load:
Run as root:
```
modprobe -r usbhid; modprobe hid-a320; modprobe usbhid

```

Note
----
After updating kernel you must reinstall driver.

Issue
-----
(Ctrl Alt F4) (Ctrl Alt F7) (Ctrl Alt F11) Dont work - it is hadrware bug.
Use RCtrl RAlt for this key combinations.
