hid-a320
========

Lenovo Ideacentre A320 linux keyboard driver.

It should work on Ideacentre A300 and Ideacentre A310

Fix Shift, Alt, and Ctrl keys press.

Install
-------
Download and compile source code:
```
git clone https://github.com/aleksandr-rakov/hid-a320.git
cd hid-a320
make
sudo make install
```

Make module load at boot time (ubuntu 12.04 example):
* add ```hid-a320``` to ```/etc/initramfs-tools/modules```
* run ```sudo update-initramfs -u```
* reboot

Or try manual module load:
```
sudo modprobe -r usbhid; sudo modprobe hid-a320; sudo modprobe usbhid;
```

For ubuntu users
----------------
Just run ```ubuntu-install``` script

Auto compiling module on kernel update
----------------
Just run ```dkms-install``` script


Note
----
After updating kernel you must reinstall driver.

Note
----
To turn off numlock press ```Fn F11```

Issue
-----
(Ctrl Alt F4) (Ctrl Alt F7) (Ctrl Alt F11) Dont work - it is hadrware bug.
Use RCtrl RAlt for this key combinations.
